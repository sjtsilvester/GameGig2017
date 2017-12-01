#include "Entity.h"
#include "EntityManager.h"

const float Entity::scroll = 0.1f;

Entity::Entity(BehaviourMap* behaviour_map,
	EntityManager* entity_manager,
	sfld::Vector2f position,
	std::string type,
	Behaviour::BEHAVIOUR_TYPE behaviour,
	ENTITY_DYNAMICS dynamic,
	bool scrolling
	) :
	is_destroyed_(is_destroyed_),
	entity_manager_(entity_manager),
	type_(type),
	dynamic_(dynamic),
	scrolling_(scrolling){

	behaviour_map_ = std::unique_ptr<BehaviourMap>(behaviour_map);

	setBehaviour(behaviour);
	setPosition(position);
}

void Entity::collided(Entity* other, MTV v) {
	current_behaviour_->collided(other, v);
}

std::string Entity::getType() const {
	return type_;
}

void Entity::update(int frame_time) {
	current_behaviour_->update(frame_time);
	if (dynamic_ == DYNAMIC_MOVING) {
		move(getVelocity(), frame_time);
	}
	else {
		doOffset(sfld::Vector2f(-1,0)*(float)scroll*(float)frame_time);
	}
	if (getPosition().x < -100 && getType() != "player") {
		is_destroyed_ = true;
	}
}

void Entity::render(sf::RenderTarget* target) {
	current_behaviour_->render(target);
}

sfld::Vector2f Entity::getVelocity() const {
	return current_behaviour_->getVelocity();
}

void Entity::setVelocity(sfld::Vector2f velocity) {
	current_behaviour_->setVelocity(velocity);
}

void Entity::setBehaviour(Behaviour::BEHAVIOUR_TYPE type) {
	current_behaviour_ = behaviour_map_->at(type).get();
	setPosition(getPosition()); //refresh position for new sprite
	getSprite()->setRotation(0);
}

void Entity::takeDamage(int damage) {
	health_ -= damage;
	if (health_ <= 0) {
		is_destroyed_ = true;
	}
}

int Entity::getHealth() const {
	return health_;
}

sf::Sprite* Entity::getSprite(){
	return current_behaviour_->getSprite();
}

void Entity::setPosition(sfld::Vector2f position) {
	position_ = position;
	getSprite()->setPosition(position_);
}

sfld::Vector2f Entity::getPosition() const {
	return position_;
}

Entity::ENTITY_DYNAMICS Entity::getDynamic() const {
	return dynamic_;
}

void Entity::setDynamic(ENTITY_DYNAMICS dynamic) {
	dynamic_ = dynamic;
}

void Entity::move(sfld::Vector2f velocity, int frame_time) {
	EntityList* list = entity_manager_->getEntities();
	if (scrolling_) {
		velocity -= sfld::Vector2f(scroll, 0);
	}
	if (getType() == "player" && getPosition().x <= 0 && velocity.x < 0) {
		velocity.x = 0;
	}
	if (getType() == "player" && getPosition().x >= 1024 && velocity.x > 0) {
		velocity.x = 0;
	}
	if (getType() == "player" && getPosition().y <= 0 && velocity.y < 0) {
		velocity.y = 0;
	}
	if (getType() == "player" && getPosition().y >= 768 && velocity.y > 0) {
		velocity.y = 0;
	}


	sfld::Vector2f direction = velocity.normalise();
	double mag = velocity.length();
	for (auto& it : *list) {
		if (it.get() != this) {
			float dist = sfld::Vector2f(it->getPosition() - getPosition()).length();
			if (dist <= TILE_SIZE*1.5f) { //need accurate collisions here
				MTV mtv(Collision::getCollision(*getSprite(), current_behaviour_->getShape(), *it->getSprite(), it->current_behaviour_->getShape()));
				if (!(mtv.axis == MTV::NONE.axis && mtv.overlap == MTV::NONE.overlap)) {
					//collided
					sfld::Vector2f n = mtv.axis;
					sfld::Vector2f comp_u(0, 0);

					if (direction.dot(n) < 0) {
						if (n != sfld::Vector2f(0, 0)) {
							comp_u = n * (direction.dot(n) / n.dot(n)); //component of hit axis in dir
						}
					}
					direction = direction - comp_u;
					collided(it.get(), mtv);
					if (it->getDynamic() == DYNAMIC_STATIC) { //because then it won't resolve its own collisions
						it->collided(this, mtv);
					}
				}
			}
			else {//otherwise, it's a circle, and we are only concerned with checking if they touch, no more
				if (dist <= TILE_SIZE*1.5f) {
					MTV mtv(Collision::getCollision(*getSprite(), current_behaviour_->getShape(), *it->getSprite(), current_behaviour_->getShape()));
					if (!(mtv.axis == MTV::NONE.axis && mtv.overlap == MTV::NONE.overlap)) {
						collided(it.get(), mtv);
						if (it->getDynamic() == DYNAMIC_STATIC) { //because then it won't resolve its own collisions
							it->collided(this, mtv);
						}
					}
				}
			}
		}
	}
	if (direction != sf::Vector2f(0, 0)) {
		//getSprite()->setRotation(sfld::maths::toDegrees(atan2(direction.y, direction.x)));
	}
	doOffset(direction*(float)mag*(float)frame_time);
}

void Entity::doOffset(sfld::Vector2f offset) {
	setPosition(getPosition() + offset);
}

bool Entity::toDestroy() const {
	return is_destroyed_;
}

