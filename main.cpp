/** Main.cpp controls lib.h for a simple
 *  Gfx example and Audio example.
 */

#include "gfx.h" // general gfx lib I made for SDL
#include "input.h"
#include "general.h"
#include "body.h"
#include <iostream>
#define screenw 640
#define screenh 640//480

const int numBodies = 4;
const double timeStep = 5e4;//1e8;

void addForces(Body inputBodies[]) {
	for (int i = 0; i < numBodies; i++) {
		inputBodies[i].resetForce();
		for (int j = 0; j < numBodies; j++) {
			if (i != j) inputBodies[i].addForce(inputBodies[j]);
		}	
	}

	for (int i = 0; i < numBodies; i++) {
		inputBodies[i].update(timeStep); //Update with Timestep
		inputBodies[i].drawBody(screenw, screenh, 0, 0, 5e8*1000, 5e8*1000);
	}	
}

int main ( int argc, char** argv ) {
	gfx::gfxinit(screenw, screenh); // open window with 640x480 res. 

	Body bodies[numBodies] = {{1.496e11, 0, 0, 29783, 5.972e24, gfx::createTexture("./gfx/earth.bmp"), 32, 32},
                                  {1.639e11, 1.583e11, -16762, 17358, 6.39e23, gfx::createTexture("./gfx/mars.bmp"), 25, 25},
                                  {0, 0, 0, 0, 1.989e30, gfx::createTexture("./gfx/sun.bmp"), 100, 100},
                                  {1.505e11, 0, 0, 32730, 500, gfx::createTexture("./gfx/sun.bmp"), 5, 5}};

	/* program main loop */
	while (!(input::getKeyState(SDLK_ESCAPE) || input::getQuit())) {
		gfx::clearScreen(0, 0, 0);

		//Main Logic
		addForces(bodies);

		/*for (int i = 0; i < numBodies; i++) {
			bodies[i].drawBody(screenw, screenh, 0, 0, 5e8*1000, 5e8*1000:);
		}*/	
		//End Main Logic
		//SDL_Delay(1);
		gfx::update();
}

	gfx::close();

	return 0; // return success!
}
