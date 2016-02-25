#include "SDLUtils.h"

int main(int argc, char *argv[])
{
	if (!InitSDL())
		return 1;

	CloseSDL();

	return 0;
}
