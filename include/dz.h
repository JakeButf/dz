#ifndef DZ_H
#define DZ_H

#include <string>
#include <map>

void DZ_GeckoConnect(std::string wiiuip);
void DZ_GeckoDisconnect();
void DZ_DrawMainWindow();
void DZ_DisposeMainWindow();

void DZ_DrawWatchesWindow();

void FetchValueAsync(uint32_t address);
void UpdateValue(uint32_t address);

void uint32ToCharArray(uint32_t value, char* array);
uint32_t StringToUint32(const std::string& str);
#endif
