#include "stdafx.h"
#include "GameState.h"
#include "EntityManager.h"
#include "Entity.h"
#include "DemoBehaviour.h"
#include "StaticBehaviour.h"
#include "PacManBehaviour.h"
#include "WorldManager.h"
#include "MarioBehaviour.h"
#include "PongBehaviour.h"
#include "BulletBehaviour.h"
#include "ShooterBehaviour.h"
#include "GhostBehaviour.h"
#include "GoombaBehaviour.h"
#include "PacFoodBehaviour.h"
#include "ParticleEngine.h"
#include "SoundManager.h"

#include <iostream>
#include <fstream>  

#include "SoundManager.h"

GameState::GameState() {}
GameState::~GameState() {}

void GameState::sfmlEvent(sf::Event evt) {
	if (evt.type == sf::Event::KeyPressed) {
		if (evt.key.code == sf::Keyboard::I) {
			SoundManager::play("swapcharacter");
			player->setBehaviour(Behaviour::BEHAVIOUR_PONG);
		}
		else if (evt.key.code == sf::Keyboard::O) {
			SoundManager::play("swapcharacter");
			player->setBehaviour(Behaviour::BEHAVIOUR_MARIO);
		}
		else if (evt.key.code == sf::Keyboard::P) {
			SoundManager::play("swapcharacter");
			player->setBehaviour(Behaviour::BEHAVIOUR_PACMAN);
		}
	}
}


void GameState::start() {

	texture.loadFromFile("media/images/mario_background.png");

	rm_.setDirectory("media/images/");
	rm_.load("mario", "mario.png");
	rm_.load("wall", "wall.png");
	rm_.load("pacman", "pacman.png");
	rm_.load("pong", "pong.png");
	rm_.load("shooter", "shooter.png");
	rm_.load("bullet", "bullet.png");
	rm_.load("ghost", "ghost.png");
	rm_.load("goomba", "goomba.png");
	rm_.load("pacfood", "pacfood.png");

	SoundManager::add("death", "media/sounds/death.wav");
	SoundManager::add("goombadeath", "media/sounds/goomba_death.wav");
	SoundManager::add("jump", "media/sounds/Jump.wav");
	SoundManager::add("lasershoot", "media/sounds/Laser_shoot.wav");
	SoundManager::add("pickupcoin", "media/sounds/Pickup_coin.wav");
	SoundManager::add("swapcharacter", "media/sounds/Swap_character.wav");

	SoundManager::addMusic("music", "media/sounds/gj2017.wav");
	SoundManager::playMusic("music");


	particle_manager_ = std::unique_ptr<ParticleEngine>(new ParticleEngine());
	entity_manager_ = std::unique_ptr<EntityManager>(new EntityManager());
	world_manager_ = std::unique_ptr<WorldManager>(new WorldManager(entity_manager_.get()));

	BehaviourMap* player_map = new BehaviourMap();
	player_map->insert(std::make_pair(Behaviour::BEHAVIOUR_PACMAN,
		std::unique_ptr<Behaviour>(new PacManBehaviour(&rm_))));
	player_map->insert(std::make_pair(Behaviour::BEHAVIOUR_MARIO,
		std::unique_ptr<Behaviour>(new MarioBehaviour(&rm_))));
	player_map->insert(std::make_pair(Behaviour::BEHAVIOUR_PONG,
		std::unique_ptr<Behaviour>(new PongBehaviour(&rm_))));

	player = new Entity(
		player_map,
		entity_manager_.get(),
		sfld::Vector2f(200, 200),
		Behaviour::BEHAVIOUR_PONG,
		Entity::DYNAMIC_MOVING,
		false, particle_manager_.get()
	);
	player->takeDamage(-100);
	entity_manager_->add(player);

	createShooter(1000, 500);
	createShooter(2000, 200);

	load("testlevel.png");
}

void GameState::createWall(int t, int y) {
	BehaviourMap* wall_map = new BehaviourMap();
	wall_map->insert(std::make_pair(Behaviour::BEHAVIOUR_STATIC,
		std::unique_ptr<Behaviour>(new StaticBehaviour(&rm_))));

	world_manager_->addEntity(t, new Entity(
		wall_map,
		entity_manager_.get(),
		sfld::Vector2f(0, 0),
		Behaviour::BEHAVIOUR_STATIC,
		Entity::DYNAMIC_STATIC,
		true, particle_manager_.get()), y
	);
}

