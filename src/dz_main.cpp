#include "../include/dz.h"
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

//inventory checkbox states
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
static bool hasPowerBracelet = false;

//inventory checkbox prev states
static bool prevTelescope = hasTelescope;
static bool prevWindWaker = hasWindWaker;
static bool prevGrapplingHook = hasGrapplingHook;
static bool prevSpoilsBag = hasSpoilsBag;
static bool prevBoomerang = hasBoomerang;
static bool prevDekuLeaf = hasDekuLeaf;
static bool prevTingleBottle = hasTingleBottle;
static bool prevPictoBox = hasPictoBox;
static bool prevIronBoots = hasIronBoots;
static bool prevMagicArmor = hasMagicArmor;
static bool prevBaitBag = hasBaitBag;
static bool prevHerosBow = hasHerosBow;
static bool prevBombs = hasBombs;
static bool prevBottle1 = hasBottle1;
static bool prevBottle2 = hasBottle2;
static bool prevBottle3 = hasBottle3;
static bool prevBottle4 = hasBottle4;
static bool prevDeliveryBag = hasDeliveryBag;
static bool prevHookshot = hasHookshot;
static bool prevSkullHammer = hasSkullHammer;
static bool prevPowerBracelet = hasPowerBracelet;

static int currentBow = 0;
static const char* bows[] = { "No Bow", "Hero's Bow", "Fire & Ice Arrows", "Light Arrows" };

static int currentPicto = 0;
static const char* picto[] = { "No PictoBox", "PictoBox", "Deluxe PictoBox" };

static int currentSword = 0;
static const char* swords[] = { "No Sword", "Hero's Sword", "Master Sword", "Master Sword (Half Restored)", "Master Sword (Full Restored)"};

static int currentShield = 0;
static const char* shields[] = { "No Shield", "Hero's Shield", "Mirror Shield" };

static int currentBottle1 = 0;
static const char* bottle1Contents[] = { "No Bottle", "Empty Bottle", "Red Potion", "Green Potion", "Blue Potion", "Soup (Half)", "Soup", "Water", "Fairy", "Fire Fly", "Magic Water" };

static int currentBottle2 = 0;
static const char* bottle2Contents[] = { "No Bottle", "Empty Bottle", "Red Potion", "Green Potion", "Blue Potion", "Soup (Half)", "Soup", "Water", "Fairy", "Fire Fly", "Magic Water" };

static int currentBottle3 = 0;
static const char* bottle3Contents[] = { "No Bottle", "Empty Bottle", "Red Potion", "Green Potion", "Blue Potion", "Soup (Half)", "Soup", "Water", "Fairy", "Fire Fly", "Magic Water" };

