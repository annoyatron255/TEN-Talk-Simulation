#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#include "body.h"
#include "gfx.h"

Body::Body(double rx, double ry, double vx, double vy, double mass, SDL_Texture* bodyTexture, int w, int h) {
	this->rx = rx;
	this->ry = ry;
	this->vx = vx;
	this->vy = vy;
	this->mass = mass;
	this->bodyTexture = bodyTexture;
	//bodyTexture = gfx::createTexture(file);//bodyTexture;
	//if (bodyTexture == NULL) SDL_Log("ERROR");
	//if (gfx::createTexture("./gfx/earth.bmp") == NULL) SDL_Log("error 2");
	bodyRect.w = w;
	bodyRect.h = h;
}

void Body::update(double dt) {
	vx += dt * fx / mass;
	vy += dt * fy / mass;
	rx += dt * vx;
	ry += dt * vy;
}

double Body::distanceTo(Body b) {
	double dx = rx - b.rx;
	double dy = ry - b.ry;
	return sqrt(dx*dx + dy*dy);
}

void Body::resetForce() {
	fx = 0.0;
	fy = 0.0;
}

void Body::addForce(Body b) {
	double EPS = 3E4; //to avoid infinities
	double dx = b.rx - rx;
	double dy = b.ry - ry;
	double dist = sqrt(dx*dx + dy*dy);
	double F = (G * mass * b.mass) / (dist*dist + EPS*EPS);
	fx += F * dx / dist;
	fy += F * dy / dist;
}

void Body::drawBody(int screenw, int screenh, double vpx, double vpy, double vpw, double vph) {
	double wRadius = (vpw / 2);
	double hRadius = (vph / 2);
	bodyRect.x = (int)round(screenw * (rx - (vpx - wRadius)) / ((vpx + wRadius) - (vpx - wRadius))) - (bodyRect.w / 2);
	bodyRect.y = (int)round(screenh * (ry - (vpy - hRadius)) / ((vpy + hRadius) - (vpy - hRadius))) - (bodyRect.h / 2);

	gfx::drawTexture(bodyTexture, bodyRect);
}
