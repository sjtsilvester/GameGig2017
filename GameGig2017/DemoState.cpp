#include "stdafx.h"
#include "DemoState.h"

DemoState::DemoState() {}
DemoState::~DemoState() {}

void DemoState::sfmlEvent(sf::Event evt) {}
void DemoState::start() {}
void DemoState::pause() {}
void DemoState::resume() {}
void DemoState::exit() {}

void DemoState::update(int frame_time) {}

void DemoState::render(sf::RenderTarget* target) {
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);	
	target->draw(shape);
}