static int currentBottle4 = 0;
static const char* bottle4Contents[] = { "No Bottle", "Empty Bottle", "Red Potion", "Green Potion", "Blue Potion", "Soup (Half)", "Soup", "Water", "Fairy", "Fire Fly", "Magic Water" };
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
    DZ_InventoryEditWindow_UpdateItems();
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
    ImGui::SetNextWindowSize(ImVec2(500, 350), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("DZ: Inventory Editor", nullptr))
    {
        ImGui::Columns(3, nullptr, true);

        ImGui::Checkbox("Telescope", &hasTelescope);
        ImGui::NextColumn();
        ImGui::Checkbox("Wind Waker", &hasWindWaker);
        ImGui::NextColumn();
        ImGui::Checkbox("Grappling Hook", &hasGrapplingHook);

        ImGui::NextColumn();
        ImGui::Checkbox("Spoils Bag", &hasSpoilsBag);
        ImGui::NextColumn();
        ImGui::Checkbox("Boomerang", &hasBoomerang);
        ImGui::NextColumn();
        ImGui::Checkbox("Deku Leaf", &hasDekuLeaf);

        ImGui::NextColumn();
        ImGui::Checkbox("Tingle Bottle", &hasTingleBottle);
        ImGui::NextColumn();
        ImGui::Checkbox("Iron Boots", &hasIronBoots);
        ImGui::NextColumn();
        ImGui::Checkbox("Magic Armor", &hasMagicArmor);

        ImGui::NextColumn();
        ImGui::Checkbox("Bait Bag", &hasBaitBag);
        ImGui::NextColumn();
        ImGui::Checkbox("Delivery Bag", &hasDeliveryBag);
        ImGui::NextColumn();
        ImGui::Checkbox("Hookshot", &hasHookshot);

        ImGui::NextColumn();
        ImGui::Checkbox("Bombs", &hasBombs);
        ImGui::NextColumn();
        ImGui::Checkbox("Skull Hammer", &hasSkullHammer);
        ImGui::NextColumn();
        ImGui::Checkbox("Power Bracelets", &hasPowerBracelet);

        ImGui::Columns(1);

        if (ImGui::Combo("Bow", &currentBow, bows, IM_ARRAYSIZE(bows)))
        {
            DZ_InventoryEditWindow_ChangeBow(currentBow);
        }

        if (ImGui::Combo("PictoBox", &currentPicto, picto, IM_ARRAYSIZE(picto)))
        {
            DZ_InventoryEditWindow_ChangePicto(currentPicto);
        }

        ImGui::Separator();
        ImGui::Spacing();

        if (ImGui::Combo("Sword", &currentSword, swords, IM_ARRAYSIZE(swords)))
        {
            DZ_InventoryEditWindow_ChangeSwords(currentSword);
        }

        if (ImGui::Combo("Shield", &currentShield, shields, IM_ARRAYSIZE(shields)))
        {
            DZ_InventoryEditWindow_ChangeShields(currentShield);
        }
        ImGui::Spacing();

        ImGui::Separator();
        ImGui::Spacing();

        if (ImGui::Combo("Bottle 1", &currentBottle1, bottle1Contents, IM_ARRAYSIZE(bottle1Contents)))
        {
            DZ_InventoryEditWindow_ChangeBottle(currentBottle1, item_slots.bottle1.address);
        }

        if (ImGui::Combo("Bottle 2", &currentBottle2, bottle2Contents, IM_ARRAYSIZE(bottle2Contents)))
        {
            DZ_InventoryEditWindow_ChangeBottle(currentBottle2, item_slots.bottle2.address);
        }

        if (ImGui::Combo("Bottle 3", &currentBottle3, bottle3Contents, IM_ARRAYSIZE(bottle3Contents)))
        {
            DZ_InventoryEditWindow_ChangeBottle(currentBottle3, item_slots.bottle3.address);
        }

        if (ImGui::Combo("Bottle 4", &currentBottle4, bottle4Contents, IM_ARRAYSIZE(bottle4Contents)))
        {
            DZ_InventoryEditWindow_ChangeBottle(currentBottle4, item_slots.bottle4.address);
        }
    }
}

