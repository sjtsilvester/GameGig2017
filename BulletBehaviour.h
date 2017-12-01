#pragma once

#include "stdafx.h"
#include "Collision.h"
#include "ResourceManager.h"
#include "Behaviour.h"

class Entity;

class BulletBehaviour : public Behaviour {
	ResourceManager<sf::Texture, std::string>* resourceManager;
	sf::Sprite sprite;
	sfld::Vector2f velocity_;
	ENTITY_SHAPE shape_;
	Entity* entity_;

public:
	BulletBehaviour(ResourceManager<sf::Texture, std::string>* rm);
	~BulletBehaviour();
	void collided(Entity* other, MTV v);
	void update(int frame_time);
	void render(sf::RenderTarget* target);

	void setVelocity(sfld::Vector2f velocity);
	sfld::Vector2f getVelocity();

	void setShape(ENTITY_SHAPE shape);
	ENTITY_SHAPE getShape();

	void takeDamage(int damage);
	int getHealth();

	void setEntity(Entity* entity);
	void paintSprite();
	void sfmlEvent(sf::Event e);

	sf::Sprite* getSprite();
};

