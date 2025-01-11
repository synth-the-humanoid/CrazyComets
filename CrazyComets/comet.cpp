#include "comet.h"
#include <cmath>

D2D1_COLOR_F RandomColor()
{
	return D2D1::ColorF((rand() % 101) / 100.0, (rand() % 101) / 100.0, (rand() % 101) / 100.0, (rand() % 101) / 100.0);
}

Comet::Comet(float x, float y, float xVel, float yVel, float rad, D2D1_COLOR_F innerColor, D2D1_COLOR_F outerColor, Renderer* renderer)
{
	this->x = x;
	this->y = y;
	this->xVel = xVel;
	this->yVel = yVel;
	this->rad = rad;
	this->renderer = renderer;
	innerBrush = this->renderer->GetSolidBrush(innerColor);
	outerBrush = this->renderer->GetSolidBrush(outerColor);
}

Comet::Comet(Renderer* renderer)
{
	D2D1_SIZE_U screenSize = renderer->GetSize();
	x = rand() % (int)screenSize.width;
	y = rand() % (int)screenSize.height;
	xVel = (rand() % 3) + 1;
	yVel = (rand() % 3) + 1;
	rad = rand() % 21;
	this->renderer = renderer;
	innerBrush = this->renderer->GetSolidBrush(RandomColor());
	outerBrush = this->renderer->GetSolidBrush(RandomColor());
}

Comet::~Comet()
{
	if (innerBrush)
	{
		innerBrush->Release();
	}
	if (outerBrush)
	{
		outerBrush->Release();
	}
}

void Comet::Draw()
{
	if (renderer)
	{
		renderer->DrawCircle(x, y, rad, innerBrush, outerBrush);
	}
}

void Comet::Update(int milliSecondsSinceLast)
{
	D2D1_SIZE_U size = renderer->GetSize();
	if (x > size.width || x < 0)
	{
		xVel *= -1.01;
	}
	if (y > size.height || y < 0)
	{
		yVel *= -1.01;
	}
	float deltaTime = 1 + (1 / max(milliSecondsSinceLast, 1));
	x += (xVel * deltaTime);
	y += (yVel * deltaTime);
}


float Comet::Distance(Comet* other)
{
	float a = other->x - x;
	float b = other->y - y;
	a *= a;
	b *= b;
	float c = a + b;
	return sqrt(c);
}

Comet** comets;

void InitCometArray()
{
	comets = new Comet*[1];
	comets[0] = NULL;
}

void AddComet(Comet* newComet)
{
	int currentComets = 0;
	while (comets[currentComets])
	{
		currentComets++;
	}
	Comet** cometsClone = new Comet*[currentComets + 2];
	for (int i = 0; i < currentComets; i++)
	{
		cometsClone[i] = comets[i];
	}
	cometsClone[currentComets] = newComet;
	cometsClone[currentComets + 1] = NULL;
	delete comets;
	comets = cometsClone;
}

void RemoveComet(Comet* oldComet)
{
	for (int i = 0; comets[i]; i++)
	{
		if (comets[i] == oldComet)
		{
			for (int i2 = i + 1; comets[i2]; i2++)
			{
				comets[i++] = comets[i2];
			}
			comets[i] = NULL;
			return;
		}
	}
}

void DrawComets()
{
	for (int i = 0; comets[i]; i++)
	{
		comets[i]->Draw();
	}
}

int lastUpdate = 0;

void UpdateComets()
{
	int currentTick = GetTickCount();
	int delay = 0;
	if (lastUpdate)
	{
		delay = currentTick - lastUpdate;
	}
	lastUpdate = currentTick;
	for (int i = 0; comets[i]; i++)
	{
		comets[i]->Update(delay);
	}
}

void AddRandomComets(int cometCount, Renderer* renderer)
{
	for (int i = 0; i < cometCount; i++)
	{
		AddComet(new Comet(renderer));
	}
}



void HandleCollisions()
{
	for (int i = 0; comets[i]; i++)
	{
		for (int i2 = 0; comets[i2]; i2++)
		{
			if (i != i2)
			{
				if (comets[i]->Distance(comets[i2]) <= comets[i]->rad + comets[i2]->rad)
				{
					comets[i]->xVel *= -1;
					comets[i]->yVel *= -1;
					comets[i]->x += comets[i]->xVel;
					comets[i]->y += comets[i]->yVel;
					comets[i2]->xVel *= -1;
					comets[i2]->yVel *= -1;
					comets[i2]->x += comets[i2]->xVel;
					comets[i2]->y += comets[i2]->yVel;
				}
			}
		}
	}
}