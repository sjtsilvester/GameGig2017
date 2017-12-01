#include "DemoBehaviour.h"

DemoBehaviour::DemoBehaviour(ResourceManager<sf::Texture, std::string>* rm) :rm_(rm){
	sprite_ = sf::Sprite(rm_->get("demo"));
	setShape(SHAPE_CIRCLE);
}

void DemoBehaviour::collided(Entity* other, MTV v) {

}

void DemoBehaviour::render(sf::RenderTarget* target) {
	target->draw(sprite_);
}

void DemoBehaviour::update(int frame_time) {
	using namespace sf;
	sfld::Vector2f dir(0, 0);
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		dir.y--;
	}
	if(Keyboard::isKeyPressed(Keyboard::S)){
		dir.y++;
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		dir.x--;
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		dir.x++;
	}
	setVelocity(dir.normalise()*0.1f);
}

sf::Sprite* DemoBehaviour::getSprite() {
	return &sprite_;
}

void DemoBehaviour::sfmlEvent(sf::Event evt) {

}