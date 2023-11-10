#ifndef DZ_H
#define DZ_H

#include <string>
#include <map>

#include "../include/tcpgecko.h"

void DZ_GeckoConnect(std::string wiiuip);
void DZ_GeckoDisconnect();
void DZ_DrawMainWindow();
void DZ_DisposeMainWindow();

void DZ_DrawDebugWindow();

void DZ_DrawInventoryEditWindow();
void DZ_InventoryEditWindow_CheckIfHasItems();
void DZ_FlopInventory(bool checkBox, bool& prevState, uint32_t slot, uint8_t value);
void DZ_InventoryEditWindow_UpdateItems();
void DZ_InventoryEditWindow_ChangeSwords(int index);
void DZ_InventoryEditWindow_ChangeShields(int index);
void DZ_InventoryEditWindow_ChangePicto(int index);
void DZ_InventoryEditWindow_ChangeBow(int index);
void DZ_InventoryEditWindow_ChangeBottle(int index, uint32_t slot);

void uint32ToCharArray(uint32_t value, char* array);
uint32_t StringToUint32(const std::string& str);
#endif
