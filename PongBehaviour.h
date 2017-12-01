#pragma once

#include "stdafx.h"
#include "Collision.h"
#include "ResourceManager.h"
#include "Behaviour.h"

class Entity;

class PongBehaviour : public Behaviour{
	ResourceManager<sf::Texture, std::string>* resourceManager;
	sf::Sprite sprite;
	sfld::Vector2f velocity_;

public:  
	PongBehaviour(ResourceManager<sf::Texture, std::string>* rm);
	~PongBehaviour();
	void collided(Entity* other, MTV v);
	void update(int frame_time); // has logic and physics
	void render(sf::RenderTarget* target); //Usage: target->draw(sprite)
	sf::Sprite* getSprite();
	void paintSprite();
	void sfmlEvent(sf::Event e);
};