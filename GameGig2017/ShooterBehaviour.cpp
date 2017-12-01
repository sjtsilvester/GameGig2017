#include "ShooterBehaviour.h"
#include "Entity.h"
#include "GameState.h"
#include "SoundManager.h"

ShooterBehaviour::ShooterBehaviour(ResourceManager<sf::Texture, std::string>* rm,
	Entity* player, GameState* gameState) {
	rm_ = rm;
	player_ = player;
	gameState_ = gameState;
	sprite = sf::Sprite(rm->get("shooter"));
	timer = 0;
	r = 0;
	shoottimer = 0;
	setVelocity(sfld::Vector2f(0, -0.05));
}

void ShooterBehaviour::collided(Entity* other, MTV v) {
	if (other == player_ && other->getType() != "pong") {
		player_->takeDamage(10);
		takeDamage(1000);
	}
}

void ShooterBehaviour::update(int frameTime) {
	timer += frameTime;
	shoottimer += frameTime;
	if (timer > r) {
		timer = 0;
		r = rand() % 2500 + 500;
		setVelocity(sfld::Vector2f(0, -getVelocity().y));
	}
	if (shoottimer > 1500) {
		SoundManager::play("lasershoot");
		shoottimer = 0;
		sfld::Vector2f dir = player_->getPosition() - entity_->getPosition();
		dir = dir.normalise();
		gameState_->createBullet(dir * 0.5f, entity_->getPosition());
	}
}

void ShooterBehaviour::render(sf::RenderTarget* target) {
	target->draw(sprite);
}

void ShooterBehaviour::sfmlEvent(sf::Event evt) {
}

sf::Sprite* ShooterBehaviour::getSprite() {
	return &sprite;
}
