#include "stdafx.h"
#include "Collision.h"
#include "ResourceManager.h"
#include "GoombaBehaviour.h"
#include "Entity.h"

//You will want to save rm to a private variable. To get a texture: rm->get("texture name"); We will load textures later.
GoombaBehaviour::GoombaBehaviour(ResourceManager<sf::Texture, std::string>* rm) {
	resourceManager = rm;
	setVelocity(sfld::Vector2f(-0.1, 0));
	flatTime = 500;
	flat = false;

	//initialise sprite
	paintSprite();
	sprite.setOrigin(16, 32);
}

void GoombaBehaviour::sfmlEvent(sf::Event evt) {}

void GoombaBehaviour::collided(Entity* other, MTV v) {
	if (other->getType() == "mario" && v.axis.y != 0 && !flat) {
		sprite.setScale(sf::Vector2f(1.0f, 0.4f));
		flat = true;
	}else if(other->getType() == "mario" && !flat){
		other->takeDamage(10);
	}
}

void GoombaBehaviour::update(int frame_time) {
	if (flat) {
		if (flatTime == 0) {
			takeDamage(1000);
		}
		else {
			flatTime--;
		}
	}

}

//Usage: target->draw(sprite)
void GoombaBehaviour::render(sf::RenderTarget* target) {
	target->draw(sprite);
}

void GoombaBehaviour::paintSprite() {
	sprite.setTexture(resourceManager->get("goomba"));
}

sf::Sprite* GoombaBehaviour::getSprite() {
	return &sprite;
}