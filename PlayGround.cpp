#include "PlayGround.h"
#include <ctime>
#include <iostream>

PlayGround::PlayGround() : 
	BaseApp(BG_SIZE_X+7, BG_SIZE_Y),
	oldObj(0),
	currentTime(0),
	score(0),
	step(STEP)
{
	srand(time(0));
	nextObj = rand() % 5;
	nextFlip = rand() % 2;
	createObj();

}

void PlayGround::KeyPressed(int btnCode)
{
	if (btnCode == 97) //a
	{
		if (leftIsEmpty())
			obj->coord.X--;
	}
	else if (btnCode == 100) //d
	{
		if (rightIsEmpty())
			obj->coord.X++;
	}
	else if (btnCode == 119) //w
	{
		//проверка чтобы не задеть ничего на развороте
		toEmptyOld();
		if (canBeRotate())
			obj->rotate();
		oldObj = obj->copy();
	}
	else if (btnCode == 115) //s
	{
		if (downIsEmpty())
		{
			obj->coord.Y++;
			currentTime = 0;//дабы небыло "двойных" скачков
		}
		/*если последнее движение вниз перед "заморозкой" объекта было инициировано 
		нажетием клавиши "вниз" - мгновенно фиксируем объект на матрице*/
		else
			currentTime = step;
	}
	else if (btnCode == 32) // spase
	{
		while (downIsEmpty())
			obj->coord.Y++;
		currentTime = step;
	}

	if (obj->coord.X < 0)
		obj->coord.X = 0;
	else if (obj->coord.X + obj->getSizeX() > BG_SIZE_X - 1)
		obj->coord.X = BG_SIZE_X - obj->getSizeX();
}

void PlayGround::UpdateF(float deltaTime)
{
	toEmptyOld();
	burn();
	currentTime += deltaTime;
	if (currentTime > step)
	{
		currentTime = 0;
		//если на шаг ниже залоченные клетки - фиксируем объект
		if (downIsEmpty())
			obj->coord.Y++;
		else
		{
			lockIn();
			if (!createObj())
				gameOver();
		}
	}
	oldObj = obj->copy();
	printObj(obj);
	printWalls();
	printNextObj();
	showInfo();
}

bool PlayGround::createObj()
{
	int shape = nextObj;
	nextObj = rand() % 5;
	int side = rand() % 4;
	bool flip = nextFlip;
	nextFlip = rand() % 2;
	switch (shape)
	{
	case 0:
		obj = new O(START_X, START_Y);
		break;
	case 1:
		obj = new I(START_X, START_Y, (bool)(side>1)?side-2:side);
		break;
	case 2:
		obj = new T(START_X, START_Y, side);
		break;
	case 3:
		obj = new L(START_X, START_Y, side, flip);
		break;
	case 4:
		obj = new Z(START_X, START_Y, side, flip);
		break;
	default:
		break;
	}
	for (int x = 0; x < obj->getSizeX(); x++)
		for (int y = 0; y < obj->getSizeY(); y++)
			if (GetChar(obj->coord.X + x, obj->coord.Y + y) != CHAR_EMPTY)
				return false;
	oldObj = obj->copy();
	return true;
}

void PlayGround::printObj(const Shape* object)
{
	for (int x = 0; x < object->getSizeX(); x++)
		for (int y = 0; y < object->getSizeY(); y++)
			if (object->arr[x][y] != CHAR_EMPTY)
				SetChar(x + object->coord.X, y + object->coord.Y, object->arr[x][y]);
}

void PlayGround::printWalls()
{
	for (int x = 0; x <= X_SIZE; x++)
		SetChar(x, 0, CHAR_SIDE);
	for (int x = 0; x <= BG_SIZE_X; x++)
		SetChar(x, Y_SIZE, CHAR_SIDE);
	for (int y = 0; y <= Y_SIZE; y++)
	{
		SetChar(0, y, '/');
		SetChar(BG_SIZE_X, y, '\\');
	}
	for (int y = 0; y <= Y_SIZE; y++)
		SetChar(X_SIZE, y, '/');
	for (int x = BG_SIZE_X + 1; x < X_SIZE; x++)
	{
		SetChar(x, 5, CHAR_SIDE);
		SetChar(x, 9, CHAR_SIDE);
		SetChar(x, 14, CHAR_SIDE);
		SetChar(x, Y_SIZE, CHAR_SIDE);
	}
}

