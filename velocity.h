#pragma once

#include "position.h"

// Velocity on a 2d plane
class Velocity
{
private:
	double dx;
	double dy;
	// The maximum Total velocity
	double maxVelocity;
	// Sets velocity to the Max if over
	void normalize();
public:
	// Constructor
	Velocity() : dx(0.0), dy(0.0), maxVelocity(150.0) {}
	// Setters
	void set(double dx, double dy);
	void setTotal(double total, double dir);
	void setDx(double dx);
	void setDy(double dy);
	void setMax(double maxVelocity);
	// Adders
	void addDx(double ddx);
	void addDy(double ddy);
	void addTotal(double total, double direction);
	// Getters
	double getDx() { return dx; }
	double getDy() { return dy; }
	double getDir() { return atan2(dx, dy); }
	double getTotal() { return sqrt((dx * dx) + (dy * dy)); }
	// Applies the Velocity to the position
	void apply(Position& position, double dtime);
};