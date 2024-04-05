// messager.h
// Gobal Class that allows for Error Message Boxes

#pragma once

#include <windows.h>


int ShowMessageBox(LPCWSTR text, LPCWSTR title, UINT type);

void ShowErrorBoxRepeat(LPCWSTR text, LPCWSTR title);
int ShowErrorBox(LPCWSTR text, LPCWSTR title);