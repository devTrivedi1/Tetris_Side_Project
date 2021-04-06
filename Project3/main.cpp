#include <iostream>
#include <Windows.h>

std::wstring tetris[7];
int nFieldWidth = 12;
int nFieldHeight = 18;
unsigned char* pField = nullptr;

int nScreenWidth = 80;
int nScreenHeight = 30;

int Rotate(int px, int py, int r)
{
	switch (r % 4)
	{
	case 0: return py * 4 + px; //0 degrees
	case 1: return 12 + py - (px * 4); // 90 degrees
	case 2: return 15 - (py * 4) - px; //180 degrees
	case 3: return 3 - py + (px * 4); //270 degrees
	}
	return 0;
}
int main()
{
	HWND hwnd = GetConsoleWindow();
	if (hwnd != NULL)
	{
		MoveWindow(hwnd, 200, 200, 680, 400, TRUE);
	}

	tetris[0].append(L"..X.");
	tetris[0].append(L"..X.");
	tetris[0].append(L"..X.");
	tetris[0].append(L"..X.");

	tetris[1].append(L".XX.");
	tetris[1].append(L"..XX");
	tetris[1].append(L"....");
	tetris[1].append(L"....");

	tetris[2].append(L"..XX");
	tetris[2].append(L".XX.");
	tetris[2].append(L"....");
	tetris[2].append(L"....");

	tetris[3].append(L"X...");
	tetris[3].append(L"XX..");
	tetris[3].append(L"X...");
	tetris[3].append(L"....");
					  
	tetris[4].append(L".XX.");
	tetris[4].append(L".XX.");
	tetris[4].append(L"....");
	tetris[4].append(L"....");

	tetris[5].append(L"X...");
	tetris[5].append(L"XXXX");
	tetris[5].append(L"....");
	tetris[5].append(L"....");
		   
	tetris[6].append(L"...X");
	tetris[6].append(L"XXXX");
	tetris[6].append(L"....");
	tetris[6].append(L"....");


	pField = new unsigned char[nFieldWidth * nFieldHeight];
	for (int x = 0; x < nFieldWidth; x++)
		for(int y = 0; y < nFieldHeight; y++)
		pField[y * nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;

	wchar_t *screen = new wchar_t[nScreenWidth*nScreenHeight];
	for (int i = 0; i < nScreenWidth*nScreenHeight; i++) screen[i] = L' ';
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	bool bGameOver = false;

	while (!bGameOver)
	{
		// Game timing ====

		//Input ====

		// Game Logic ==== Shape change, falling etc.

		// Render Output =====

		for (int x = 0; x < nFieldWidth; x++)
			for (int y = 0; y < nFieldHeight; y++)
				screen[(y + 2) * nScreenWidth + (x + 2)] = L" ABCDEFG=#"[pField[y * nFieldWidth + x]];

	WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, & dwBytesWritten);
	}
	return 0;
}