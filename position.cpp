
#include "position.h"
#include <cmath>

/***********************************************
* Position : Offset Rotate
* Returns a point that is this point rotated
* around an origin by a specified amount.
***********************************************/
Position Position::offsetRotate(const Position& origin, double rotation)
{
	// because sine and cosine are expensive, we want to call them only once
	double cosA = cos(rotation);
	double sinA = sin(rotation);

	// start with our original point
	Position ptReturn(origin);

	// find the new values
	ptReturn.addX(x * cosA + y * sinA);
	ptReturn.addY(y * cosA - x * sinA);


	return ptReturn;
}

/***********************************************
* Position : add
* Adds all components of the position objects.
***********************************************/
void Position::add(const Position& pt)
{
	this->x += pt.getX();
	this->y += pt.getY();
	this->z += pt.getZ();
}

//void Position::addpx(const Position& pt) // not used
//{
//	this->x += pt.getpxX();
//	this->y += pt.getpxY();
//	this->z += pt.getpxZ();
//}

/***********************************************
* Position : Move
* Moves a point an amount in a direction.
***********************************************/
void Position::move(double total, double direction)
{
	this->addX(sin(direction) * total);
	this->addY(cos(direction) * total);
}

/***********************************************
* Position : Move Towards 2d
* Moves a point an amount towards a point in a
* single plane.
***********************************************/
void Position::moveTowards2d(double amount, const Position& destination)
{
	this->move(amount, atan2(destination.getY(), destination.getX()));
}
