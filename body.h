#ifndef body_h
#define body_h
#include <iostream>
#include <SDL2/SDL.h>
#include "gfx.h"

class Body {
	public:
		Body(double rx, double ry, double vx, double vy, double mass);
		void drawBody();
		void update(double dt);
		double distanceTo(Body b);
		void resetForce();
		void addForce(Body b);

		SDL_Rect bodyRect = {0, 0, 32, 32};
		SDL_Texture* bodyTexture;

		double rx, ry; //coords
		double vx, vy; //velocity
		double fx, fy; //force
		double mass;
	private:
		const double G = 6.673e-11;
};
#endif
