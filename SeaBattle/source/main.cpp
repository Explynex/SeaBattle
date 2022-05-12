#include "output.h"

short width, height;

int main() {
	utf.setUtfLocale();
	setConsoleFullscreen();
	Sleep(100);
	srand(time(NULL));
	setConsoleNoSelection(TRUE);
	width = getConsoleSize("width");

	height = getConsoleSize("height");
	mainMenu();
}