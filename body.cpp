#include <iostream>
#include <SDL2/SDL.h>
#include "body.h"
#include "gfx.h"

Body::Body() {

}

void Body::drawBody() {
	gfx::drawTexture(bodyTexture, bodyRect);
}
