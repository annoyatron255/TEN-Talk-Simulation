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
const double timeStep = 1e8;
Body bodies[numBodies] = {{375, 25, 0, 0, 50},{400, 400, 0, 0, 50},{250, 250, 0, 0, 150}};

void addForces() {
	for (int i = 0; i < numBodies; i++) {
		bodies[i].resetForce();
		for (int j = 0; j < numBodies; j++) {
			if (i != j) bodies[i].addForce(bodies[j]);
		}	
	}

	for (int i = 0; i < numBodies; i++) {
		bodies[i].update(timeStep); //Update with Timestep
	}	
}

int main ( int argc, char** argv ) {
	gfx::gfxinit(screenw, screenh); // open window with 640x480 res. 

	//float fps, frames, frameStartTime, frameEndTime;

	/* program main loop */
	while (!(input::getKeyState(SDLK_ESCAPE) || input::getQuit())) {
		// get time when frame starts
		//frameStartTime = SDL_GetTicks();

		gfx::clearScreen(0, 0, 0);

		//Main Logic
		addForces();

		for (int i = 0; i < numBodies; i++) {
			bodies[i].drawBody();
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
