#ifndef SPACEINVADER_HH
# define SPACEINVADER_HH

# define WIDTH 1200
# define HEIGHT 800

# include <stack>
# include <map>
# include <random>

# include "engine/MyEngine.hh"
# ifdef SDL_ENGINE
#  define TEXTUREPATH "ascii"
# else
#  define TEXTUREPATH "images"
# endif

class	Hud;
class	Wave;

class	Game: public engine::platformGameController {
	private:

		Hud*						_hud;
		engine::Box					_oldscene;

		void						populateBackground(void);
		void						tick(void);

	public:

		Game(void);
		~Game(void);

//		std::map<std::string, engine::Texture*>	_textures;
		std::stack<Wave*>						_waves;
		Wave*									_current_wave;

		virtual void			onPreRender(void);

		Hud*					getHud(void);

	protected:

		virtual void			onStart(void);
		virtual void			onStop(void);

		virtual void			onKey(engine::KeyManager::KeyEvent const & e);
};

class	Hud {

	private:

		engine::Texture*	_bar_pv_container;
		engine::Texture*	_bar_pv_fill;
		engine::Texture*	_bar_shield_container;
		engine::Texture*	_bar_shield_fill;
		engine::Texture*	_score_text;
		std::map<std::string,engine::Texture*>	_weapon_textures;

	public:
		int			_max_pv;
		int			_pv;
		int			_max_shield;
		int			_shield;
		int			_score;
		std::string	_weapon;

		Hud(Game *g);
		~Hud(void);

		void		render(void);

		void		updatePv(int pv);
		void		updateShield(int shield);
};

#endif
