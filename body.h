#ifndef body_h
#define body_h
#include <iostream>
#include <SDL2/SDL.h>
#include "gfx.h"

class Body {
	public:
		Body();
		void drawBody();
		SDL_Rect bodyRect = {0, 0, 18, 24};
		SDL_Texture* bodyTexture;
	private:

};
#endif
