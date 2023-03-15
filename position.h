#pragma once

class Position
{
private:
	double x;
	double y;
	double z;
	// Conversions from Virtual to real Pixel value
	// Not really used becasue of zoom
	static double virtualPixelConversionX;
	static double virtualPixelConversionY;
	static double virtualPixelConversionZ;
public:
	// Constructors
	Position() : x(0), y(0), z(0) {}
	Position(double x, double y, double z = 0) : x(x), y(y), z(z) {}
	Position(const Position& pos) : x(pos.x), y(pos.y), z(pos.z) {}
	// Set the Pixel Conversions
	static void setPixelConversion(double vPxCvrsX, double vPxCvrsY, double vPxCvrsZ)
	{ 
		virtualPixelConversionX = vPxCvrsX;
		virtualPixelConversionY = vPxCvrsY;
		virtualPixelConversionZ = vPxCvrsZ;
	}
	// Getters
	double getX() const { return x; }
	double getY() const { return y; }
	double getZ() const { return z; }
	// Getters for Converted
	double getpxX() const { return x / virtualPixelConversionX; }
	double getpxY() const { return y / virtualPixelConversionY; }
	double getpxZ() const { return z / virtualPixelConversionZ; }
	// Setters
	void setX(double x) { this->x = x; }
	void setY(double y) { this->y = y; }
	void setZ(double z) { this->z = z; }
	// Adders
	void addX(double dx) { this->x += dx; }
	void addY(double dy) { this->y += dy; }
	void addZ(double dz) { this->z += dz; }
	// Add all components
	void add(const Position& pt);
	//void addpx(const Position& pt); // not used
	// Used for Velocity
	void move(double total, double direction);
	void moveTowards2d(double amount, const Position& destination);
	// Returns a position if this was rotated around an origin.
	Position offsetRotate(const Position& origin, double rotation);
};