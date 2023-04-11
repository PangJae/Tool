/*
  WORD EXTRACTOR
* ' ' / '.' / ','
* 문자열의 각 요소들을 포인터로 접근하여 조작
* 자른 문자열 요소를 벡터에 넣음
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

	// 처음부터 구분자가 입력됐을 경우
	if (szString[0] == L' ' || szString[0] == L',' || szString[0] == L'.')
	{
		iCurPos = 1;
		iPrePos = 1;
	}

	for (; iCurPos < MAX_STRLEN; ++iCurPos)
	{

		if (szString[iCurPos] == L' ' || szString[iCurPos] == L',' || szString[iCurPos] == L'.')
		{
			// 구분자가 연속적으로 입력됐을 경우
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

		// NULL 문자를 만나면 break
		if (szString[iCurPos] == L'\n')
		{
			// \n은 무시
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

