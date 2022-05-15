#include "devattribute.h"
#include <iostream>

static HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
static HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;

void winPause()
{
	system("pause > nul");
}

void pause()
{
	_getch();
}

void setColor(consoleColor foreground, consoleColor background)
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | foreground));
}

const char* WinFileDialog(HWND hwnd,const char* mode,const char* lpstrFilters){
#if defined(_UNICODE)
	OPENFILENAMEA ofn{};
#elif defined(_MBCS)
	OPENFILENAME ofn{};
#endif
    char pathFile[255]{};
    HANDLE hf;

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = pathFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(pathFile);
    ofn.lpstrFilter = lpstrFilters;
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
#if defined(_UNICODE)
	if (GetSaveFileNameA(&ofn) == TRUE)
		hf = CreateFileA(ofn.lpstrFile,
#elif defined(_MBCS)
	if (GetSaveFileName(&ofn) == TRUE)
		hf = CreateFile(ofn.lpstrFile,
#endif
            GENERIC_READ,
            0,
            (LPSECURITY_ATTRIBUTES)NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            (HANDLE)NULL);
    return pathFile;
}

void GotoXY(short X, short Y, std::string print, consoleColor foreground, consoleColor background) 
{
	COORD cord = { X, Y };
	SetConsoleCursorPosition(hStdOut, cord);
	if (foreground != WHITE || background != BLACK) setColor(foreground, background);
	if (print != "") std::cout << print;
	if (foreground != WHITE || background != BLACK) setColor(WHITE, BLACK);
}

void sheetGenerator(int x, int y, const int sizeX, const int sizeY, int lengthX, int lengthY,int boardStyle,consoleColor text,consoleColor background) 
{
	std::string style[7][11] = {
		{ "║","═","╬","╠","╣","╦","╩","╚","╗","╝","╔" },
		{"│","─","┼","├","┤","┬","┴","╰","╮","╯","╭"},
		{ "│","─","┼","├","┤","┬","┴","└","┐","┘","┌" },
		{ "┃","━","╋","┣","┫","┳","┻","┗","┓","┛","┏" },
		{ "┋","╍","╋","┣","┫","┳","┻","┗","┓","┛","┏" },
		{ "█","▄","█","█","█","▄","█","█","▄","█","▄" },
		{ "█","█","█","█","█","█","█","█","█","█","█" }
	};
	utf.setUtfLocale();
	lengthY += 1;
	int buffsizeY = sizeY * lengthY + 1, buffX = x;
	setColor(text, background);
	for (int j = 0; j < sizeX; j++) {
		for (int i = 1; i <= buffsizeY; i++) {
			GotoXY(buffX, y + i - 1, style[boardStyle][0]);
			for (int k = 0; k < lengthX; k++)
				std::cout << " ";
			std::cout << style[boardStyle][0];
			if (i % lengthY == 1) {
				GotoXY(buffX, y + i - 1);
				for (int t = 0; t < lengthX + 1; t++)
					std::cout << style[boardStyle][1];
				for (int p = 0; p < lengthX + 1; p++)
					GotoXY(buffX, y + i - 1, style[boardStyle][2]);
				if (i != 1 && i != buffsizeY && j == 0)
					GotoXY(buffX, y + i - 1, style[boardStyle][3]);
				if (i != 1 && i != buffsizeY && j == sizeX - 1)
					GotoXY(buffX + lengthX + 1, y + i - 1, style[boardStyle][4]);
			}
			if (i == 1) {
				x = buffX + lengthX + 1;
				GotoXY(buffX, y + i - 1, style[boardStyle][5]);
			}
			if (i == buffsizeY && x == buffX + lengthX + 1)
				GotoXY(buffX, y + i - 1, style[boardStyle][6]);
		}
		buffX += lengthX + 1;
	}
	GotoXY(x - sizeX * (lengthX + 1), y + sizeY * lengthY, style[boardStyle][7]);
	GotoXY(x, y, style[boardStyle][8]);
	GotoXY(x, y + sizeY * lengthY, style[boardStyle][9]);
	GotoXY(x - sizeX * (lengthX + 1), y, style[boardStyle][10]);
	setColor(WHITE, BLACK);
}

void cleaning(int x, int y, int width, int height, consoleColor background) 
{
	int counter = 0, buff = y;
	if (background != BLACK) setColor(BLACK, background);
	for (int i = 0; i < height; i++) {
		GotoXY(x, buff++);
		for (int j = 0; j < width; j++)
			printf(" ");
	}
	setColor(WHITE, BLACK);
	GotoXY(x, y);
}

void setConsoleSize(int columnsX, int linesY) 
{
	std::string command = "mode con cols=" + std::to_string(columnsX) + " lines=" + std::to_string(linesY);
	system(command.c_str());
}

int getConsoleSize(std::string position) 
{
	GetConsoleScreenBufferInfo(hStdOut, &scrBufferInfo);
	short winWidth = scrBufferInfo.srWindow.Right - scrBufferInfo.srWindow.Left + 1;
	short winHeight = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;
	if (position == "width") return winWidth;
	if (position == "height") return winHeight;
	return 0;
}

void setConsoleFullscreen() 
{
	COORD newSize;
	short bufferHeight = getConsoleSize("height");
	short bufferWidth = scrBufferInfo.dwSize.X;
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, &newSize);
	keybd_event(VK_MENU, 0x38, 0, 0);
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
	newSize.X = bufferWidth;
	newSize.Y = bufferHeight;
	SetConsoleScreenBufferSize(hStdOut, newSize);
}

