#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "go.h"
#include <windows.h>

void kb_press(WORD key) {
  INPUT input = {0};
  input.type = INPUT_KEYBOARD;
  input.ki.wVk = key;
  SendInput(1, &input, sizeof(INPUT));
}

void kb_release(WORD key) {
  INPUT input = {0};
  input.type = INPUT_KEYBOARD;
  input.ki.wVk = key;
  input.ki.dwFlags = KEYEVENTF_KEYUP;
  SendInput(1, &input, sizeof(INPUT));
}

void m_l_click() {
  INPUT input = {0};
  input.type = INPUT_MOUSE;
  input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
  SendInput(1, &input, sizeof(INPUT));
  Sleep(100);
  input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
  SendInput(1, &input, sizeof(INPUT));
}

void m_r_click() {
  INPUT input = {0};
  input.type = INPUT_MOUSE;
  input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
  SendInput(1, &input, sizeof(INPUT));
  Sleep(100);
  input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
  SendInput(1, &input, sizeof(INPUT));
}

int main(int argc, char **argv) {
  HDC hDC;
  hDC = GetDC(NULL);
  COLORREF color;

  struct {
    u_int x;
    u_int y;
  } screen;

  screen.x = 1920;
  screen.y = 1080;

  int scan_x = (screen.x / 2) - 2;
  int scan_y = (screen.y / 2) - 2;

  double d_t;

  while (1) {

    clock_t start_time = clock();

		if(scan_x == (screen.x / 2) - 2){
			scan_x == (screen.x / 2) + 2;
			scan_y == (screen.y / 2) + 2;
		} else {
			scan_x = (screen.x / 2) - 2;
			scan_y = (screen.y / 2) - 2;
		}

    color = GetPixel(hDC, scan_x, scan_y);

    if(GetRValue(color) > 110 && GetGValue(color) < 60 && GetBValue(color) < 60){
      m_l_click();
      Sleep(90);
    }

    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
      break;

    Sleep(1);

    d_t = (double)(clock() - start_time) / CLOCKS_PER_SEC;

    printf("\rd_t: %fms", d_t);
  }

  ReleaseDC(NULL, hDC);
  return 0;
}
