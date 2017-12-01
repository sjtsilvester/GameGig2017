#pragma once
#include "Collision.h"
#include "ResourceManager.h"
#include "Behaviour.h"

class Entity;

class PacFoodBehaviour : public Behaviour {
private:
	ResourceManager<sf::Texture, std::string>* resourceManager;
	sf::Sprite sprite;

public:
	PacFoodBehaviour(ResourceManager<sf::Texture, std::string>* rm, Entity* player);
	void collided(Entity* other, MTV v);
	void update(int frame_time);
	void render(sf::RenderTarget* target); //Usage: target->draw(sprite)
	void sfmlEvent(sf::Event evt);
	void paintSprite();
	sf::Sprite* getSprite();
private:
	Entity* player_;
};
