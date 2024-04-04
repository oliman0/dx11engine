#include "messager.h"

Messager::Messager() { GlobalMessager = this; }
Messager::~Messager() { GlobalMessager = 0; }

int Messager::ShowMessageBox(LPCWSTR text, LPCWSTR title, UINT type) { return MessageBox(NULL, text, title, type); }

void Messager::ShowErrorBoxRepeat(LPCWSTR text, LPCWSTR title) {
    int res = IDRETRY;
    while (res == IDRETRY) res = MessageBox(NULL, text, title, MB_ICONERROR | MB_RETRYCANCEL);
}

int Messager::ShowErrorBox(LPCWSTR text, LPCWSTR title) {
    int res = MessageBox(NULL, text, title, MB_ICONERROR | MB_RETRYCANCEL);

    return res;
}

Messager* GetMessager() { return GlobalMessager; }