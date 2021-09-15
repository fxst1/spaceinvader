#include "driver/SDL/SdlGameController.hh"

engine::SdlGameController::SdlGameController(int width, int height, int fps):
	engine::GameController(),
	_width(width),
	_height(height),
	_fps(fps)
{
	SDL_CreateWindowAndRenderer(
		_width, _height, SDL_WINDOW_RESIZABLE,
		&_window, &_renderer
	);

	this->_engine.getScene().move(0, 0);
	this->_engine.getCamera().move(0, 0);

	this->_engine.getScene().resize(width + 1, height + 1);
	this->_engine.getCamera().resize(width, height);

	SDL_Rect r;
	r.x = 0;
	r.y = 0;
	r.w = width;
	r.h = height;

	SDL_RenderSetViewport(_renderer, &r);
}
engine::SdlGameController::~SdlGameController(void){}

void	engine::SdlGameController::loop(void) {

	std::uint32_t	minimum_fps_delta_time = 1000 / this->_fps;
	std::uint32_t	last_game_step = SDL_GetTicks();

	while (this->isRunning()) {

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
	}
}

int			engine::SdlGameController::getWidth(void) const {
	return (_width);
}
int			engine::SdlGameController::getHeight(void) const {
	return (_height);
}

void		engine::SdlGameController::onPreRender(void) {
	SDL_RenderClear(this->_renderer);
}
void		engine::SdlGameController::onPostRender(void) {
	SDL_RenderPresent(this->_renderer);
}