COORD getConsoleCursorPosition()
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(hStdOut, &cbsi))
		return cbsi.dwCursorPosition;
}

BOOL showConsoleCursor(BOOL bShow)
{
	CONSOLE_CURSOR_INFO cci;
	if (!GetConsoleCursorInfo(hStdOut, &cci)) return 0;
	cci.bVisible = bShow;
	if (!SetConsoleCursorInfo(hStdOut, &cci)) return 0;
	return 1;
}

void consoleResize(BOOL status) 
{
	HWND hwnd = GetConsoleWindow();
	HMENU hm{};
	hm = GetSystemMenu(hwnd, status);
	RemoveMenu(hm, SC_SIZE, MF_BYCOMMAND | MF_REMOVE);
	RemoveMenu(hm, SC_MAXIMIZE, MF_BYCOMMAND | MF_REMOVE);
	DrawMenuBar(hwnd);
	GetMenu(hwnd);
}

bool removeLineFromFile(std::string filename, int index) {
	std::vector<std::string> vec;
	std::ifstream file(filename);
	if (file.is_open())
	{
		std::string str;
		while (std::getline(file, str))
			vec.push_back(str);
		file.close();
		if (vec.size() < index - 1)
			return false;
		vec.erase(vec.begin() + index - 1);
		std::ofstream outfile(filename);
		if (outfile.is_open())
		{
			std::copy(vec.begin(), vec.end(),
				std::ostream_iterator<std::string>(outfile, "\n"));
			outfile.close();
			return true;
		}
		return false;
	}
	return false;
}

LONG calc_percentof64(_In_ LONG64 length, _In_ LONG64 total_length)
{
	LONG value;
	value = (LONG)(((DOUBLE)length / (DOUBLE)total_length) * 100.0);
	return value;
}

void setConsoleNoSelection(BOOL status) 
{
	DWORD prev_mode{};
	if (status == 1) {
		GetConsoleMode(hStdIn, &prev_mode);
		SetConsoleMode(hStdIn, prev_mode & ~ENABLE_QUICK_EDIT_MODE);
		return;
	}
	if (status == 0) {
		SetConsoleMode(hStdIn, prev_mode);
		return;
	}
}

