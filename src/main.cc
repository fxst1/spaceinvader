#include "spaceinvader.hh"
#include <ctime>
#include <iostream>

int		main(int ac, char **av) {

#ifdef SDL_ENGINE
	SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
#else
    	initscr();			/* Start curses mode 		*/
		keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
		cbreak();
		noecho();
		nodelay(stdscr, TRUE);
		timeout(10);

		init_pair(0, COLOR_WHITE, COLOR_BLACK);
		init_pair(1, COLOR_WHITE, COLOR_BLACK);
		init_pair(2, COLOR_RED, COLOR_BLACK);
		init_pair(3, COLOR_GREEN, COLOR_BLACK);
		init_pair(4, COLOR_YELLOW, COLOR_BLACK);
		init_pair(5, COLOR_BLUE, COLOR_BLACK);
		init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(7, COLOR_CYAN, COLOR_BLACK);
		init_pair(8, COLOR_WHITE, COLOR_BLACK);
		//timeout(100);
#endif
//	if (ac == 2 && ::strcmp(av[1], "--space"))
	{
		Game		g;

		g.mainloop();
	}

#ifdef SDL_ENGINE
	IMG_Quit();
	SDL_Quit();
#else
    endwin();
#endif
	return (0);
	(void)ac;
	(void)av;
}
