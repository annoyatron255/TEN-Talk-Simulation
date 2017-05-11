/** Main.cpp controls lib.h for a simple
 *  Gfx example and Audio example.
 */

#include "gfx.h" // general gfx lib I made for SDL
#include "input.h"
#include "general.h"
#include "body.h"
#include <iostream>
#define screenw 640
#define screenh 480

const int numBodies = 3;
const double timeStep = 1e6;//1e8;

void addForces(Body inputBodies[]) {
	for (int i = 0; i < numBodies; i++) {
		inputBodies[i].resetForce();
		for (int j = 0; j < numBodies; j++) {
			if (i != j) inputBodies[i].addForce(inputBodies[j]);
		}	
	}

	for (int i = 0; i < numBodies; i++) {
		inputBodies[i].update(timeStep); //Update with Timestep
	}	
}

int main ( int argc, char** argv ) {
	gfx::gfxinit(screenw, screenh); // open window with 640x480 res. 

	Body bodies[numBodies] = {{0, 110, 1.8267e-6, 0, 1, gfx::createTexture("./gfx/earth.bmp"), 32, 32},
       	                          {0, 240, 3.8583e-6, 0, 0.107, gfx::createTexture("./gfx/mars.bmp"), 32, 32},
                                  {0, 0, 0, 0, 333000, gfx::createTexture("./gfx/sun.bmp"), 32, 32}};



	//float fps, frames, frameStartTime, frameEndTime;

	/* program main loop */
	while (!(input::getKeyState(SDLK_ESCAPE) || input::getQuit())) {
		// get time when frame starts
		//frameStartTime = SDL_GetTicks();

		gfx::clearScreen(0, 0, 0);

		//Main Logic
		addForces(bodies);

		for (int i = 0; i < numBodies; i++) {
			bodies[i].drawBody(screenw, screenh);
		}	

		//End Main Logic

		gfx::update();
		// Using Vsync -- no need
		// get time at the end of frame after updating
		//frameEndTime = SDL_GetTicks();
		// increment frames
		//++frames;

		//fps = frames / (SDL_GetTicks() / 1000);

		//if ((1000 / 60) < (frameEndTime - frameStartTime)) {
		//	SDL_Delay((frameEndTime - frameStartTime) - (1000 / 60));
		//}
	}

	gfx::close();

	return 0; // return success!
}
