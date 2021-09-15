#ifndef ENGINE_IMG_HH
# define ENGINE_IMG_HH

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>

# include "engine/box.hh"

namespace	engine {

	class	SdlTexture: public engine::Texture {
		private:
			SDL_Texture*		_texture;
			SDL_Renderer*		_renderer;
			double				_angle;
			SDL_RendererFlip	_flip;
			SDL_Point			_center;

		public:
			SdlTexture(std::string const &filename, SDL_Renderer* r);
			SdlTexture(std::string const &filename, SDL_Renderer* r, double angle, SDL_RendererFlip flip);
			SdlTexture(std::string const &filename, SDL_Renderer* r, double angle, int flip);
			virtual ~SdlTexture(void);

			void				useRenderer(SDL_Renderer* renderer);
			virtual void		render(engine::Box const &e);
	};

	class	SdlAnimation: public engine::Animation {
		public:
			SdlAnimation(bool cyclic, engine::Texture* r);
			virtual ~SdlAnimation(void);
	};

};

#endif
