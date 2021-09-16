#ifndef ENGINE_SDL_HH
# define ENGINE_SDL_HH
# define MY_SDL_ENGINE
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include "driver/SDL/ImgTexture.hh"
# include "driver/SDL/SdlGameController.hh"
namespace engine {
    typedef engine::SdlGameController platformGameController;
    typedef engine::SdlTexture platformTexture;
};
#endif
