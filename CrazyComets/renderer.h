#ifndef RENDERER_H
#define RENDERER_H
#include <d2d1.h>

class Renderer
{
	private:
		ID2D1Factory* factory;
		ID2D1HwndRenderTarget* renderTarget;
	public:
		Renderer();
		~Renderer();
		bool Init(HWND hWnd);
		void BeginDraw();
		void EndDraw();
		void ClearScreen(D2D1_COLOR_F color);
		void DrawCircle(float x, float y, float rad, ID2D1Brush* innerBrush, ID2D1Brush* outerBrush);
		ID2D1SolidColorBrush* GetSolidBrush(D2D1_COLOR_F color);
		D2D1_SIZE_U GetSize();
};

#endif