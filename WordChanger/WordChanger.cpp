#include <Windows.h>
#include <cstdio>
#include <cstring>
#include <locale>
using namespace std;

#define MAX_STRLEN 1000
#define df_WORD_CNT 13

WCHAR g_Dic[df_WORD_CNT][2][20]
{
  { L"i",L"나" },{ L"you",L"너" },{ L"like",L"좋아한다" },{ L"love",L"사랑한다" },{ L"hate", L"증오한다" },
  { L"am",L"은/는" },{ L"are", L"은/는" },{L"is", L"은/는"}, { L"she", L"그녀" },{ L"he", L"그" },
  { L"boy", L"소년" },{L"a",L""}, { L"an",L"" }
};

WCHAR g_Buff[MAX_STRLEN / 2][MAX_STRLEN];


void StringDiv(PCWCHAR);
void Exchange(WCHAR* pSrc, WCHAR* pDest);
void main()
{
	_wsetlocale(LC_ALL, L"kor");

	WCHAR wInput[MAX_STRLEN];
	WCHAR wOutput[MAX_STRLEN];

	ZeroMemory(wInput, sizeof(wInput));
	ZeroMemory(wOutput, sizeof(wOutput));


	fgetws(wInput, MAX_STRLEN, stdin);

	// 문자열을 소문자로 변환


	StringDiv(wInput);
	for (int i = 0; i < MAX_STRLEN / 2; i++)
	{
		if (wcscmp(g_Buff[i], L"\0") != 0)
		{
			Exchange(g_Buff[i], wOutput);
		}
	}

	wprintf(L"%s\n", wOutput);
	system("pause");


}

void StringDiv(PCWCHAR wstr)
{
	int iArr = 0;
	int iPrev = 0;
	int iCur = 0;
	if (wstr[0] == L' ' || wstr[0] == L',' || wstr[0] == L'.')
	{
		iCur = 1;
		//iPrev = 1;
	}

	for (; iCur < MAX_STRLEN; iCur++)
	{
		if (wstr[iCur] == L' ' || wstr[iCur] == L',' || wstr[iCur] == L'.')
		{
			if (wstr[iCur - 1] == L' ' || wstr[iCur - 1] == L',' || wstr[iCur - 1] == L'.')
			{
				iPrev = iCur + 1;
				continue;
			}

			wcsncpy_s(g_Buff[iArr++], wstr + iPrev, iCur - iPrev);
			iPrev = iCur + 1;
		}


		if (wstr[iCur] == L'\0')
		{
			wcsncpy_s(g_Buff[iArr++], wstr + iPrev, iCur - iPrev-1);
			break;
		}
	}
}

void Exchange(WCHAR* pSrc, WCHAR* pDest)
{
	for (int i = 0; i < df_WORD_CNT; i++)
	{
		if (wcscmp(g_Dic[i][0], pSrc) == 0)
		{
			wcscat_s(pDest, MAX_STRLEN, g_Dic[i][1]);
			wcscat_s(pDest, MAX_STRLEN, L" ");
			return;
		}
	}
	wcscat_s(pDest, MAX_STRLEN, pSrc);
	wcscat_s(pDest, MAX_STRLEN, L" ");
	
}