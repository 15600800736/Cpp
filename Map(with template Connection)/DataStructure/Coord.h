

//Coord.h
#ifndef COORD_H
#define COORD_H

namespace huger
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
	Coord operator-(Coord& otherCoord)
	{
		Coord coord(X - otherCoord.X, Y - otherCoord.Y);
		return coord;
	}
	Coord operator+(Coord& otherCoord)
	{
		Coord coord(X + otherCoord.X, Y + otherCoord.Y);
		return coord;
	}
	int dot(Coord& otherCoord)
	{
		return X*otherCoord.X + Y*otherCoord.Y;
	}
	int cross(Coord& otherCoord)
	{
		return X*otherCoord.Y - Y*otherCoord.X;
	}
	int X;
	int Y;
};
}
#endif