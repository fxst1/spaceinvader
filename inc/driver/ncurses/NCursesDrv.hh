#ifndef ENGINE_NCURSES_HH
# define ENGINE_NCURSES_HH
# define MY_NCURSES_ENGINE
# include <ncurses.h>
# include "driver/ncurses/ascii.hh"

namespace engine {
    typedef engine::NCursesGameController platformGameController;
    typedef engine::AsciiTexture platformTexture;
};

#endif
