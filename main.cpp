/** Main.cpp controls lib.h for a simple
 *  Gfx example and Audio example.
 */

#include "gfx.h" // general gfx lib I made for SDL
#include "input.h"
#include "general.h"
#include "body.h"
#include <iostream>

const int screenw = 640;
const int screenh = 640;

double viewPortX = 0;
double viewPortY = 0;
double viewPortW = 5e11;
double viewPortH = 5e11;

const int numBodies = 4;
double timeStep = 5e4;

double totalTime = 0;

void addForces(Body inputBodies[]) {
	for (int i = 0; i < numBodies; i++) {
		inputBodies[i].resetForce();
		for (int j = 0; j < numBodies; j++) {
			if (i != j) inputBodies[i].addForce(inputBodies[j]);
		}	
	}
}

void updateBodies(Body inputBodies[]) {
	for (int i = 0; i < numBodies; i++) {
		inputBodies[i].update(timeStep); //Update with Timestep
		inputBodies[i].drawBody(screenw, screenh, viewPortX, viewPortY, viewPortW, viewPortH);
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

		if (1==0) {
			bodies[3].rx = bodies[1].rx + 1000;
			bodies[3].ry = bodies[1].ry + 1000;
			//bodies[3].vx = 0;
			//bodies[3].vy = 0;	
		}

		updateBodies(bodies);
		//End Main Logic
		//SDL_Delay(1);
		totalTime += timeStep;
		gfx::update();
}

	gfx::close();

	return 0; // return success!
}
