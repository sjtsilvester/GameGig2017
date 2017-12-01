#include "stdafx.h"
#include "Collision.h"
#include "ResourceManager.h"
#include "GhostBehaviour.h"
#include "Entity.h"

//You will want to save rm to a private variable. To get a texture: rm->get("texture name"); We will load textures later.
GhostBehaviour::GhostBehaviour(ResourceManager<sf::Texture, std::string>* rm) {
	resourceManager = rm;
	setVelocity(sfld::Vector2f(0, -0.2));
	scared = false;
	counter = 0;

	//initialise sprite
	paintSprite();
	sprite.setOrigin(16, 16);
}

void GhostBehaviour::sfmlEvent(sf::Event evt) {
}

void GhostBehaviour::collided(Entity* other, MTV v) {
	if (other->getType() == "pacman" && scared) {
		takeDamage(1000);
	}
	else if (other->getType() == "mario") {
		other->takeDamage(10);
		takeDamage(1000);
	}
}

void GhostBehaviour::update(int frame_time) {
	if (counter % 1000 < 500) {
		setVelocity(sfld::Vector2f(0, -0.2));
	}
	else{
		setVelocity(sfld::Vector2f(0, 0.2));
	}
	counter++;
}

//Usage: target->draw(sprite)
void GhostBehaviour::render(sf::RenderTarget* target) {
	target->draw(sprite);
}

void GhostBehaviour::paintSprite() {
	sprite.setTexture(resourceManager->get("ghost"));
}

sf::Sprite* GhostBehaviour::getSprite() {
	return &sprite;
}