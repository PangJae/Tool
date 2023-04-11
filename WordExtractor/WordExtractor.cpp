/*
  WORD EXTRACTOR
* ' ' / '.' / ','
* ���ڿ��� �� ��ҵ��� �����ͷ� �����Ͽ� ����
* �ڸ� ���ڿ� ��Ҹ� ���Ϳ� ����
* 
*/


#include <Windows.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#pragma comment(lib, "Winmm")
using namespace std;

#define MAX_STRLEN 1000



void StringDivide(PCWCHAR szString, vector<wstring> &wordArray);
void PrintWord(vector<wstring> &wordArray);

__int64 GetTick();
__int64 Begin, End;

void main()
{
	timeBeginPeriod(1);
	WCHAR wInput[MAX_STRLEN];
	vector<wstring> wordArray;
	memset(wInput, 0, sizeof(wInput));

	while (1)
	{
		wcout << "Input String: ";
		fgetws(wInput, MAX_STRLEN, stdin);

		Begin = GetTick();
		StringDivide(wInput, wordArray);
		End = GetTick();
		PrintWord(wordArray);
		wcout << endl << " (Elapsed Time : " << End - Begin << "ms)" << endl;
		wordArray.clear();
	}
	timeEndPeriod(1);
}


void StringDivide(PCWCHAR szString, vector<wstring>& wordArray)
{
	WCHAR tmp[MAX_STRLEN];
	int iPrePos = 0;
	int iCurPos = 0;

	// ó������ �����ڰ� �Էµ��� ���
	if (szString[0] == L' ' || szString[0] == L',' || szString[0] == L'.')
	{
		iCurPos = 1;
		iPrePos = 1;
	}

	for (; iCurPos < MAX_STRLEN; ++iCurPos)
	{

		if (szString[iCurPos] == L' ' || szString[iCurPos] == L',' || szString[iCurPos] == L'.')
		{
			// �����ڰ� ���������� �Էµ��� ���
			if (szString[iCurPos - 1] == L' ' || szString[iCurPos - 1] == L',' || szString[iCurPos - 1] == L'.')
			{
				iPrePos = iCurPos + 1;
				continue;
			}

			wcsncpy_s(tmp, szString + iPrePos, iCurPos - iPrePos);
			//tmp[iCurPos - iPrePos] = L'\0';
			wordArray.push_back(tmp);

			iPrePos = iCurPos + 1;
		}

		// NULL ���ڸ� ������ break
		if (szString[iCurPos] == L'\n')
		{
			// \n�� ����
			wcsncpy_s(tmp, szString + iPrePos, iCurPos - iPrePos);
			//tmp[iCurPos - iPrePos] = L'\0';
			wordArray.push_back(tmp);
			break;
		}
	}
}

void PrintWord(vector<wstring>& wordArray)
{
	for (auto it = wordArray.begin(); it != wordArray.end(); ++it)
		wcout << *it << ' ';
}


__int64 GetTick()
{
	LARGE_INTEGER liTime;
	QueryPerformanceCounter(&liTime);
	return static_cast<__int64>(liTime.QuadPart);
}

