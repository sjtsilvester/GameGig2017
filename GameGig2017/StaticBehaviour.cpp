#include "StaticBehaviour.h"

StaticBehaviour::StaticBehaviour(ResourceManager<sf::Texture, std::string>* rm) :rm_(rm) {
	sprite_ = sf::Sprite(rm_->get("wall"));
	setShape(SHAPE_SQUARE);
}

void StaticBehaviour::collided(Entity* other, MTV v) {

}

void StaticBehaviour::render(sf::RenderTarget* target) {
	target->draw(sprite_);
}

void StaticBehaviour::update(int frame_time) {
}

sf::Sprite* StaticBehaviour::getSprite() {
	return &sprite_;
}

void StaticBehaviour::sfmlEvent(sf::Event evt) {

}