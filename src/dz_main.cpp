#include "../include/dz.h"
#include "Drawing.h"
#include "tcpgecko.h"

static TCPGecko* gecko = nullptr;
static bool isConnected = false;
static char ipBuffer[16] = "192.168.0.0";
static const char* connectionStatus = "Awaiting Connection...";
void DZ_GeckoConnect(std::string wiiuip)
{
	connectionStatus = "Attempting Connection...";
	if (gecko) //Make sure there's no repeat connections
	{
		gecko->Disconnect();
		delete gecko;
		gecko = nullptr;
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

void DZ_DrawMainWindow()
{
	ImGui::Text(connectionStatus);
	ImGui::InputText("Wii U IP:", ipBuffer, IM_ARRAYSIZE(ipBuffer));
	if (ImGui::Button("Connect"))
	{
		DZ_GeckoConnect(std::string(ipBuffer));
	}

	if (isConnected) 
	{
		ImGui::Text("Status: Connected");
	}
	else 
	{
		ImGui::Text("Status: Not Connected");
	}

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}