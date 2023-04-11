/*
  PRODUCTION LINE
* FIFO���� �ϹǷ� ����ť ���
* GetickCount64�� ����Ͽ� 10�� ����� ���� �Ϸ�
*/

#include <Windows.h>
#include <cstdio>
#include <conio.h>
#pragma comment(lib,"Winmm")

#define MAX_UNIT 5
#define PRODUCTION_TIME 10000

const char* szNotice = "";
bool bExit;


int Front=0;
int Rear=0;
ULONGLONG UnitQueue[MAX_UNIT];
bool Enqueue(ULONGLONG In);
bool Dequeue();
bool Peek(int iPos, ULONGLONG* pOut);


void Draw();
void Action();
void KeyProcess();

void main()
{
	timeBeginPeriod(1);
	COORD pos;
	pos.X = pos.Y = 0;
	while (!bExit)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		Draw();
		Action();
		KeyProcess();
		Sleep(20);
	}

	timeEndPeriod(1);
}

bool Enqueue(ULONGLONG In)
{
	if ((Rear + 1) % MAX_UNIT == Front)
		return false;

	Rear = (Rear + 1) % MAX_UNIT;
	UnitQueue[Rear] = In;
	return true;
}
bool Dequeue()
{
	if (Front == Rear)
		return false;

	Front = (Front + 1) % MAX_UNIT;
	return true;
}
bool Peek(int iPos, ULONGLONG* pOut)
{
	if (iPos == Rear)
		return false;

	iPos = (iPos + 1) % MAX_UNIT;
	*pOut = UnitQueue[iPos];
	return true;

}

void KeyProcess()
{
	if (_kbhit())
	{
		int iKey = _getch();
		if (iKey == '1')
		{
			if (!Enqueue(GetTickCount64()))
			{
				szNotice = "���ֻ������";
			}
		}

		if (iKey == '2')
		{
			bExit = true;
		}
	}
}

void Action()
{
	ULONGLONG Out;
	Peek(Front, &Out);
	if (GetTickCount64() - Out > 10000)
	{
		if (Dequeue())
		{
			szNotice = "���ֻ���Ϸ�";
			system("cls");
		}
	}
}

void Draw()
{
	ULONGLONG Out;
	int iPos = Front;
	printf("1. ���ֻ���    2. ����\n");
	printf("---------------------------------------------\n");
	while (Peek(iPos, &Out))
	{
		printf("Progress: %lld |", (GetTickCount64()-Out)/100);
		iPos = (iPos+1)%MAX_UNIT;
	}
	printf("\n---------------------------------------------\n");
	printf(szNotice);
	szNotice = "";
}