#pragma once

#include "position.h"
#include <chrono>

// Game Object
class Space
{
private:
	// The extent of the game and window
	Position extent;
	// The last time that a time was gotten.
	std::chrono::microseconds lastFrame;
	// Can a new time be gotten yet?
	bool isTimeUnlocked;
public:
	// Constructor
	Space(Position extent) : extent(extent), shipPosition(), 
		shipAngle(0.0), isTimeUnlocked(true)
	{
		// Get current time in microseconds
		using namespace std::chrono;
		lastFrame = duration_cast<microseconds>(
			system_clock::now().time_since_epoch()
			);
	}
	// Where the ship is currently
	Position shipPosition;
	// Speed and direction of the ship
	Velocity shipVelocity;
	// The direction the ship is facing.
	double shipAngle;
	// Get a new time.
	double getdTime()
	{
		// Get current time in microseconds
		using namespace std::chrono;
		microseconds timeNow = duration_cast<microseconds>(
			system_clock::now().time_since_epoch()
			);
		// find how long it has been since last gotten
		double dtime = (timeNow - lastFrame).count() / 1000000.0;
		// If we can save this time
		if (isTimeUnlocked)
		{
			// Save current time
			lastFrame = timeNow;
			isTimeUnlocked = false;
		}
		return dtime;
	}
	// Can we get a new time yet?
	void unlockTime() { isTimeUnlocked = true; }
};