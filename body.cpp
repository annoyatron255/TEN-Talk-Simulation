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

void Body::drawBody(int screenw, int screenh) {
	//bodyRect.w = 32;
	//bodyRect.h = 32;
	bodyRect.x = ((int) round(rx)) - (bodyRect.w / 2) + (screenw / 2);
	bodyRect.y = ((int) round(ry)) - (bodyRect.h / 2) + (screenh / 2);
	//bodyTexture = gfx::createTexture("./gfx/earth.bmp");
	gfx::drawTexture(bodyTexture, bodyRect);
	//if (gfx::createTexture("./gfx/earth.bmp") == NULL) SDL_Log("error 3");
	//gfx::drawTexture(gfx::createTexture("./gfx/earth.bmp"), bodyRect);
	//gfx::drawRect(bodyRect, 255, 0, 0);
}
