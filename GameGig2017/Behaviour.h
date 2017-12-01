#pragma once

#include "ResourceManager.h"
#include "Collision.h"
#include <SFML/Graphics.hpp>
#include <map>
#include <memory.h>

class Entity;

class Behaviour {
public:
	enum BEHAVIOUR_TYPE {
		BEHAVIOUR_TEST,
		BEHAVIOUR_STATIC
	};

	virtual void collided(Entity* other, MTV v) = 0;
	virtual void update(int frame_time) = 0;
	virtual void render(sf::RenderTarget* target) = 0;
	virtual void sfmlEvent(sf::Event evt) = 0;

	void setVelocity(sfld::Vector2f velocity);
	sfld::Vector2f getVelocity() const;

	void setShape(ENTITY_SHAPE shape);
	ENTITY_SHAPE getShape() const;

	void takeDamage(int damage);
	int getHealth() const;

	void setEntity(Entity* entity);

	virtual sf::Sprite* getSprite() = 0;
private:
	sfld::Vector2f velocity_;
	ENTITY_SHAPE shape_;
	Entity* entity_;
};

typedef std::map<Behaviour::BEHAVIOUR_TYPE, std::unique_ptr<Behaviour>> BehaviourMap;