void DZ_InventoryEditWindow_UpdateItems()
{
    if (hasTelescope != prevTelescope)
        DZ_FlopInventory(hasTelescope, prevTelescope, item_slots.telescope.address, items.telescope.value);
    if (hasWindWaker != prevWindWaker)
        DZ_FlopInventory(hasWindWaker, prevWindWaker, item_slots.wind_waker.address, items.wind_waker.value);
    if (hasGrapplingHook != prevGrapplingHook)
        DZ_FlopInventory(hasGrapplingHook, prevGrapplingHook, item_slots.grappling_hook.address, items.grappling_hook.value);
    if (hasSpoilsBag != prevSpoilsBag)
        DZ_FlopInventory(hasSpoilsBag, prevSpoilsBag, item_slots.spoils_bag.address, items.spoils_bag.value);
    if (hasBoomerang != prevBoomerang)
        DZ_FlopInventory(hasBoomerang, prevBoomerang, item_slots.boomerang.address, items.boomerang.value);
    if (hasDekuLeaf != prevDekuLeaf)
        DZ_FlopInventory(hasDekuLeaf, prevDekuLeaf, item_slots.deku_leaf.address, items.deku_leaf.value);
    if (hasTingleBottle != prevTingleBottle)
        DZ_FlopInventory(hasTingleBottle, prevTingleBottle, item_slots.tingle_bottle.address, items.tingle_bottle.value);
    if (hasIronBoots != prevIronBoots)
        DZ_FlopInventory(hasIronBoots, prevIronBoots, item_slots.iron_boots.address, items.iron_boots.value);
    if (hasMagicArmor != prevMagicArmor)
        DZ_FlopInventory(hasMagicArmor, prevMagicArmor, item_slots.magic_armor.address, items.magic_armor.value);
    if (hasBaitBag != prevBaitBag)
        DZ_FlopInventory(hasBaitBag, prevBaitBag, item_slots.bait_bag.address, items.bait_bag.value);
    if (hasDeliveryBag != prevDeliveryBag)
        DZ_FlopInventory(hasDeliveryBag, prevDeliveryBag, item_slots.delivery_bag.address, items.delivery_bag.value);
    if (hasHookshot != prevHookshot)
        DZ_FlopInventory(hasHookshot, prevHookshot, item_slots.hookshot.address, items.hookshot.value);
    if (hasBombs != prevBombs)
        DZ_FlopInventory(hasBombs, prevBombs, item_slots.bombs.address, items.bombs.value);
    if (hasSkullHammer != prevSkullHammer)
        DZ_FlopInventory(hasSkullHammer, prevSkullHammer, item_slots.skull_hammer.address, items.skull_hammer.value);
    if (hasPowerBracelet != prevPowerBracelet)
        DZ_FlopInventory(hasPowerBracelet, prevPowerBracelet, quest_status.power_bracelets.address, items.power_bracelets.value);
}

void DZ_InventoryEditWindow_ChangeSwords(int index)
{
    switch (index)
    {
        case 0: //No Sword
            gecko->poke8(equipment.sword.address, items.empty_slot.value);
            break;
        case 1: //Hero's Sword
            gecko->poke8(equipment.sword.address, items.heros_sword.value);
            break;
        case 2: //Master Sword
            gecko->poke8(equipment.sword.address, items.master_sword.value);
            break;
        case 3: //Master Sword Half
            gecko->poke8(equipment.sword.address, items.master_sword_half_restored.value);
            break;
        case 4: //Master Sword Full
            gecko->poke8(equipment.sword.address, items.master_sword_full_restored.value);
            break;
    }
}

void DZ_InventoryEditWindow_ChangeBow(int index)
{
    switch (index)
    {
        case 0:
            gecko->poke8(item_slots.heros_bow.address, items.empty_slot.value);
            break;
        case 1:
            gecko->poke8(item_slots.heros_bow.address, items.heros_bow.value);
            break;
        case 2:
            gecko->poke8(item_slots.heros_bow.address, items.fire_ice_arrows.value);
            break;
        case 3:
            gecko->poke8(item_slots.heros_bow.address, items.light_arrows.value);
            break;
    }
}

void DZ_InventoryEditWindow_ChangeShields(int index)
{
    switch (index)
    {
        case 0:
            gecko->poke8(equipment.shield.address, items.empty_slot.value);
            break;
        case 1:
            gecko->poke8(equipment.shield.address, items.heros_shield.value);
            break;
        case 2:
            gecko->poke8(equipment.shield.address, items.mirror_shield.value);
            break;
    }
}

void DZ_InventoryEditWindow_ChangePicto(int index)
{
    switch (index)
    {
        case 0:
            gecko->poke8(item_slots.picto_box.address, items.empty_slot.value);
            break;
        case 1:
            gecko->poke8(item_slots.picto_box.address, items.pictobox.value);
            break;
        case 2:
            gecko->poke8(item_slots.picto_box.address, items.deluxe_pictobox.value);
            break;
    }
}

