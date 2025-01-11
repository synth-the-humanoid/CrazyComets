#include <windows.h>
#include "comet.h"


LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

Renderer* renderer = new Renderer();

// controls
bool shouldClear = true;
int cometCount = 10;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	WNDCLASSEX windowClass;
	memset(&windowClass, 0, sizeof(WNDCLASSEX));
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.hInstance = hInstance;
	windowClass.lpszClassName = L"Comets";
	windowClass.lpszMenuName = L"Comets";
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.style = CS_VREDRAW | CS_HREDRAW;

	if (RegisterClassEx(&windowClass))
	{
		HWND hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"Comets", L"Comets", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
		if (hWnd)
		{
			renderer->Init(hWnd);
			InitCometArray();
			srand(GetTickCount());

			AddRandomComets(cometCount, renderer);
			ShowWindow(hWnd, nCmdShow);
			MSG message;
			while (GetMessage(&message, NULL, 0, 0))
			{
				DispatchMessage(&message);
			}
			return 0;
		}
	}

	return GetLastError();
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_PAINT:
			
			renderer->BeginDraw();
			if (shouldClear)
			{
				renderer->ClearScreen(D2D1::ColorF(0, 0, 0, 1));
			}
			DrawComets();
			HandleCollisions();
			UpdateComets();
			renderer->EndDraw();
			return 0;
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}