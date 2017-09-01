#pragma once

#include "BaseApp.h"
#include "Shape.h"

#define STEP 1			// ��������� �������� (����� ������ ����)
#define CSTEP 0.85		// �����������-��������� ���������� ��������
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

	//false - ���� ����������������� ������� ��� �������� ������� ��������� �������
	bool createObj();//�������� ������ �������
	void printObj(const Shape*);//����������� ������� (��������� �� �������)
	void printWalls();//����������� �����
	void printNextObj();
	void showInfo();
	void toEmptyOld();//�������� ������� (�������� �� ������� �������������� ��������)
	void lockIn();//��������������� ������� ������ �� �������
	bool downIsEmpty();//true - ��� ��� �������� ����, ����� ���������
	bool rightIsEmpty();
	bool leftIsEmpty();
	bool canBeRotate();//true - ����� ���������
	bool burn();//��������� ����� ���. true - ���� ������� (���� ��� �������)
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