COORD setConsoleButton(
	int x, int y, int width, int height, int countButtonsX, int countButtonsY,
	int returnButton, consoleColor inactiveButton, consoleColor activeButton, int YCorrect,int XCorrect, bool boarder,
	int boarder_style, consoleColor boarderColor,consoleColor backBoarderColor,
	std::string titles[], int titlesIndent, consoleColor titlesColor,int subReturn
)
{
	RECT r{};
	POINT p{};
	COORD** buttonCord = new COORD * [countButtonsY], numButton{};
	HWND wh = GetConsoleWindow();
	showConsoleCursor(FALSE);
	for (int i = 0; i < countButtonsY; i++) buttonCord[i] = new COORD[countButtonsX];
	if (boarder) sheetGenerator(x - 1, y - 1, countButtonsX, countButtonsY, width, height,boarder_style,boarderColor,backBoarderColor);
	for (int i = 0, tempY = y; i < countButtonsY; i++) {
		for (int j = 0, tempX = x; j < countButtonsX; j++) {
			if (inactiveButton != -1 || activeButton != -1)
				cleaning(tempX, tempY, width, height, inactiveButton);
			buttonCord[i][j].X = tempX;
			buttonCord[i][j].Y = tempY;
			if (titles != 0 && countButtonsX == 1) {
				GotoXY(tempX + titlesIndent, tempY + (height / 2), titles[i], titlesColor, inactiveButton);
			}
			else if (titles != 0 && countButtonsY == 1) {
				GotoXY(tempX + titlesIndent, tempY + (height / 2), titles[j], titlesColor, inactiveButton);
			}

			if (!boarder) tempX += width + 2;
			else tempX += width + 1;
		}

		tempY += height + 1;
	}
	int posX = 0, posY = 0, buttonActive = 0, i = 0, j = 0, tempCordX = 0, tempCordY = 0,
		mCord = 0,buttonPointX = 0, buttonPointY = 0; // переменные для проверки находится или нет курсор на конкретной кнопке
	while (true) {
		GetWindowRect(wh, &r);
		GetCursorPos(&p);
		posX = ((p.x - r.left) / (8-XCorrect));
		posY = ((p.y - r.top) / (16-YCorrect));
		for (i = 0; i < countButtonsY; i++) {
			for (j = 0; j < countButtonsX; j++) {
				if (countButtonsX <= countButtonsY) mCord = i;
				else mCord = j;
					if (posX >= buttonCord[i][j].X && posX <= buttonCord[i][j].X + width && posY >= buttonCord[i][j].Y && posY <= buttonCord[i][j].Y + height) {
						if (tempCordX != buttonCord[i][j].X || tempCordY != buttonCord[i][j].Y) {
							if (inactiveButton != NUL && activeButton != NUL) {
								cleaning(buttonCord[i][j].X, buttonCord[i][j].Y, width, height, activeButton);
								if (titles != 0)
									GotoXY(buttonCord[i][j].X + titlesIndent, buttonCord[i][j].Y + (height / 2), titles[mCord], titlesColor, activeButton);
								if (tempCordX != 0 || tempCordY != 0) {
									cleaning(tempCordX, tempCordY, width, height, inactiveButton);
									if (titles != 0)
										GotoXY(tempCordX + titlesIndent, tempCordY + (height / 2), titles[mCord + 1], titlesColor, inactiveButton);
								}
							}
							tempCordX = buttonCord[i][j].X;
							tempCordY = buttonCord[i][j].Y;

						}
						buttonPointY = i; buttonPointX = j;
						if (GetKeyState(returnButton) < 0 || GetKeyState(subReturn)<0) {
							for (int i = 0; i < countButtonsY; i++) // очистка памяти под массив координат кнопок
								delete[] buttonCord[i];
							delete[] buttonCord;
							if (GetKeyState(subReturn) < 0 && (countButtonsY != 1 || countButtonsX != 1)) {
								numButton.X = (j + 1) * -1;
								numButton.Y = (i + 1) * -1;
							}
							else if (countButtonsY != 1 || countButtonsX != 1) {
								numButton.X = j+1;
								numButton.Y = i+1;
							}
							else {
								numButton.X = 1;
								numButton.Y = 1;
							}
							return numButton;
						}
					}
					else if (inactiveButton != NUL &&i == buttonPointY && buttonPointX == j && (tempCordX != 0 || tempCordY != 0)) {
						cleaning(tempCordX, tempCordY, width, height, inactiveButton);
						if (titles != 0) 
							GotoXY(tempCordX + titlesIndent,tempCordY + (height / 2), titles[mCord], titlesColor, inactiveButton);
						tempCordX = 0;
						tempCordY = 0;
					}
			}

		}
		if (GetKeyState(VK_ESCAPE) < 0) {
			for (int i = 0; i < countButtonsY; i++) 
				delete[] buttonCord[i];
			delete[] buttonCord;
			numButton.X = 0;
			numButton.Y = 0;
			return numButton;
		}
		Sleep(60);
	}
}

std::string printFilter(int length, int x, int y, std::string mode, std::string min, std::string max, int minDig, int maxDig)
{
	if (mode.length() > 3 && min < "0" || mode.length() >3 && max > "9") {
		min = "0"; max = "9";
	}
	std::wstring wmin = utf.stows(min), wmax = utf.stows(max);
	int factive = 0;
	std::wstring buff;
	for (int i = 0; i <= length + 1; i++) {
	m: std::wstring key;
		key += _getwch();
		if (i == length + 1) {
			i--;
			goto m;
		}
		if (GetAsyncKeyState(VK_DOWN) != 0 || GetAsyncKeyState(VK_UP) != 0 ||
			GetAsyncKeyState(VK_LEFT) != 0 || GetAsyncKeyState(VK_RIGHT) != 0) goto m;
		if (GetAsyncKeyState(VK_ESCAPE) != 0) return "0";
		if (GetAsyncKeyState(VK_BACK) != 0) {
			if (i != 0) {
				if (i == factive)
					factive = 0;
				i--;
				buff.erase(buff.length() - 1, 1);
				GotoXY(x + i, y, utf.wstos(key));
				GotoXY(x + i, y, " ");
				GotoXY(x + i, y);
			}
			goto m;
		}
		if (GetAsyncKeyState(VK_RETURN) != 0 && i != 0) {
			if (mode.length() > 3 && stof(buff) < minDig || mode.length() > 3 && stof(buff) > maxDig)
				goto m;
			return utf.wstos(buff);
		}
		if (mode == "str" && key < wmin || key > wmax || mode.length() > 4 && key < wmin || key > wmax)
			goto m;
		if (mode == "calc") {
			if (key < wmin && key != L"-" && key != L"." || key > wmax && key != L"-" && key != L".")
				goto m;
			if (key == L"-" && i != 0) goto m;
			if (key == L".") {
				if (factive != 0 || i == 0) goto m;
				factive = i;
			}
		}
		if (i != length) {
			buff += key;
			GotoXY(x + i, y, utf.wstos(key));
		}
	}
}

