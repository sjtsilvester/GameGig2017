#pragma once

#include "Vector.h"
#include "ResourceManager.h"
#include "Collision.h"
#include <memory.h>
#include <map>
#include "Behaviour.h"

class Behaviour; 
class EntityManager;
class ParticleEngine;

class Entity {
public:
	enum ENTITY_DYNAMICS{
		DYNAMIC_STATIC,
		DYNAMIC_MOVING
	};
	Entity(BehaviourMap* behaviour_map,
		EntityManager* entity_manager,
		sfld::Vector2f position,
		Behaviour::BEHAVIOUR_TYPE behaviour,
		ENTITY_DYNAMICS dynamic,
		bool scrolling,
		ParticleEngine* particle
	);

	void collided(Entity* other, MTV v);
	void update(int frame_time);
	void render(sf::RenderTarget* target);

	void takeDamage(int damage);
	int getHealth() const;
	
	sfld::Vector2f getVelocity() const;
	void setVelocity(sfld::Vector2f velocity);

	bool toDestroy() const;

	sf::Sprite* getSprite();
	sfld::Vector2f getPosition() const;
	void setPosition(sfld::Vector2f position);

	ENTITY_DYNAMICS getDynamic() const;
	void setDynamic(ENTITY_DYNAMICS dynamic);
	std::string getType() const;

	static const float scroll;
	void setBehaviour(Behaviour::BEHAVIOUR_TYPE type);

private:
	ParticleEngine* engine;
	void doOffset(sfld::Vector2f offset);
	void move(sfld::Vector2f velocity, int frame_time);

	int health_;

	sfld::Vector2f position_;
	std::string type_;

	std::unique_ptr<BehaviourMap> behaviour_map_;
	Behaviour* current_behaviour_;

	bool is_destroyed_;

	EntityManager* entity_manager_;
	ENTITY_DYNAMICS dynamic_;

	bool scrolling_;
};