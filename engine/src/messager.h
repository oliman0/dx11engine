// messager.h
// Gobal Class that allows for Error Message Boxes

#pragma once

#include <windows.h>

class Messager
{
public:
	Messager();
	~Messager();

	int ShowMessageBox(LPCWSTR text, LPCWSTR title, UINT type);

	void ShowErrorBoxRepeat(LPCWSTR text, LPCWSTR title);
	int ShowErrorBox(LPCWSTR text, LPCWSTR title);
};

static Messager* GlobalMessager = 0;

Messager* GetMessager();