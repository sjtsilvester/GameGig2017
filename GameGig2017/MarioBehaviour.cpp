#include <SFML/Graphics/Texture.hpp>
#include "ResourceManager.h"
#include "MarioBehaviour.h"
#include "SoundManager.h"

MarioBehaviour::MarioBehaviour(ResourceManager<sf::Texture, std::string>* rm) {
    this->rm = rm;
    this->can_jump = false;
    this->jump_timer = JUMP_TIME;    // milliseconds
    sprite.setTexture(rm->get("mario"));
    setVelocity(sfld::Vector2f(0, 0));
}

void MarioBehaviour::collided(Entity *other, MTV v){
    if (v.axis.y < 0 && (abs(v.axis.y) > abs(v.axis.x))) {
        setVelocity(sfld::Vector2f(getVelocity().x, 0));
        can_jump = true;
        jump_timer = 0;
    }
}

void MarioBehaviour::sfmlEvent(sf::Event evt) {}

MarioBehaviour::~MarioBehaviour() {}

void MarioBehaviour::update(int frame_time) {
    setVelocity(getVelocity() + sfld::Vector2f(0, GRAVITY));
    if (getVelocity().y > MAX_VSPEED) {
        setVelocity(sfld::Vector2f(getVelocity().x, MAX_VSPEED));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        setVelocity(sfld::Vector2f(-HSPEED, getVelocity().y));
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        setVelocity(sfld::Vector2f(HSPEED, getVelocity().y));
    } else {
        setVelocity(sfld::Vector2f(0, getVelocity().y));
    }

    jump_timer--;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        if (jump_timer <= 0 && can_jump) {
			SoundManager::play("jump");
            setVelocity(sfld::Vector2f(getVelocity().x, -JUMP));
            jump_timer = JUMP_TIME;
            can_jump = false;
        }
    } else if (jump_timer < 0) {
        jump_timer = 0;
    }

}

void MarioBehaviour::render(sf::RenderTarget* target) {
    target->draw(sprite);
}


sf::Sprite* MarioBehaviour::getSprite() {
    return &sprite;
}
