#pragma once

#include "BaseState.h"
#include "ResourceManager.h"
#include "Behaviour.h"

class EntityManager;
class WorldManager;

class GameState : public BaseState {
public:
	GameState();
	~GameState();
	void sfmlEvent(sf::Event evt);
	void start();
	void pause();
	void resume();
	void exit();

	void update(int frame_time);
	void render(sf::RenderTarget* target);
private:
	void load(std::string texture);

	void createWall(int time, int y);

	ResourceManager<sf::Texture, std::string> rm_;

	std::unique_ptr<WorldManager> world_manager_;
	std::unique_ptr<EntityManager> entity_manager_;
};