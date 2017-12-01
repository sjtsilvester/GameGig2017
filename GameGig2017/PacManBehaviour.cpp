#include "stdafx.h"
#include "Collision.h"
#include "ResourceManager.h"
#include "PacManBehaviour.h"
#include "Entity.h"

//You will want to save rm to a private variable. To get a texture: rm->get("texture name"); We will load textures later.
PacManBehaviour::PacManBehaviour(ResourceManager<sf::Texture, std::string>* rm) {
	resourceManager = rm;
	speed = 0.2;
	setVelocity(sfld::Vector2f(speed, 0));

	//initialise sprite
	paintSprite();
	isFlashing = false;
	endFlash = 500;
	sprite.setOrigin(16, 16);
}

void PacManBehaviour::sfmlEvent(sf::Event evt) {}

void PacManBehaviour::collided(Entity* other, MTV v){
	if (other->getType() == "ghost") {
		takeDamage(10);
		isFlashing = true;
	}
	else if (other->getType() == "vulnerable ghost") {
		other->takeDamage(1000);
		isFlashing = true;
	}
	else if (other->getType() == "goomba") {
		takeDamage(10);
		isFlashing = true;
	}
	else if (other->getType() == "food") {
		other->takeDamage(1000);
	}
}

void PacManBehaviour::update(int frame_time) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		setVelocity(sfld::Vector2f(0, -speed));
		sprite.setRotation(270);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		setVelocity(sfld::Vector2f(-speed, 0));
		sprite.setRotation(180);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		setVelocity(sfld::Vector2f(0, speed));
		sprite.setRotation(90);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		setVelocity(sfld::Vector2f(speed, 0));
		sprite.setRotation(0);
	}

	if (isFlashing) {
		if (endFlash == 0) {
			isFlashing = false;
			endFlash = 500;			
			sprite.setColor(sf::Color(255, 255, 255));
		}
		else if (endFlash % 100 < 50) {
			sprite.setColor(sf::Color(255, 0, 0));
			endFlash--;
		}
		else {
			sprite.setColor(sf::Color(255, 255, 255));
			endFlash--;
		}
	}

}

//Usage: target->draw(sprite)
void PacManBehaviour::render(sf::RenderTarget* target) {
	target->draw(sprite);
}

void PacManBehaviour::paintSprite() {
	sprite.setTexture(resourceManager->get("pacman"));
}

sf::Sprite* PacManBehaviour::getSprite() {
	return &sprite;
}