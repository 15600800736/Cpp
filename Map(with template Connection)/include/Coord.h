

//Coord.h
#ifndef COORD_H
#define COORD_H

namespace graphic
{
struct Coord
{
	Coord() :X(0), Y(0)
	{

	}
	Coord(int x, int y)
	{
		X = x;
		Y = y;
	}
	bool operator==(Coord otherCoord)
	{
		return (this->X == otherCoord.X) && (this->Y == otherCoord.Y) ? true : false;
	}
	Coord operator-(const Coord& otherCoord)
	{
		Coord coord(X - otherCoord.X, Y - otherCoord.Y);
		return coord;
	}
	Coord operator+(const Coord& otherCoord)
	{
		Coord coord(X + otherCoord.X, Y + otherCoord.Y);
		return coord;
	}
	int dot(const Coord& otherCoord)
	{
		return X*otherCoord.X + Y*otherCoord.Y;
	}
	int cross(const Coord& otherCoord)
	{
		return X*otherCoord.Y - Y*otherCoord.X;
	}
	int X;
	int Y;
};

Coord operator-(const Coord& first, const Coord& second)
{
	Coord coord(first.X - second.X, first.Y - second.Y);
	return coord;
}
}
#endif