void DZ_InventoryEditWindow_ChangeBottle(int index, uint32_t slot)
{
    switch (index)
    {
        case 0:
            gecko->poke8(slot, items.empty_slot.value);
            break;
        case 1:
            gecko->poke8(slot, items.bottle_1.value);
            break;
        case 2:
            gecko->poke8(slot, items.red_potion.value);
            break;
        case 3:
            gecko->poke8(slot, items.green_potion.value);
            break;
        case 4:
            gecko->poke8(slot, items.blue_potion.value);
            break;
        case 5:
            gecko->poke8(slot, items.soup_half.value);
            break;
        case 6:
            gecko->poke8(slot, items.soup.value);
            break;
        case 7:
            gecko->poke8(slot, items.water.value);
            break;
        case 8:
            gecko->poke8(slot, items.fairy.value);
            break;
        case 9:
            gecko->poke8(slot, items.fire_fly.value);
            break;
        case 10:
            gecko->poke8(slot, items.magic_water.value);
            break;
    }
}

void DZ_FlopInventory(bool checkBox, bool& prevState, uint32_t slot, uint8_t value)
{
    if (checkBox)
        gecko->poke8(slot, value);
    else
    {
        if (slot == quest_status.power_bracelets.address)
        {
            gecko->poke8(slot, 0x00);
        }
        else 
        {
            gecko->poke8(slot, 0xFF);
        }
    }
        

    prevState = checkBox;
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

    hasPowerBracelet = gecko->peekmem8(quest_status.power_bracelets.address) != 0x00;

    uint32_t swordVal = gecko->peekmem8(equipment.sword.address);
    if (swordVal == items.empty_slot.value)
        currentSword = 0;
    else if (swordVal == items.heros_sword.value)
        currentSword = 1;
    else if (swordVal == items.master_sword.value)
        currentSword = 2;
    else if (swordVal == items.master_sword_half_restored.value)
        currentSword = 3;
    else if (swordVal == items.master_sword_full_restored.value)
        currentSword = 4;

    uint32_t shieldVal = gecko->peekmem8(equipment.shield.address);
    if (shieldVal == items.empty_slot.value)
        currentShield = 0;
    else if (shieldVal == items.heros_shield.value)
        currentShield = 1;
    else if (shieldVal == items.mirror_shield.value)
        currentShield = 2;

    uint32_t pictoVal = gecko->peekmem8(item_slots.picto_box.address);
    if (pictoVal == items.empty_slot.value)
        currentPicto = 0;
    else if (pictoVal == items.pictobox.value)
        currentPicto = 1;
    else if (pictoVal == items.deluxe_pictobox.value)
        currentPicto = 2;

    uint32_t bowVal = gecko->peekmem8(item_slots.heros_bow.address);
    if (bowVal == items.empty_slot.value)
        currentBow = 0;
    else if (bowVal == items.heros_bow.value)
        currentBow = 1;
    else if (bowVal == items.fire_ice_arrows.value)
        currentBow = 2;
    else if (bowVal == items.light_arrows.value)
        currentBow = 3;

    uint32_t bottle1Val = gecko->peekmem8(item_slots.bottle1.address);
    if (bottle1Val == items.empty_slot.value)
        bottle1Val = 0;
    else if (bottle1Val == items.bottle_1.value)
        bottle1Val = 1;
    else if (bottle1Val == items.red_potion.value)
        bottle1Val = 2;
    else if (bottle1Val == items.green_potion.value)
        bottle1Val = 3;
    else if (bottle1Val == items.blue_potion.value)
        bottle1Val = 4;
    else if (bottle1Val == items.soup_half.value)
        bottle1Val = 5;
    else if (bottle1Val == items.soup.value)
        bottle1Val = 6;
    else if (bottle1Val == items.water.value)
        bottle1Val = 7;
    else if (bottle1Val == items.fairy.value)
        bottle1Val = 8;
    else if (bottle1Val == items.fire_fly.value)
        bottle1Val = 9;
    else if (bottle1Val == items.magic_water.value)
        bottle1Val = 10;

    uint32_t bottle2Val = gecko->peekmem8(item_slots.bottle2.address);
    if (bottle2Val == items.empty_slot.value)
        bottle2Val = 0;
    else if (bottle2Val == items.bottle_2.value)
        bottle2Val = 1;
    else if (bottle2Val == items.red_potion.value)
        bottle2Val = 2;
    else if (bottle2Val == items.green_potion.value)
        bottle2Val = 3;
    else if (bottle2Val == items.blue_potion.value)
        bottle2Val = 4;
    else if (bottle2Val == items.soup_half.value)
        bottle2Val = 5;
    else if (bottle2Val == items.soup.value)
        bottle2Val = 6;
    else if (bottle2Val == items.water.value)
        bottle2Val = 7;
    else if (bottle2Val == items.fairy.value)
        bottle2Val = 8;
    else if (bottle2Val == items.fire_fly.value)
        bottle2Val = 9;
    else if (bottle2Val == items.magic_water.value)
        bottle2Val = 10;

    uint32_t bottle3Val = gecko->peekmem8(item_slots.bottle3.address);
    if (bottle3Val == items.empty_slot.value)
        bottle3Val = 0;
    else if (bottle3Val == items.bottle_1.value)
        bottle3Val = 1;
    else if (bottle3Val == items.red_potion.value)
        bottle3Val = 2;
    else if (bottle3Val == items.green_potion.value)
        bottle3Val = 3;
    else if (bottle3Val == items.blue_potion.value)
        bottle3Val = 4;
    else if (bottle3Val == items.soup_half.value)
        bottle3Val = 5;
    else if (bottle3Val == items.soup.value)
        bottle3Val = 6;
    else if (bottle3Val == items.water.value)
        bottle3Val = 7;
    else if (bottle3Val == items.fairy.value)
        bottle3Val = 8;
    else if (bottle3Val == items.fire_fly.value)
        bottle3Val = 9;
    else if (bottle3Val == items.magic_water.value)
        bottle3Val = 10;

    uint32_t bottle4Val = gecko->peekmem8(item_slots.bottle4.address);
    if (bottle4Val == items.empty_slot.value)
        bottle4Val = 0;
    else if (bottle4Val == items.bottle_1.value)
        bottle4Val = 1;
    else if (bottle4Val == items.red_potion.value)
        bottle4Val = 2;
    else if (bottle4Val == items.green_potion.value)
        bottle4Val = 3;
    else if (bottle4Val == items.blue_potion.value)
        bottle4Val = 4;
    else if (bottle4Val == items.soup_half.value)
        bottle4Val = 5;
    else if (bottle4Val == items.soup.value)
        bottle4Val = 6;
    else if (bottle4Val == items.water.value)
        bottle4Val = 7;
    else if (bottle4Val == items.fairy.value)
        bottle4Val = 8;
    else if (bottle4Val == items.fire_fly.value)
        bottle4Val = 9;
    else if (bottle4Val == items.magic_water.value)
        bottle4Val = 10;

    prevTelescope = hasTelescope;
    prevWindWaker = hasWindWaker;
    prevGrapplingHook = hasGrapplingHook;
    prevSpoilsBag = hasSpoilsBag;
    prevBoomerang = hasBoomerang;
    prevDekuLeaf = hasDekuLeaf;
    prevTingleBottle = hasTingleBottle;
    prevPictoBox = hasPictoBox;
    prevIronBoots = hasIronBoots;
    prevMagicArmor = hasMagicArmor;
    prevBaitBag = hasBaitBag;
    prevHerosBow = hasHerosBow;
    prevBombs = hasBombs;
    prevBottle1 = hasBottle1;
    prevBottle2 = hasBottle2;
    prevBottle3 = hasBottle3;
    prevBottle4 = hasBottle4;
    prevDeliveryBag = hasDeliveryBag;
    prevHookshot = hasHookshot;
    prevSkullHammer = hasSkullHammer;
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
