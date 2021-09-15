#ifndef MYENGINE
# define MYENGINE

# include "engine/types.hh"
# include "engine/box.hh"
# include "engine/entity.hh"
# include "engine/engine.hh"

# ifdef SDL_ENGINE
#  include "driver/SDL/SdlDrv.hh"
# else
#  include "driver/ncurses/NCursesDrv.hh"
# endif

#endif
