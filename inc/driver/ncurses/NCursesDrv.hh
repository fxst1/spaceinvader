#ifndef ENGINE_NCURSES_HH
# define ENGINE_NCURSES_HH
# define MY_NCURSES_ENGINE
# include <ncurses.h>
# include "driver/ncurses/ascii.hh"
using engine::platformGameController = engine::NCursesGameController;
using engine::platformTexture = AsciiTexture;
#endif
