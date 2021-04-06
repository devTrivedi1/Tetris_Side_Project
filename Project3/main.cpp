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

bool DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY)
{

	for (int px = 0; px < 4; px++)
		for (int py = 0; py < 4; py++)
		{
			// Getting index into piece
			int pi = Rotate(px, py, nRotation);

			// Getting index into the field
			int fi = (nPosY + py) * nFieldWidth + (nPosX + px);

			if (nPosX + px >= 0 && nPosX + px < nFieldWidth) 
			{
				if (nPosY + py >= 0 && nPosY + py < nFieldHeight)
				{
					if (tetris[nTetromino][pi] == L'X' && pField[fi] != 0)
						return false; // fail on first hit
				}

			}

		}
	{
	
	}

	return true;
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

	int nCurrentPiece = 0;
	int nCurrentRotation = 0;
	int nCurrentX = nFieldWidth / 2;
	int nCurrentY = 0;


	while (!bGameOver)
	{
		// Game timing ====

		//Input ====

		// Game Logic ==== Shape change, falling etc.

		// Render Output =====

		//Drawing the field
		for (int x = 0; x < nFieldWidth; x++)
			for (int y = 0; y < nFieldHeight; y++)
				screen[(y + 2) * nScreenWidth + (x + 2)] = L" ABCDEFG=#"[pField[y * nFieldWidth + x]];

		//Drawing the current piece
		for (int px = 0; px < 4; px++)
			for (int py = 0; py < 4; py++)
				if (tetris[nCurrentPiece][Rotate(px, py, nCurrentRotation)] == L'X')
					screen[(nCurrentY + py + 2) * nScreenWidth + (nCurrentX + px + 2)] = nCurrentPiece + 65;


	 //Displaying the frame
	WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, & dwBytesWritten);
	}
	return 0;
}