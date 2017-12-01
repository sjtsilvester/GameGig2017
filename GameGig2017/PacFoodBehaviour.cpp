#include "stdafx.h"
#include "Collision.h"
#include "ResourceManager.h"
#include "PacFoodBehaviour.h"
#include "Entity.h"

//You will want to save rm to a private variable. To get a texture: rm->get("texture name"); We will load textures later.
PacFoodBehaviour::PacFoodBehaviour(ResourceManager<sf::Texture, std::string>* rm, Entity* player) {
	resourceManager = rm;
	player_ = player;
	setVelocity(sfld::Vector2f(0, 0));

	//initialise sprite
	paintSprite();
	sprite.setOrigin(16, 16);
}

void PacFoodBehaviour::sfmlEvent(sf::Event evt) {
}

void PacFoodBehaviour::collided(Entity* other, MTV v) {
	if (other->getType() != "pacman" && other == player_) {
		other->takeDamage(10);
	}
	takeDamage(100);
}

void PacFoodBehaviour::update(int frame_time) {
}

//Usage: target->draw(sprite)
void PacFoodBehaviour::render(sf::RenderTarget* target) {
	target->draw(sprite);
}

void PacFoodBehaviour::paintSprite() {
	sprite.setTexture(resourceManager->get("pacfood"));
}

sf::Sprite* PacFoodBehaviour::getSprite() {
	return &sprite;
}