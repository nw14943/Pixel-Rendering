
#define _USE_MATH_DEFINES
#include <cmath>
#include "velocity.h"
#include "GUI.h"

/***********************************************
* Velocity : Apply
* This is where the Velocity is applied to a
* position based on time.
***********************************************/
void Velocity::apply(Position& position, double dtime)
{
	// Get extent and convert to coords
	Position extent = GUI::getExtent();
	double x = extent.getX() / 2.0;
	double y = extent.getY() / 2.0;

	// Warp if off the screen
	if (position.getpxX() > x||
		position.getpxX() < -x)
		position.setX((position.getpxX() < 0) ? x : -x);
	// Change the x position based on velocity and time
	position.addX(this->dx * dtime);
	// Warp if off the screen
	if (position.getpxY() > y ||
		position.getpxY() < -y)
		position.setY((position.getpxY() < 0) ? x : -x);
	// Change the y position based on velocity and time
	position.addY(this->dy * dtime);
}

/***********************************************
* Velocity : Set
* Sets the dx and dy components of the velocity
***********************************************/
void Velocity::set(double dx, double dy)
{
	this->dx = dx;
	this->dy = dy;
	// Make sure it's not too fast
	this->normalize();
}

/***********************************************
* Velocity : Set Total
* Sets the Velocity based on the direction and
* total.
***********************************************/
void Velocity::setTotal(double total, double dir)
{
	this->dx = (sin(dir) * total);
	this->dy = (cos(dir) * total);
	// Make sure it's not too fast
	this->normalize();
}

/***********************************************
* Velocity : Set Dx
* Sets the dx component of the velocity
***********************************************/
void Velocity::setDx(double dx)
{
	this->dx = dx;
	// Make sure it's not too fast
	this->normalize();
}

/***********************************************
* Velocity : Set Dy
* Sets the dy component of the velocity
***********************************************/
void Velocity::setDy(double dy)
{
	this->dy = dy;
	// Make sure it's not too fast
	this->normalize();
}

/***********************************************
* Velocity : Set Max
* Sets the maximum velocity that should be
* allowed.
***********************************************/
void Velocity::setMax(double maxVelocity)
{
	this->maxVelocity = maxVelocity;
	// Make sure it's not too fast
	this->normalize();
}

/***********************************************
* Velocity : Add Dx
* Adds to the dx component of the velocity
***********************************************/
void Velocity::addDx(double ddx)
{
	this->dx += ddx;
	// Make sure it's not too fast
	this->normalize();
}

/***********************************************
* Velocity : Add Dy
* Adds to the dy component of the velocity
***********************************************/
void Velocity::addDy(double ddy)
{
	this->dy += ddy;
	// Make sure it's not too fast
	this->normalize();
}

/***********************************************
* Velocity : Add Total
* Adds to the total velocity in a specified
* direction.
***********************************************/
void Velocity::addTotal(double total, double direction)
{
	this->dx += total * sin(direction);
	this->dy += total * cos(direction);
	// Make sure it's not too fast
	this->normalize();
}

/***********************************************
* Velocity : Normalize
* Makes sure the total velocity does not exceed
* the allowed maximum.
***********************************************/
void Velocity::normalize()
{
	if (this->getTotal() > this->maxVelocity)
	{
		double dx = (sin(getDir()) * maxVelocity);
		double dy = (cos(getDir()) * maxVelocity);

		this->dx = dx;
		this->dy = dy;
	}
}