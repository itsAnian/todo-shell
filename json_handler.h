#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include "cJSON.h"
void SaveJsonToFile(const char* filename, cJSON* json);
cJSON* ReadJsonFromFile(const char* filename);
cJSON* CreateObject(char* id, char* titel, char* description, char* flags[], int flagCount);

#endif