void PlayGround::printNextObj()
{
	//очистка предыдущего
	for (int y = 1; y < 5; y++)
		for (int x = X_SIZE - 6; x < X_SIZE; x++)
			SetChar(x, y, CHAR_EMPTY);
	Shape* next = 0;
	switch (nextObj)
	{
	case 0:
		next = new O(X_SIZE - 4, 2);
		break;
	case 1:
		next = new I(X_SIZE - 5, 3, true);
		break;
	case 2:
		next = new T(X_SIZE-5, 2, 2);
		break;
	case 3:
		next = (nextFlip) ? new L(X_SIZE - 5, 2, 1, nextFlip) : new L(X_SIZE - 5, 2, 3, nextFlip);
		break;
	case 4:
		next = new Z(X_SIZE - 5, 2, 0, nextFlip);
		break;
	default:
		return;
		break;
	}
	printObj(next);
}

void PlayGround::showInfo()
{
	string info = to_string(step);
	for (int i = 0; i < 5; i++)
		SetChar(X_SIZE - 6 + i, 7, info[i]);
	SetChar(X_SIZE - 1, 7, 's');

	info = to_string(score);
	for (int i = 0; i < 6; i++)
		SetChar(X_SIZE - 6 + i, 11, *(L"Score:"+i));
	for (int i = 0; i < info.length(); i++)
		SetChar(X_SIZE - 4 + i, 12, info[i]);
}

void PlayGround::toEmptyOld()
{
	for (int x = 0; x < oldObj->getSizeX(); x++)
		for (int y = 0; y < oldObj->getSizeY(); y++)
			if (oldObj->arr[x][y] != CHAR_EMPTY)
				SetChar(x + oldObj->coord.X, y + oldObj->coord.Y, CHAR_EMPTY);
}

void PlayGround::lockIn()
{
	toEmptyOld();
	for (int x = 0; x < obj->getSizeX(); x++)
		for (int y = 0; y < obj->getSizeY(); y++)
			if (obj->arr[x][y] != CHAR_EMPTY)
				SetChar(x + obj->coord.X, y + obj->coord.Y, CHAR_LOCK);
	delete obj;
	delete oldObj;
}

bool PlayGround::downIsEmpty()
{
	if (obj->coord.Y + obj->getSizeY() > Y_SIZE)
		return false;
	for (int x = 0; x < obj->getSizeX(); x++)
		for (int y = obj->getSizeY() - 1; y >= 0; y--)
			if (obj->arr[x][y] != CHAR_EMPTY)
			{
				if (GetChar(obj->coord.X + x, obj->coord.Y + y + 1) != CHAR_EMPTY)
					return false;
				else
					break;
			}
	return true;
}

bool PlayGround::rightIsEmpty()
{
	for (int y = 0; y < obj->getSizeY(); y++)
		for (int x = obj->getSizeX() - 1; x >= 0; x--)
			if (obj->arr[x][y] != CHAR_EMPTY)
			{
				if (GetChar(obj->coord.X + x + 1, obj->coord.Y + y) == CHAR_LOCK)
					return false;
				else
					break;
			}
	return true;
}

bool PlayGround::leftIsEmpty()
{
	for (int y = 0; y < obj->getSizeY(); y++)
		for (int x = 0; x < obj->getSizeX(); x++)
			if (obj->arr[x][y] != CHAR_EMPTY)
			{
				if (GetChar(obj->coord.X + x - 1, obj->coord.Y + y) != CHAR_EMPTY)
					return false;
				else
					break;
			}
	return true;
}

bool PlayGround::canBeRotate()
{
	Shape * temp = obj->copy();
	temp->rotate();
	for (int y = 0; y < temp->getSizeY(); y++)
		for (int x = 0; x < temp->getSizeX(); x++)
			if (temp->arr[x][y] != CHAR_EMPTY && GetChar(temp->coord.X + x, temp->coord.Y + y) == CHAR_LOCK)
				return false;
	return true;
}

bool PlayGround::burn()
{
	bool filledString;
	for (int y = Y_SIZE-1; y > 0; y--)
	{
		filledString = true;
		for (int x = 1; x < BG_SIZE_X; x++)
			if (GetChar(x, y) == CHAR_EMPTY)
			{
				filledString = false;
				break;
			}
		if (!filledString)
			continue;
		
		for (int x = 1; x < BG_SIZE_X; x++)
			SetChar(x, y, CHAR_EMPTY);

		for (int i = y; i > 1; i--)
			for (int x = 0; x < BG_SIZE_X; x++)
				SetChar(x, i, GetChar(x, i - 1));

		score++;
		step *= CSTEP;
		return true;
	}
	return false;
}

void PlayGround::gameOver()
{
	system("cls");
	std::cout << "Game over!\nYour score: " << score << endl;
	cin.ignore();
	exit(0);
}