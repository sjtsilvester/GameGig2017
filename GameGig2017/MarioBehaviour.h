#pragma once
#include "stdafx.h"
#include "Behaviour.h"

class MarioBehaviour : public Behaviour {
public:
	MarioBehaviour(ResourceManager<sf::Texture, std::string>* rm);
	~MarioBehaviour();
    void collided(Entity* other, MTV v);
	void update(int frameTime);
    void render(sf::RenderTarget* target);
	void sfmlEvent(sf::Event evt);
    sf::Sprite *getSprite();
    const double MAX_VSPEED = 1;
    const double GRAVITY = 0.002;
    const double HSPEED = 0.2;
    const double JUMP = 0.6;
    const int JUMP_TIME = 200;

private:
    ResourceManager<sf::Texture, std::string>* rm;
    sf::Sprite sprite;
    int jump_timer;
    bool can_jump;
};
