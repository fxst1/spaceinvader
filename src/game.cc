#include "spaceinvader.hh"
#include "gameobjects.hh"

Game::Game(void):
	engine::SdlGameController(WIDTH, HEIGHT),
	_oldscene(),
	_current_wave(nullptr)
{
	this->_textures["background"] = new engine::SdlTexture("textures/images/bg5.png", _renderer);
	this->_textures["spaceship"] = new engine::SdlTexture("textures/images/DurrrSpaceShip.png", _renderer);
	this->_textures["bullet"] = new engine::SdlTexture("textures/images/bullet.png", _renderer);
	this->_textures["bullet2"] = new engine::SdlTexture("textures/images/bullet2.png", _renderer);
	this->_textures["star"] = new engine::SdlTexture("textures/images/star.png", _renderer);
	this->_textures["explosion"] = new engine::SdlTexture("textures/images/explosion/sheet.png", _renderer);
	this->_textures["spider"] = new engine::SdlTexture("textures/images/enemy.png", _renderer);

	this->_textures["player_shield"] = new engine::SdlTexture("textures/images/shield.png", _renderer);

	this->_textures["pv_bar"] = new engine::SdlTexture("textures/images/hud/bar1.png", _renderer);
	this->_textures["pv_bar_color"] = new engine::SdlTexture("textures/images/hud/pv.png", _renderer);
	this->_textures["shield_bar"] = new engine::SdlTexture("textures/images/hud/bar2.png", _renderer);
	this->_textures["shield_bar_color"] = new engine::SdlTexture("textures/images/hud/shield.png", _renderer);

	this->_hud = new Hud(this);
}

Game::~Game(void) {
	delete this->_textures["background"];
	delete this->_textures["spaceship"];
	delete this->_textures["bullet"];
	delete this->_textures["bullet2"];
	delete this->_textures["star"];
	delete this->_textures["spider"];
	delete this->_textures["explosion"];
}

Hud*	Game::getHud(void) {
	return (_hud);
}

void	Game::tick(void) {
	this->populateBackground();

	if (!_waves.empty() && (_current_wave == nullptr || _current_wave->isEmpty())) {
		_current_wave = _waves.top();
		_waves.pop();
		_current_wave->populate( this->_engine, *this );
		this->_engine.addEntity(_current_wave);
	}

	this->_engine.tick();
}

void	Game::populateBackground(void) {

	std::random_device					rd;
	std::uniform_int_distribution<int>	pop_rand(1, 200);
	std::mt19937						rdengine(rd());

	if (pop_rand(rdengine) > 198) {

		std::uniform_int_distribution<int> y_rand(1, this->getHeight());

		engine::Entity	*bgstar = new BackgroundTexture(this->_textures["star"], 1);
		bgstar->move( this->getWidth(), y_rand(rdengine) );
		this->_engine.addEntity(bgstar);
	}

	this->_oldscene = this->_engine.getScene();
}

void	Game::onStart(void) {

	SpaceShip*	player = new SpaceShip(this->_textures["spaceship"], this->_textures["player_shield"]);
	player->resize( player->getTexture()->getW(), player->getTexture()->getH() );
	player->move(10, this->_engine.getScene().getH() / 2 - player->getH() / 2);
	this->_engine.addEntity( player );


	std::random_device rd;
	std::uniform_int_distribution<int> y_rand(1, this->getHeight());
	std::uniform_int_distribution<int> x_rand(1, this->getWidth());
	std::mt19937 rdengine(rd());

	std::size_t n = 0;

	engine::Box b1 = this->_engine.getScene();
	while (n < 5) {
		engine::Entity	*bgstar = new BackgroundTexture(this->_textures["star"], 1);
		bgstar->move(x_rand(rdengine), y_rand(rdengine));
		this->_engine.addEntity(bgstar);
		n++;
	}

//	MoveSinusFunc*	wave_sinus = new MoveSinusFunc(0.3, 200, 100);

	_waves.push( new Wave1_2() );
}

void		Game::onStop(void) {}

void		Game::onPreRender(void) {
	engine::SdlGameController::onPreRender();
	this->_textures["background"]->render(
		this->_engine.getScene()
	);

	_hud->render();
}

/******************************************/

BackgroundTexture::BackgroundTexture(engine::Texture *texture, engine::speed_t sp):
	engine::Entity()
{
	this->setMaxTimer(1000);
	this->setTexture(texture);
	this->setSpeed(sp);
	this->setZ(-1);
}
BackgroundTexture::~BackgroundTexture(void) {}
void 	BackgroundTexture::tick(engine::Engine & engine)
{
	this->moveRel(-1 * 	engine._delta_time, 0);
	(void)engine;
}


bool		BackgroundTexture::canOutScene(void) const {
	return (true);
}

void		BackgroundTexture::onOutScene(engine::Engine & engine) {
	if (this->getX() <= 0) {
		engine.removeEntity(this);
	}
}

void		BackgroundTexture::onDestroy(engine::Engine & engine) {
	(void)engine;
}

/******************************/

Explosion::Explosion(engine::Texture *t):
	engine::Animation(false, t)
{
	for (int x = 0; x <= 1024; x += 128) {

		for (int y = 0; y <= 1024; y += 128) {
			engine::Box b;
			b.move(y, x);
			b.resize(128, 128);
			this->addTexture(10, b);
		}

	}
}
Explosion::~Explosion(void)
{}

/******************************/

ExplosionEntity::ExplosionEntity(Game *g, engine::Box const & parent):
	engine::Entity(),
	_animation(nullptr)
{
	_animation = new Explosion(g->_textures["explosion"]);
	this->setTexture( _animation );

	this->setW(128);
	this->setH(128);

	this->center(parent);

	_animation->resize(128, 128);
	_animation->start();
}
ExplosionEntity::~ExplosionEntity(void)
{
	delete _animation;
}

void				ExplosionEntity::tick(engine::Engine & e) {
	this->_animation->tick(e);
	if (this->_animation->isStop()) {
		e.removeEntity( this );
	}
}

std::string ExplosionEntity::ID(void) const {
	return (":explosion");
}
