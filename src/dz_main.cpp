#include "../include/dz.h"
#include "../include/Drawing.h"
#include "../include/tcpgecko.h"
#include <future>
#include <string>

static TCPGecko* gecko = nullptr;
static bool isConnected = false;
static char ipBuffer[16] = "192.168.4.57";
static const char* connectionStatus = "Status: Awaiting Connection...";
static const char* connectButton = "Connect";

//Watches
struct watchesWindow_Watch {
	uint32_t address;
	std::string type;
	std::string name;
};

struct watchesWindow_WatchValue {
	std::future<std::uint32_t> future;
	std::uint32_t lastKnown;
};
std::map<uint32_t, watchesWindow_WatchValue> watchValues;

std::vector<watchesWindow_Watch> watchesWindow_watches;

char watchesWindow_addressInputBuffer[128];
char watchesWindow_nameInputBuffer[128];
const char* watchesWindow_variableTypes[] = { "Int", "Float", "Double", "String", "Bool" };
int watchesWindow_currentTypeIndex = 0;
static bool watchesWindow_show = false;

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
	if (ImGui::Button("Watches"))
		watchesWindow_show = !watchesWindow_show;
	if (watchesWindow_show)
	{
		DZ_DrawWatchesWindow();
	}

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

void DZ_DrawWatchesWindow()
{
	ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
	if (ImGui::Begin("DZ: Watches", &watchesWindow_show)) {

		ImGui::InputText("Name", watchesWindow_nameInputBuffer, IM_ARRAYSIZE(watchesWindow_nameInputBuffer));
		ImGui::InputText("Address (hex)", watchesWindow_addressInputBuffer, IM_ARRAYSIZE(watchesWindow_addressInputBuffer));
		ImGui::Combo("Value Type", &watchesWindow_currentTypeIndex, watchesWindow_variableTypes, IM_ARRAYSIZE(watchesWindow_variableTypes));

		if (ImGui::Button("Add Watch") && watchesWindow_addressInputBuffer[0] != '\0' && watchesWindow_nameInputBuffer[0] != '\0') {
			try {
				uint32_t address = StringToUint32(watchesWindow_addressInputBuffer);
				watchesWindow_watches.push_back({ address, watchesWindow_variableTypes[watchesWindow_currentTypeIndex], watchesWindow_nameInputBuffer });
				watchesWindow_addressInputBuffer[0] = '\0'; // Clear the address buffer after adding
				watchesWindow_nameInputBuffer[0] = '\0';    // Clear the name buffer after adding
			}
			catch (const std::invalid_argument& ia) {
				// Handle invalid input (non-hexadecimal input)
			}
			catch (const std::out_of_range& oor) {
				// Handle out of range input
			}
		}

		ImGui::Separator();

		if (!watchesWindow_watches.empty()) {
			ImGui::BeginChild("Watches List", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), true);

			for (size_t i = 0; i < watchesWindow_watches.size(); ) {
				const auto& watch = watchesWindow_watches[i];
				ImGui::PushID(i); // Ensure unique ID for widgets
				ImGui::Text("%s:", watchesWindow_watches[i].name.c_str());
				ImGui::SameLine();

				FetchValueAsync(watch.address);
				UpdateValue(watch.address);

				// Retrieve the watch value.
				const auto& watchValue = watchValues[watch.address];
				if (watchValue.future.valid()) {
					ImGui::Text("Value: %u", watchValue.lastKnown);
				}
				else {
					ImGui::Text("Value: Loading...");
				}

				ImGui::SameLine();
				if (ImGui::Button("Delete")) {
					watchesWindow_watches.erase(watchesWindow_watches.begin() + i);
					// Do not increment 'i' as the current item is removed
				}
				else {
					++i; // Only increment 'i' if the current item was not removed
				}
				ImGui::PopID();
			}

			ImGui::EndChild();
		}
	}
	ImGui::End();
}

void DZ_DisposeMainWindow()
{
	if (gecko)
		DZ_GeckoDisconnect();
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

void FetchValueAsync(uint32_t address)
{
	// Initialize the future object for this address if not already fetching.
	auto& watchValue = watchValues[address];
	if (!watchValue.future.valid()) { // Start the fetch only if it's not already fetching.
		watchValue.future = std::async(std::launch::async, [address] {
			return gecko->peekmem(address);
			});
	}
}

void UpdateValue(uint32_t address)
{
	auto& watchValue = watchValues[address];
	if (watchValue.future.valid() &&
		watchValue.future.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
		// The future is ready, get the result and update lastKnown.
		watchValue.lastKnown = watchValue.future.get();
	}
}
