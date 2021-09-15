#include "driver/ncurses/NCursesGameController.hh"

engine::NCursesGameController::NCursesGameController(int width, int height, int fps):
	engine::GameController(),
	_width(width),
	_height(height),
	_fps(fps)
{
    _window = newwin(height, width, 0, 0);
    box(_window, 0, 0);
    wrefresh(_window);

	this->_engine.getScene().move(0, 0);
	this->_engine.getCamera().move(0, 0);

	this->_engine.getScene().resize(width + 1, height + 1);
	this->_engine.getCamera().resize(width, height);

}
engine::NCursesGameController::~NCursesGameController(void){}

std::string         engine::NCursesGameController::getTexturePath() const {
    return ("/textures/ascii/");
}

engine::Texture*    engine::NCursesGameController::allocTexture(std::string const & name, std::string const & path) {
    this->_textures[name] = AsciiTexture::loadFromFile(this->getTexturePath() + path);
    return (this->_textures[name]);
}

void	engine::NCursesGameController::loop(void) {

	//std::uint32_t	minimum_fps_delta_time = 1000 / this->_fps;
	//std::uint32_t	last_game_step = SDL_GetTicks();

	while (this->isRunning()) {

        this->tick();
        wrefresh(_window);

/*
		std::uint32_t	now = SDL_GetTicks();
		if ((int)last_game_step <= (int)now) { // | vsync_enabled

			std::uint32_t	delta_time = now - last_game_step;
			if (delta_time > minimum_fps_delta_time) {
				delta_time = minimum_fps_delta_time; // slow down if the computer is too slow
			}

			_engine._delta_time = delta_time;

			SDL_Event	event;
			if (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					this->stop();
					break ;
				}
			}

			this->tick();

			last_game_step = now;
		} else {
			SDL_Delay(1);
		}

		*/
	}
}

int			engine::NCursesGameController::getWidth(void) const {
	return (_width);
}
int			engine::NCursesGameController::getHeight(void) const {
	return (_height);
}

void		engine::NCursesGameController::onPreRender(void) {
	werase(this->_window);
}
void		engine::NCursesGameController::onPostRender(void) {
	wrefresh(this->_window);
}
