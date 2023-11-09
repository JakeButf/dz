#include "../include/dz.h"
#include "../include/Drawing.h"
#include "../include/tcpgecko.h"
#include "../include/twwhd.h"
#include <future>
#include <string>
#include <mutex>
#include <condition_variable>
#include <map>
#include <chrono>
#include <thread>

static TCPGecko* gecko = nullptr;
static bool isConnected = false;
static char ipBuffer[16] = "192.168.4.57";
static const char* connectionStatus = "Status: Awaiting Connection...";
static const char* connectButton = "Connect";

//inventory editor
static bool invedit_showWindow = false;

static bool hasTelescope = false;
static bool hasWindWaker = false;
static bool hasGrapplingHook = false;
static bool hasSpoilsBag = false;
static bool hasBoomerang = false;
static bool hasDekuLeaf = false;
static bool hasTingleBottle = false;
static bool hasPictoBox = false;
static bool hasIronBoots = false;
static bool hasMagicArmor = false;
static bool hasBaitBag = false;
static bool hasHerosBow = false;
static bool hasBombs = false;
static bool hasBottle1 = false;
static bool hasBottle2 = false;
static bool hasBottle3 = false;
static bool hasBottle4 = false;
static bool hasDeliveryBag = false;
static bool hasHookshot = false;
static bool hasSkullHammer = false;
//debug
static bool debug_showWindow = false;


void DZ_GeckoConnect(std::string wiiuip)
{
	connectionStatus = "Status: Attempting Connection...";
	if (gecko) //Make sure there's no repeat connections
	{
		DZ_GeckoDisconnect();
	}

	gecko = new TCPGecko(wiiuip, 7331);

	if (gecko->Connect()) //Check if gecko connected
	{
		isConnected = true;
		std::cout << "Connection Successful to " << wiiuip;
	}
	else 
	{
		isConnected = false;
		std::cout << "Connection Failed to " << wiiuip;
	}
}

void DZ_GeckoDisconnect()
{
	gecko->Disconnect();
	delete gecko;
	gecko = nullptr;
	isConnected = false;
}

