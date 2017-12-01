#pragma once

#include "stdafx.h"
#include "Collision.h"
#include "ResourceManager.h"
#include "Behaviour.h"

class Entity;

class BulletBehaviour : public Behaviour {
	ResourceManager<sf::Texture, std::string>* resourceManager;
	sf::Sprite sprite;
	ENTITY_SHAPE shape_;
	Entity* entity_;

public:
	BulletBehaviour(ResourceManager<sf::Texture, std::string>* rm);
	~BulletBehaviour();
	void collided(Entity* other, MTV v);
	void update(int frame_time);
	void render(sf::RenderTarget* target);

	void paintSprite();
	void sfmlEvent(sf::Event e);

	sf::Sprite* getSprite();
};

