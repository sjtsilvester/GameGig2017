#include "stdafx.h"
#include "GameState.h"
#include "EntityManager.h"
#include "Entity.h"
#include "DemoBehaviour.h"
#include "StaticBehaviour.h"
#include "PacManBehaviour.h"
#include "WorldManager.h"

GameState::GameState() {}
GameState::~GameState() {}

void GameState::sfmlEvent(sf::Event evt) {}


void GameState::start() {
	rm_.setDirectory("media/images/");
	rm_.load("demo", "demo.png");
	rm_.load("wall", "wall.png");
	rm_.load("pacman", "pacman.png");

	entity_manager_ = std::unique_ptr<EntityManager>(new EntityManager());
	world_manager_ = std::unique_ptr<WorldManager>(new WorldManager(entity_manager_.get()));

	BehaviourMap* player_map = new BehaviourMap();
	player_map->insert(std::make_pair(Behaviour::BEHAVIOUR_TEST,
		std::unique_ptr<Behaviour>(new DemoBehaviour(&rm_))));
	player_map->insert(std::make_pair(Behaviour::BEHAVIOUR_PACMAN,
		std::unique_ptr<Behaviour>(new PacManBehaviour(&rm_))));

	entity_manager_->add(new Entity(
		player_map,
		entity_manager_.get(),
		sfld::Vector2f(200, 200),
		"demo",
		Behaviour::BEHAVIOUR_PACMAN,
		Entity::DYNAMIC_MOVING,
		false)
	);

	createWall(1000, 300);
	createWall(1000, 500);
	createWall(3000, 200);
	createWall(3500, 600);
}

void GameState::createWall(int t, int y) {
	BehaviourMap* wall_map = new BehaviourMap();
	wall_map->insert(std::make_pair(Behaviour::BEHAVIOUR_STATIC,
		std::unique_ptr<Behaviour>(new StaticBehaviour(&rm_))));

	world_manager_->addEntity(t, new Entity(
		wall_map,
		entity_manager_.get(),
		sfld::Vector2f(0, 0),
		"wall",
		Behaviour::BEHAVIOUR_STATIC,
		Entity::DYNAMIC_STATIC,
		true), y
	);
}

void GameState::pause() {}
void GameState::resume() {}
void GameState::exit() {}

void GameState::update(int frame_time) {
	entity_manager_->update(frame_time);
	world_manager_->update(frame_time);
}

void GameState::render(sf::RenderTarget* target) {
	entity_manager_->render(target);
}