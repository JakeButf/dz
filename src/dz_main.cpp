#include "../include/dz.h"
#include "../include/Drawing.h"
#include "../include/tcpgecko.h"
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

//watches
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

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

void DZ_DisposeMainWindow()
{
	if (gecko)
		DZ_GeckoDisconnect();
}

void DZ_DrawDebugWindow()
{
    static char debugAddressInput[128] = "";
    static const char* debugSizes[] = { "First 8 bits", "First 16 bits", "Last 8 bits", "Last 16 bits", "32 bits" };
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
                debugValue = gecko->peekmem(address);
            }
        }

        // Display the peeked value in different formats
        ImGui::Separator();
        uint8_t firstByte = static_cast<uint8_t>((debugValue >> 24) & 0xFF);
        uint16_t firstTwoBytes = static_cast<uint16_t>((debugValue >> 16) & 0xFFFF);
        uint8_t lastByte = static_cast<uint8_t>(debugValue & 0xFF);
        uint16_t lastTwoBytes = static_cast<uint16_t>(debugValue & 0xFFFF);

        switch (currentDebugSize) {
        case 0: // First 8 bits
            ImGui::Text("INT: %d", firstByte);
            ImGui::Text("HEX: 0x%02X", firstByte);
            ImGui::Text("STRING: %c", static_cast<char>(firstByte));
            break;
        case 1: // First 16 bits
            ImGui::Text("INT: %d", firstTwoBytes);
            ImGui::Text("HEX: 0x%04X", firstTwoBytes);
            // Convert to ASCII characters if applicable
            break;
        case 2: // Last 8 bits
            ImGui::Text("INT: %d", lastByte);
            ImGui::Text("HEX: 0x%02X", lastByte);
            ImGui::Text("STRING: %c", static_cast<char>(lastByte));
            break;
        case 3: // Last 16 bits
            ImGui::Text("INT: %d", lastTwoBytes);
            ImGui::Text("HEX: 0x%04X", lastTwoBytes);
            // Convert to ASCII characters if applicable
            break;
        case 4: // 32 bits
            // Display as 32-bit integer, hex, and string (if applicable)
            ImGui::Text("INT: %d", static_cast<int>(debugValue));
            ImGui::Text("HEX: 0x%08X", debugValue);
            char str[5] = {
                static_cast<char>((debugValue >> 24) & 0xFF),
                static_cast<char>((debugValue >> 16) & 0xFF),
                static_cast<char>((debugValue >> 8) & 0xFF),
                static_cast<char>(debugValue & 0xFF),
                '\0'
            };
            ImGui::Text("STRING: %s", str);
            break;
        }
    }
    ImGui::End();
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
