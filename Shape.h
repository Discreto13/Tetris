#pragma once

#define CHAR_EMPTY ' '
#define CHAR_OBJECT 'Х'
#define CHAR_LOCK '*'
#define CHAR_SIDE '='

class Coordinates
{
public:
	Coordinates(int x, int y) : X(x), Y(y) {}
	Coordinates() : X(0), Y(0) {}
	int X;
	int Y;
};

//абстрактный класс дл€ всех фигур
class Shape
{
public:
	Shape(Coordinates, int, int);
	virtual ~Shape();

	int getSizeX() const { return sizeX; }
	int getSizeY() const { return sizeY; }

	virtual Shape* copy() = 0;
	virtual void rotate() = 0;

	Coordinates coord;
	char ** arr;

protected:
	Shape(Coordinates);
	void clearArray();
	void initArray();
	void flip();
	int sizeX;
	int sizeY;
};

//  **
//  **
class O : public Shape
{
public:
	O(int, int);
	virtual Shape* copy();
	virtual void rotate();
};

// ****
class I : public Shape
{
public:
	I(int, int, bool = 0);
	virtual Shape* copy();
	virtual void rotate();
	bool mySide;
};

//  ***
//   *
class T : public Shape
{
public:
	T(int, int, int = 0);
	virtual Shape* copy();
	virtual void rotate();
	int mySide;
};

//  *
//  *
//  **
class L : public Shape
{
public:
	L(int, int, int = 0, bool = 0);
	virtual Shape* copy();
	virtual void rotate();
	int mySide;
	const bool myFlip;
};

//  **
//   **
class Z : public Shape
{
public:
	Z(int, int, int = 0, bool = 0);
	virtual Shape* copy();
	virtual void rotate();
	int mySide;
	const bool myFlip;
};