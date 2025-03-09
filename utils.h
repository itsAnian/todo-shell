#ifndef UTILS_H
#define UTILS_H

#include "cJSON.h"
#include <stdbool.h>

void ThrowError(const char* message);
char* GetPath(bool history);
char* GenerateId(int length);
void PrintJsonObject(cJSON* obj);
void PrintJsonArray(cJSON* jsonArray);
void PrintHelp();

#endif
