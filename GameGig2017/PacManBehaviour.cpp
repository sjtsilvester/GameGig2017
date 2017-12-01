#include "stdafx.h"
#include "Collision.h"
#include "ResourceManager.h"
#include "PacManBehaviour.h"


//You will want to save rm to a private variable. To get a texture: rm->get("texture name"); We will load textures later.
PacManBehaviour::PacManBehaviour(ResourceManager<sf::Texture, std::string>* rm) {
	resourceManager = rm;
	speed = 10.0;
	setVelocity(sfld::Vector2f(speed, 0));

	//initialise sprite
	sf::Texture texture = resourceManager->get("Pacman");
	paintSprite(texture);
	flash = 0;
}

void PacManBehaviour::collided(Entity* other, MTV v){
	if (other->getType() == "wall"){
		setVelocity(sfld::Vector2f(0.0,0.0));
	}
	else if (other->getType() == "normal ghost") {
		takeDamage(10);
		flash = 1;
	}
	else if (other->getType() == "vulnerable ghost") {
		other->die();
	}
}

void PacManBehaviour::update(double frame_time) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		setVelocity(sfld::Vector2f(0, speed));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		setVelocity(sfld::Vector2f(-speed, 0));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		setVelocity(sfld::Vector2f(0, -speed));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		setVelocity(sfld::Vector2f(speed, 0));
	}
	else {

	}

	if (flash > 0) {
		if (flash == 300) {
			flash = 0;
		}
		else {
			flash++;
			if (flash % 20 == 1) {
				sprite.setColor(sf::Color(255, 0, 0));
			}
			else if (flash % 20 == 0) {
				sprite.setColor(sf::Color(0, 0, 0));
			}
		}
	}

}

//Usage: target->draw(sprite)
void PacManBehaviour::render(sf::RenderTarget* target) {
	sf::Sprite *spr = getSprite();
	target->draw(sprite);
}

void PacManBehaviour::paintSprite(sf::Texture texture) {
	texture.setSmooth(true);
	sprite.setTexture(texture);
}

sf::Sprite* PacManBehaviour::getSprite() {
	return &sprite;
}