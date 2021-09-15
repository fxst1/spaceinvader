#ifndef MYENGINE
# define MYENGINE

# include "engine/types.hh"
# include "engine/box.hh"
# include "engine/entity.hh"
# include "engine/engine.hh"

# ifdef SDL_ENGINE
#  include "driver/SDL/SdlDrv.hh"
using engine::platformGameController = engine::SdlGameController;
# else
#  include "driver/ncurses/NCursesDrv.hh"
using engine::platformGameController = engine::SdlGameController;
# endif

#endif
