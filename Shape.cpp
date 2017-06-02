#include "Shape.h"

Shape::Shape(Coordinates c, int arrX, int arrY) :
	sizeX(arrX),
	sizeY(arrY),
	arr(0)
{
	this->coord = c;
	initArray();
}

Shape::Shape(Coordinates c) :
	sizeX(0),
	sizeY(0),
	arr(0)
{
	this->coord = c;
}

Shape::~Shape()
{
	clearArray();
}

void Shape::initArray()
{
	arr = new char*[sizeX];
	for (int i = 0; i < sizeX; i++)
		arr[i] = new char[sizeY];

	for (int x = 0; x < sizeX; x++)
		for (int y = 0; y < sizeY; y++)
			arr[x][y] = CHAR_EMPTY;
}

void Shape::clearArray()
{
	for (int i = 0; i < sizeX; i++)
		delete[] arr[i];
	delete[] arr;
}

void Shape::rotate()
{
	if (arr == 0)
		return;

	char** tempM;
	tempM = new char*[sizeX];
	for (int x = 0; x < sizeX; x++)
		tempM[x] = new char[sizeY];
	for (int x = 0; x < sizeX; x++)
		for (int y = 0; y < sizeY; y++)
			tempM[x][y] = arr[x][y];

	clearArray();
	int temp = sizeX;
	sizeX = sizeY;
	sizeY = temp;
	initArray();

	for (int x = 0; x < sizeX; x++)
		for (int y = 0; y < sizeY; y++)
			arr[x][y] = tempM[y][sizeX - x - 1];

	for (int x = 0; x < sizeY; x++)
		delete[] tempM[x];
	delete[] tempM;
}

void Shape::flip()
{
	int temp;
	for (int y = 0; y < sizeY; y++)
		for (int x = 0; x < sizeX / 2; x++)
		{
			temp = arr[x][y];
			arr[x][y] = arr[sizeX - x - 1][y];
			arr[sizeX - x - 1][y] = temp;
		}
}

O::O(int x, int y) :
	Shape(Coordinates(x, y), 2, 2)
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			arr[i][j] = CHAR_OBJECT;
}

Shape* O::copy()
{
	O* temp = new O(this->coord.X, this->coord.Y);
	return temp;
}

void O::rotate() {}

I::I(int x, int y, bool side) :
	Shape(Coordinates(x, y), 1, 4),
	mySide(0)
{
	for (int x = 0; x < 1; x++)
		for (int y = 0; y < 4; y++)
			arr[x][y] = CHAR_OBJECT;

	if (side != mySide)
		rotate();
}

Shape* I::copy()
{
	I* temp = new I(this->coord.X, this->coord.Y, mySide);
	return temp;
}

void I::rotate()
{
	Shape::rotate();
	mySide = !mySide;
}


T::T(int x, int y, int side) :
	Shape(Coordinates(x, y), 3, 2),
	mySide(0)
{
	arr[1][1] = CHAR_OBJECT;
	arr[0][0] = CHAR_OBJECT;
	arr[1][0] = CHAR_OBJECT;
	arr[2][0] = CHAR_OBJECT;

	while (mySide < side)
		rotate();
}

Shape * T::copy()
{
	return new T(this->coord.X, this->coord.Y, mySide);
}

void T::rotate()
{
	Shape::rotate();
	if (++mySide > 3)
		mySide = 0;
}

L::L(int x, int y, int side, bool flip) :
	Shape(Coordinates(x, y), 2, 3),
	mySide(0),
	myFlip(flip)
{
	arr[0][0] = CHAR_OBJECT;
	arr[0][1] = CHAR_OBJECT;
	arr[0][2] = CHAR_OBJECT;
	arr[1][2] = CHAR_OBJECT;

	if (myFlip)
		Shape::flip();

	while (mySide < side)
		rotate();
}

Shape * L::copy()
{
	return new L(this->coord.X, this->coord.Y, mySide, myFlip);
}

void L::rotate()
{
	Shape::rotate();
	if (++mySide > 3)
		mySide = 0;
}

Z::Z(int x, int y, int side, bool flip) :
	Shape(Coordinates(x, y), 3, 2),
	mySide(0),
	myFlip(flip)
{
	arr[0][0] = CHAR_OBJECT;
	arr[1][0] = CHAR_OBJECT;
	arr[1][1] = CHAR_OBJECT;
	arr[2][1] = CHAR_OBJECT;

	if (myFlip)
		Shape::flip();

	while (mySide < side)
		rotate();
}

Shape * Z::copy()
{
	return new Z(this->coord.X, this->coord.Y, mySide, myFlip);
}

void Z::rotate()
{
	Shape::rotate();
	if (++mySide > 3)
		mySide = 0;
}