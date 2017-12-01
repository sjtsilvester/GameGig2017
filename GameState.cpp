#include "stdafx.h"
#include "GameState.h"
#include "EntityManager.h"
#include "Entity.h"
#include "DemoBehaviour.h"
#include "StaticBehaviour.h"
#include "PacManBehaviour.h"
#include "PongBehaviour.h"
#include "BulletBehaviour.h"

GameState::GameState() {}
GameState::~GameState() {}

void GameState::sfmlEvent(sf::Event evt) {}


void GameState::start() {
	

	rm_.setDirectory("media/images/");
	rm_.load("demo", "demo.png");
	rm_.load("wall", "wall.png");
	rm_.load("pacman", "pacman.png");
	rm_.load("pong", "pong.png");
	rm_.load("bullet", "bullet.png");

	entity_manager_ = std::unique_ptr<EntityManager>(new EntityManager());

	BehaviourMap* player_map = new BehaviourMap();
	player_map->insert(std::make_pair(Behaviour::BEHAVIOUR_TEST,
		std::unique_ptr<Behaviour>(new DemoBehaviour(&rm_))));
	player_map->insert(std::make_pair(Behaviour::BEHAVIOUR_PACMAN,
		std::unique_ptr<Behaviour>(new PacManBehaviour(&rm_))));
	player_map->insert(std::make_pair(Behaviour::BEHAVIOUR_PONG,
		std::unique_ptr<Behaviour>(new PongBehaviour(&rm_))));
	player_map->insert(std::make_pair(Behaviour::BEHAVIOUR_BULLET,
		std::unique_ptr<Behaviour>(new BulletBehaviour(&rm_))));

	entity_manager_->add(new Entity(
		player_map,
		entity_manager_.get(),
		sfld::Vector2f(200, 200),
		"demo",
		Behaviour::BEHAVIOUR_BULLET,
		Entity::DYNAMIC_MOVING)
	);

	BehaviourMap* wall_map0 = new BehaviourMap();
	wall_map0->insert(std::make_pair(Behaviour::BEHAVIOUR_STATIC,
		std::unique_ptr<Behaviour>(new StaticBehaviour(&rm_))));

	entity_manager_->add(new Entity(
		wall_map0,
		entity_manager_.get(),
		sfld::Vector2f(450, 450),
		"wall",
		Behaviour::BEHAVIOUR_STATIC,
		Entity::DYNAMIC_STATIC)
	);

	BehaviourMap* wall_map1 = new BehaviourMap();
	wall_map1->insert(std::make_pair(Behaviour::BEHAVIOUR_STATIC,
		std::unique_ptr<Behaviour>(new StaticBehaviour(&rm_))));

	entity_manager_->add(new Entity(
		wall_map1,
		entity_manager_.get(),
		sfld::Vector2f(400, 400),
		"wall",
		Behaviour::BEHAVIOUR_STATIC,
		Entity::DYNAMIC_STATIC)
	);
}

void GameState::pause() {}
void GameState::resume() {}
void GameState::exit() {}

void GameState::update(int frame_time) {
	entity_manager_->update(frame_time);
}

void GameState::render(sf::RenderTarget* target) {
	entity_manager_->render(target);
}