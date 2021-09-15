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
