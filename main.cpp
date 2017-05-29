/** Main.cpp controls lib.h for a simple
 *  Gfx example and Audio example.
 */

#include "gfx.h" // general gfx lib I made for SDL
#include "input.h"
#include "general.h"
#include "body.h"
#include <iostream>

const int screenw = 720;//640;
const int screenh = 720;//640;

double viewPortX = 0;
double viewPortY = 0;
double viewPortW = 5e11;
double viewPortH = 5e11;


const int numBodies = 4;
double timeStep = 5e4/2; //Number of Seconds Elapsed in One Frame (Generally 1/60 of a Second)

double totalTime = 0;

long trailIndex = 0;

const int orbitSize = 3000;
SDL_Point earthOrbitPoints[orbitSize];
SDL_Point marsOrbitPoints[orbitSize];

void addForces(Body inputBodies[], int length) {
	for (int i = 0; i < length; i++) {
		inputBodies[i].resetForce();
		for (int j = 0; j < length; j++) {
			if (i != j) inputBodies[i].addForce(inputBodies[j]);
		}	
	}
}


void updateBodies(Body inputBodies[], int length) {
	for (int i = 0; i < length; i++) {
		inputBodies[i].update(timeStep); //Update with Timestep
	}
}

void drawBodies(Body inputBodies[], int length) {
	for (int i = 0; i < length; i++) {
		inputBodies[i].updateBody(screenw, screenh, viewPortX, viewPortY, viewPortW, viewPortH);
		inputBodies[i].drawBody();
	}
}

void drawInitialOrbits(Body inputBodies[]) {

	Body bodyArray[3] = {
		inputBodies[0],inputBodies[1], inputBodies[2]
	};

	for (int i = 0; i < orbitSize; i++) {

		//std::cout << "x: "<<bodyArray[1].rx<<"\n";

		addForces(bodyArray,3);
		updateBodies(bodyArray,3);

		bodyArray[0].updateBody(screenw, screenh, viewPortX, viewPortY, viewPortW, viewPortH);
		earthOrbitPoints[i].x=bodyArray[0].bodyRect.x + bodyArray[0].bodyRect.w/2;
		earthOrbitPoints[i].y=bodyArray[0].bodyRect.y + bodyArray[0].bodyRect.h/2;
		bodyArray[1].updateBody(screenw, screenh, viewPortX, viewPortY, viewPortW, viewPortH);
		marsOrbitPoints[i].x=bodyArray[1].bodyRect.x + bodyArray[1].bodyRect.w/2;
		marsOrbitPoints[i].y=bodyArray[1].bodyRect.y + bodyArray[1].bodyRect.h/2;
	}
}

int main ( int argc, char** argv ) {
	gfx::gfxinit(screenw, screenh); // open window with 640x480 res. 

	SDL_Point trail[10000];
	SDL_Color trailColor[10000];

	Body bodies[numBodies] = {{1.496e11, 0, 0, 29783, 5.972e24, gfx::createTexture("./gfx/earth.bmp"), 32, 32},
		{1.639e11, 1.583e11, -16762, 17358, 6.39e23, gfx::createTexture("./gfx/mars.bmp"), 25, 25},
		{0, 0, 0, 0, 1.989e30, gfx::createTexture("./gfx/sun.bmp"), 100, 100},
		{1.505e11, 0, 0, 32730, 500, gfx::createTexture("./gfx/sun.bmp"), 5, 5}};

	drawInitialOrbits(bodies);
	gfx::clearScreen(0, 0, 0);

	gfx::setFont("./FiraMono-Regular.ttf", 22);
	/* program main loop */
	while (!(input::getKeyState(SDLK_ESCAPE) || input::getQuit())) {
		gfx::clearScreen(0, 0, 0);

		//Main Logic
		addForces(bodies,numBodies);

		for(int i = 1; i < orbitSize; i++){
			gfx::drawLine(earthOrbitPoints[i].x,earthOrbitPoints[i].y,earthOrbitPoints[i-1].x,earthOrbitPoints[i-1].y,85, 85, 85);
			gfx::drawLine(marsOrbitPoints[i].x,marsOrbitPoints[i].y,marsOrbitPoints[i-1].x,marsOrbitPoints[i-1].y,85, 85, 85);
		}

		//Manually Modifiy Force, Velocity, and Coord. Here
		double TOF = 22375000;
		//double timeToReturn = 66500000;
		double timeToReturn = 61550000;

		trailColor[trailIndex] = trailColor[trailIndex-1];

		if (totalTime < TOF) {
			trailColor[trailIndex].r = 255;
			trailColor[trailIndex].g = 255;
			trailColor[trailIndex].b = 255;
		} else if (totalTime > TOF && totalTime < timeToReturn) {
			bodies[3].rx = bodies[1].rx + 1000;
			bodies[3].ry = bodies[1].ry + 1000;
			bodies[3].vx = 0;
			bodies[3].vy = 0;
			trailColor[trailIndex].r = 255;
			trailColor[trailIndex].g = 0;
			trailColor[trailIndex].b = 0;
		} else if (totalTime >= timeToReturn && totalTime < timeToReturn + timeStep) {
			bodies[3].rx = bodies[1].rx + 600000000;
			bodies[3].ry = bodies[1].ry;
			bodies[3].vx = -18240;//-21435;
			bodies[3].vy = 11354;//-1461;
			trailColor[trailIndex].r = 0;
			trailColor[trailIndex].g = 255;
			trailColor[trailIndex].b = 0;
		} else if (totalTime > timeToReturn + timeStep + TOF) {
			bodies[3].rx = bodies[0].rx + 1000;
			bodies[3].ry = bodies[0].ry + 1000;
			bodies[3].vx = 0;
			bodies[3].vy = 0;
		}

		updateBodies(bodies,numBodies);
		//SDL_Log("Mars X: %f Y: %f VX: %f VY: %f", bodies[1].rx, bodies[1].ry, bodies[1].vx, bodies[1].vy);
		//SDL_Log("Time: %f", totalTime);
		//SDL_Log("Angle: %f", acos(((bodies[0].rx * bodies[1].rx) + (bodies[0].ry * bodies[1].ry))/(1.496e11 * 2.279e11)) * 180 / 3.141592654);
		//Modify Viewport Here
		drawBodies(bodies,numBodies);
		if ( totalTime < timeToReturn + timeStep + TOF) {
			trail[trailIndex].x = bodies[3].bodyRect.x + bodies[3].bodyRect.w / 2;
			trail[trailIndex].y = bodies[3].bodyRect.y + bodies[3].bodyRect.h / 2;
			trailIndex++;
		}
		for (int i = 1; i < trailIndex; i++) {
			gfx::drawLine(trail[i].x, trail[i].y, trail[i-1].x, trail[i-1].y, trailColor[i].r, trailColor[i].g, trailColor[i].b);
			//gfx::drawPoint(trail[i].x, trail[i].y, trailColor[i].r, trailColor[i].g, trailColor[i].b);
		}
		//End Main Logic
		totalTime += timeStep;
		SDL_Delay(1);
		//gfx::drawText("Hello, World!", 50, 50, 255, 0, 0);
		gfx::update();
	}

	gfx::close();

	return 0; // return success!
}
