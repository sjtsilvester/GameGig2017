#include "Behaviour.h"
#include "Entity.h"

void Behaviour::setVelocity(sfld::Vector2f velocity) {
	velocity_ = velocity;
}

sfld::Vector2f Behaviour::getVelocity() const{
	return velocity_;
}

void Behaviour::setShape(ENTITY_SHAPE shape) {
	shape_ = shape;
}

ENTITY_SHAPE Behaviour::getShape() const {
	return shape_;
}

void Behaviour::setEntity(Entity* entity) {
	entity_ = entity;
}

int Behaviour::getHealth() const{
	return entity_->getHealth();
}

void Behaviour::takeDamage(int amount) {
	entity_->takeDamage(amount);
}