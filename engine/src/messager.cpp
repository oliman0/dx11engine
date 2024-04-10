#include "messager.h"

int ShowMessageBox(LPCWSTR text, LPCWSTR title, UINT type) { return MessageBox(NULL, text, title, type); }

void ShowErrorBoxRepeat(LPCWSTR text, LPCWSTR title) {
    int res = IDRETRY;
    while (res == IDRETRY) res = MessageBox(NULL, text, title, MB_ICONERROR | MB_RETRYCANCEL);
}

int ShowErrorBox(LPCWSTR text, LPCWSTR title) {
    int res = MessageBox(NULL, text, title, MB_ICONERROR | MB_RETRYCANCEL);

    return res;
}