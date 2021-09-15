/*
Gameover::Gameover(Game *g) {
	_gameover_text = g->_text_texture->createText("GAMEOVER");
	_score_text = g->_text_texture->createText( std::to_string(g->getScore()) );
	_retry_text = g->_text_texture->createText("Recommencer");
	_stop_text = g->_text_texture->createText("Arreter");
}
Gameover::~Gameover(void) {}

void	Gameover::onClick(engine::Entity* ent, engine::Engine& engine) {
	if (ent->ID() == "retry") {
		engine.getGameController()->stop();
		engine.getGameController()->start();
	} else if (ent->ID() == "stop") {
		engine.getGameController()->stop();
	}
}
*/
