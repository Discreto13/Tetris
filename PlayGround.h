#pragma once

#include "BaseApp.h"
#include "Shape.h"

#define STEP 1			// начальная скорость (время одного шага)
#define CSTEP 0.85		// коэффициент-множитель увеличения скорости
#define START_X 7
#define START_Y 1
#define BG_SIZE_X 16
#define BG_SIZE_Y 20

class PlayGround : public BaseApp
{
public:
	PlayGround();
	virtual void KeyPressed(int btnCode);
	virtual void UpdateF(float deltaTime);

	//false - если зарезервированная область для создания объекта оказалась занятой
	bool createObj();//создание нового объекта
	void printObj(const Shape*);//прорисовать текущий (перенести на матрицу)
	void printWalls();//прорисовать стены
	void printNextObj();
	void showInfo();
	void toEmptyOld();//очистить прошлый (очистить на матрице соответсвующие элементы)
	void lockIn();//зафиксироваться текущий объект на матрице
	bool downIsEmpty();//true - низ под объектом пуст, можно двигаться
	bool rightIsEmpty();
	bool leftIsEmpty();
	bool canBeRotate();//true - можно повернуть
	bool burn();//пытаеться сжечь ряд. true - если удалось (было что сжигать)
	void gameOver();

private:
	int score;
	float currentTime;
	float step;
	Shape* obj;
	Shape* oldObj;
	int nextObj;
	bool nextFlip;
};