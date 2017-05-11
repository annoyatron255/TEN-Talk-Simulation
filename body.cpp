#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#include "body.h"
#include "gfx.h"

Body::Body(double rx, double ry, double vx, double vy, double mass) {
	this->rx = rx;
	this->ry = ry;
	this->vx = vx;
	this->vy = vy;
	this->mass = mass;
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
	Body a = *this;
	double EPS = 3E4; //to avoid infinities
	double dx = b.rx - a.rx;
	double dy = b.ry - a.ry;
	double dist = sqrt(dx*dx + dy*dy);
	double F = (G * a.mass * b.mass) / (dist*dist + EPS*EPS);
	a.fx += F * dx / dist;
	a.fy += F * dy / dist;
}

void Body::drawBody() {
	gfx::drawTexture(bodyTexture, bodyRect);
}
