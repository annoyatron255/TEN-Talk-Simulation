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
const double timeStep = 1;//1e8;

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

	Body bodies[numBodies] = {{1.496e8, 0, 0, 941976.6599, 5.972e24, gfx::createTexture("./gfx/earth.bmp"), 32, 32},
       	                          //{-2.279e8, 0, 0, -763068.101, 6.39e23, gfx::createTexture("./gfx/mars.bmp"), 25, 25},
                                  {1.639e8, 1.583e8, -530072, 548905, 6.39e23, gfx::createTexture("./gfx/mars.bmp"), 25, 25},
                                  {0, 0, 0, 0, 1.989e30, gfx::createTexture("./gfx/sun.bmp"), 100, 100},
                                  {1.505e8, 0, 0, 1.036e6, 500000, gfx::createTexture("./gfx/sun.bmp"), 5, 5}};

	/* program main loop */
	while (!(input::getKeyState(SDLK_ESCAPE) || input::getQuit())) {
		gfx::clearScreen(0, 0, 0);

		//Main Logic
		addForces(bodies);

		for (int i = 0; i < numBodies; i++) {
			bodies[i].drawBody(screenw, screenh, 0, 0, 5e8, 5e8);
		}	

		//End Main Logic

		gfx::update();
}

	gfx::close();

	return 0; // return success!
}
