#include "renderer.h"

Renderer::Renderer()
{
	factory = NULL;
	renderTarget = NULL;
}

Renderer::~Renderer()
{
	if (factory)
	{
		factory->Release();
	}
	if (renderTarget)
	{
		renderTarget->Release();
	}
}

bool Renderer::Init(HWND hWnd)
{
	if (D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory) == S_OK)
	{
		RECT clientRect;
		GetClientRect(hWnd, &clientRect);
		if (factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top)), &renderTarget) == S_OK)
		{
			return true;
		}
	}
	return false;
}

void Renderer::BeginDraw()
{
	if (renderTarget)
	{
		renderTarget->BeginDraw();
	}
}

void Renderer::EndDraw()
{
	if (renderTarget)
	{
		renderTarget->EndDraw();
	}
}

void Renderer::ClearScreen(D2D1_COLOR_F color)
{
	if (renderTarget)
	{
		renderTarget->Clear(color);
	}
}

void Renderer::DrawCircle(float x, float y, float rad, ID2D1Brush* innerBrush, ID2D1Brush* outerBrush)
{
	if (renderTarget)
	{
		D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2F(x, y), rad, rad);
		renderTarget->DrawEllipse(ellipse, outerBrush, 3);
		renderTarget->FillEllipse(ellipse, innerBrush);
	}
}

ID2D1SolidColorBrush* Renderer::GetSolidBrush(D2D1_COLOR_F color)
{
	if (renderTarget)
	{
		ID2D1SolidColorBrush* brush;
		if (renderTarget->CreateSolidColorBrush(color, &brush) == S_OK)
		{
			return brush;
		}
	}
	return NULL;
}

D2D1_SIZE_U Renderer::GetSize()
{
	if (renderTarget)
	{
		return renderTarget->GetPixelSize();
	}
	return D2D1::SizeU(0, 0);
}