void GameState::createShooter(int t, int y) {
	BehaviourMap* wall_map = new BehaviourMap();
	wall_map->insert(std::make_pair(Behaviour::BEHAVIOUR_SHOOTER,
		std::unique_ptr<Behaviour>(new ShooterBehaviour(&rm_, player, this))));

	world_manager_->addEntity(t, new Entity(
		wall_map,
		entity_manager_.get(),
		sfld::Vector2f(0, 0),
		Behaviour::BEHAVIOUR_SHOOTER,
		Entity::DYNAMIC_MOVING,
		true, particle_manager_.get()), y
	);
}

void GameState::createGhost(int t, int y) {
	BehaviourMap* wall_map = new BehaviourMap();
	wall_map->insert(std::make_pair(Behaviour::BEHAVIOUR_GHOST,
		std::unique_ptr<Behaviour>(new GhostBehaviour(&rm_))));

	world_manager_->addEntity(t, new Entity(
		wall_map,
		entity_manager_.get(),
		sfld::Vector2f(0, 0),
		Behaviour::BEHAVIOUR_GHOST,
		Entity::DYNAMIC_MOVING,
		true, particle_manager_.get()), y
	);
}

void GameState::createGoomba(int t, int y) {
	BehaviourMap* wall_map = new BehaviourMap();
	wall_map->insert(std::make_pair(Behaviour::BEHAVIOUR_GOOMBA,
		std::unique_ptr<Behaviour>(new GoombaBehaviour(&rm_))));

	world_manager_->addEntity(t, new Entity(
		wall_map,
		entity_manager_.get(),
		sfld::Vector2f(0, 0),
		Behaviour::BEHAVIOUR_GOOMBA,
		Entity::DYNAMIC_MOVING,
		true, particle_manager_.get()), y
	);
}

void GameState::createPacfood(int t, int y) {
	BehaviourMap* wall_map = new BehaviourMap();
	wall_map->insert(std::make_pair(Behaviour::BEHAVIOUR_FOOD,
		std::unique_ptr<Behaviour>(new PacFoodBehaviour(&rm_, player))));

	world_manager_->addEntity(t, new Entity(
		wall_map,
		entity_manager_.get(),
		sfld::Vector2f(0, 0),
		Behaviour::BEHAVIOUR_FOOD,
		Entity::DYNAMIC_MOVING,
		true, particle_manager_.get()), y
	);
}


void GameState::createBullet(sfld::Vector2f velocity, sfld::Vector2f position) {
	BehaviourMap* bullet_map = new BehaviourMap();
	bullet_map->insert(std::make_pair(Behaviour::BEHAVIOUR_BULLET,
		std::unique_ptr<Behaviour>(new BulletBehaviour(&rm_, player))));

	Entity* b = new Entity(
		bullet_map,
		entity_manager_.get(),
		position + 40.0f*velocity.normalise(),
		Behaviour::BEHAVIOUR_BULLET,
		Entity::DYNAMIC_MOVING,
		false, particle_manager_.get());
	b->setVelocity(velocity);
	entity_manager_->add(b);

}


void GameState::pause() {}
void GameState::resume() {}
void GameState::exit() {}

void GameState::update(int frame_time) {
	entity_manager_->update(frame_time);
	world_manager_->update(frame_time);
	particle_manager_->update(frame_time);
}

void GameState::render(sf::RenderTarget* target) {
	//particle_manager_->renderStatics(target);
	sf::Sprite s(texture);
	target->draw(s);
	entity_manager_->render(target);
	particle_manager_->renderParticles(target);
}

void GameState::load(std::string texture) {
	sf::Image level;
	level.loadFromFile("media/levels/" + texture);
	for (int x = 0; x < level.getSize().x; x++) {
		for (int y = 0; y < level.getSize().y; y++) {
			sf::Color color = level.getPixel(x, y);
			int t = x * 500;
			if (color == sf::Color(64, 64, 64)) { //grey
				createWall(t, y*32);
			}
			else if(color == sf::Color(255, 0, 0)) { //red
				createGhost(t, y * 32);
			}
			else if (color == sf::Color(255, 106, 0)) { //orange
				createGoomba(t, y * 32);
			}
			else if (color == sf::Color(255, 216, 0)) { //yellow-orange
				createShooter(t, y * 32);
			}
			else if (color == sf::Color(182, 255, 0)) { //light green
				createPacfood(t, y * 32);
			}
		}
	}
}