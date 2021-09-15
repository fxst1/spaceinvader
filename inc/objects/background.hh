#ifndef SPACEINVADER_BG_HH
# define SPACEINVADER_BG_HH
# include "engine/entity.hh"

class	BackgroundTexture : public engine::Entity {
	public:
		BackgroundTexture(engine::Texture *texture, engine::speed_t sp);
		virtual ~BackgroundTexture(void);

		virtual void 	tick(engine::Engine & engine);
		virtual bool	canOutScene(void) const;
		virtual void	onOutScene(engine::Engine & engine);
		virtual void	onDestroy(engine::Engine & engine);

};

#endif
