#pragma once

#include "BaseState.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "Behaviour.h"

class EntityManager;
class WorldManager;
class Entity;
class ParticleEngine;

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

	void createBullet(sfld::Vector2f velocity, sfld::Vector2f position);

private:
	void load(std::string texture);

	void createWall(int time, int y);
	void createShooter(int time, int y);
	void createGhost(int time, int y);
	void createGoomba(int time, int y);
	void createPacfood(int time, int y);


	ResourceManager<sf::Texture, std::string> rm_;

	Entity* player;

	std::unique_ptr<WorldManager> world_manager_;
	std::unique_ptr<EntityManager> entity_manager_;
	std::unique_ptr<ParticleEngine> particle_manager_;

	sf::Texture texture;
};