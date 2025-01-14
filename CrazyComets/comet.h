#ifndef COMET_H
#define COMET_H
#include "renderer.h"
#include "cometconf.h"


class Comet
{
	private:
		Renderer* renderer;
		ID2D1SolidColorBrush* outerBrush;
		ID2D1SolidColorBrush* innerBrush;
	public:
		float x;
		float y;
		float rad;
		float xVel;
		float yVel;
		Comet(float x, float y, float xVel, float yVel, float rad, D2D1_COLOR_F innerColor, D2D1_COLOR_F outerColor, Renderer* renderer);
		Comet(Renderer* renderer);
		~Comet();
		void Draw();
		void Update(int millisecondsSinceLast);
		float Distance(Comet* other);
};

void InitCometArray();
void AddComet(Comet* newComet);
void RemoveComet(Comet* oldComet);
void DrawComets();
void UpdateComets();
void AddRandomComets(int cometCount, Renderer* renderer);
void HandleCollisions();

#endif