void DZ_DrawMainWindow()
{
	if (isConnected)
	{
		connectionStatus = "Status: Connected";
		connectButton = "Disconnect";
	}
	else
	{
		connectionStatus = "Status: Not Connected";
		connectButton = "Connect";
	}

#pragma region Wii U Connection
	if (ImGui::CollapsingHeader("Wii U Connection", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::InputText("Wii U IP:", ipBuffer, IM_ARRAYSIZE(ipBuffer));
		if (ImGui::Button(connectButton))
		{
			if (!isConnected)
				DZ_GeckoConnect(std::string(ipBuffer));
			else
				DZ_GeckoDisconnect();
		}

		ImGui::Text(connectionStatus);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
#pragma endregion
#pragma region Watches
	if (ImGui::Button("Watches")) {/*unimplemented*/ }
#pragma endregion
#pragma region Debug
    if (ImGui::Button("Debug"))
        debug_showWindow = !debug_showWindow;
    if (debug_showWindow)
        DZ_DrawDebugWindow();
#pragma endregion
#pragma region Inventory Editor
    if (ImGui::Button("Inventory Editor"))
    {
        DZ_InventoryEditWindow_CheckIfHasItems();
        invedit_showWindow = !invedit_showWindow;
    } 
    if (invedit_showWindow)
        DZ_DrawInventoryEditWindow();
#pragma endregion
}

void DZ_DisposeMainWindow()
{
	if (gecko)
		DZ_GeckoDisconnect();
}

void DZ_DrawDebugWindow()
{
    static char debugAddressInput[128] = "";
    static const char* debugSizes[] = { "32-Bit", "8-Bit"};
    static int currentDebugSize = 4; // Default to 32 bit
    static uint32_t debugValue = 0;

    ImGui::SetNextWindowSize(ImVec2(400, 155), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("DZ: Debug", nullptr)) {
        ImGui::InputText("Address (hex)", debugAddressInput, IM_ARRAYSIZE(debugAddressInput));

        // Drop-down for selecting size of data to peek
        if (ImGui::BeginCombo("View", debugSizes[currentDebugSize])) {
            for (int i = 0; i < IM_ARRAYSIZE(debugSizes); i++) {
                bool isSelected = (currentDebugSize == i);
                if (ImGui::Selectable(debugSizes[i], isSelected)) {
                    currentDebugSize = i;
                }
                if (isSelected) {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }

        if (ImGui::Button("Peek")) {
            // Validate input and perform the memory peek
            if (debugAddressInput[0] != '\0') {
                uint32_t address = StringToUint32(debugAddressInput);
                if (currentDebugSize == 0)
                    debugValue = gecko->peekmem(address);
                else
                    debugValue = gecko->peekmem8(address);
            }
        }

        // Display the peeked value in different formats
        ImGui::Separator();
        uint8_t firstByte = static_cast<uint8_t>((debugValue >> 24) & 0xFF);
        uint16_t firstTwoBytes = static_cast<uint16_t>((debugValue >> 16) & 0xFFFF);
        uint8_t lastByte = static_cast<uint8_t>(debugValue & 0xFF);
        uint16_t lastTwoBytes = static_cast<uint16_t>(debugValue & 0xFFFF);

        char str[5] = {
                static_cast<char>((debugValue >> 24) & 0xFF),
                static_cast<char>((debugValue >> 16) & 0xFF),
                static_cast<char>((debugValue >> 8) & 0xFF),
                static_cast<char>(debugValue & 0xFF),
                '\0'
        };

        switch (currentDebugSize) {
        case 0: // First 8 bits
            // Display as 32-bit integer, hex, and string (if applicable)
            ImGui::Text("INT: %d", static_cast<int>(debugValue));
            ImGui::Text("HEX: 0x%08X", debugValue);
            ImGui::Text("STRING: %s", str);
            break;
        case 1: 
            ImGui::Text("INT: %d", lastByte);
            ImGui::Text("HEX: 0x%02X", lastByte);
            ImGui::Text("STRING: %c", static_cast<char>(lastByte));
            break;
        }
    }
    ImGui::End();
}

void DZ_DrawInventoryEditWindow()
{
    ImGui::SetNextWindowSize(ImVec2(400, 155), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("DZ: Inventory Editor", nullptr))
    {
        ImGui::Checkbox("Telescope", &hasTelescope);
        ImGui::SameLine();
        ImGui::Checkbox("Wind Waker", &hasWindWaker);
        ImGui::SameLine();
        ImGui::Checkbox("Grappling Hook", &hasGrapplingHook);

        ImGui::NewLine();
        ImGui::Checkbox("Spoils Bag", &hasSpoilsBag);
        ImGui::SameLine();
        ImGui::Checkbox("Boomerang", &hasBoomerang);
        ImGui::SameLine();
        ImGui::Checkbox("Deku Leaf", &hasDekuLeaf);

        ImGui::NewLine();
        ImGui::Checkbox("Tingle Bottle", &hasTingleBottle);
        ImGui::SameLine();
        ImGui::Checkbox("Iron Boots", &hasIronBoots);
        ImGui::SameLine();
        ImGui::Checkbox("Magic Armor", &hasMagicArmor);

        ImGui::NewLine();
        ImGui::Checkbox("Bait Bag", &hasTingleBottle);
        ImGui::SameLine();
        ImGui::Checkbox("Delivery Bag", &hasIronBoots);
        ImGui::SameLine();
        ImGui::Checkbox("Hookshot", &hasMagicArmor);

        ImGui::NewLine();
        ImGui::Checkbox("Bombs", &hasBombs);
        ImGui::SameLine();
        ImGui::Checkbox("Skull Hammer", &hasSkullHammer);
    }
}

void DZ_InventoryEditWindow_CheckIfHasItems()
{
    hasTelescope = gecko->peekmem8(item_slots.telescope.address) != 0xFF;
    hasWindWaker = gecko->peekmem8(item_slots.wind_waker.address) != 0xFF;
    hasGrapplingHook = gecko->peekmem8(item_slots.grappling_hook.address) != 0xFF;

    hasSpoilsBag = gecko->peekmem8(item_slots.spoils_bag.address) != 0xFF;
    hasBoomerang = gecko->peekmem8(item_slots.boomerang.address) != 0xFF;
    hasDekuLeaf = gecko->peekmem8(item_slots.deku_leaf.address) != 0xFF;

    hasTingleBottle = gecko->peekmem8(item_slots.tingle_bottle.address) != 0xFF;
    hasIronBoots = gecko->peekmem8(item_slots.iron_boots.address) != 0xFF;
    hasMagicArmor = gecko->peekmem8(item_slots.magic_armor.address) != 0xFF;

    hasBaitBag = gecko->peekmem8(item_slots.bait_bag.address) != 0xFF;
    hasDeliveryBag = gecko->peekmem8(item_slots.delivery_bag.address) != 0xFF;
    hasHookshot = gecko->peekmem8(item_slots.hookshot.address) != 0xFF;

    hasBombs = gecko->peekmem8(item_slots.bombs.address) != 0xFF;
    hasSkullHammer = gecko->peekmem8(item_slots.skull_hammer.address) != 0xFF;
}

uint32_t StringToUint32(const std::string& str)
{
	unsigned long address = std::stoul(str, nullptr, 16);
	return static_cast<uint32_t>(address);
}

void uint32ToCharArray(uint32_t value, char* array) 
{
	array[0] = (value >> 24) & 0xFF; 
	array[1] = (value >> 16) & 0xFF; 
	array[2] = (value >> 8) & 0xFF; 
	array[3] = value & 0xFF;       
}
