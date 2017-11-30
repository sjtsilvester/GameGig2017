#pragma once

#include "BaseState.h"

class DemoState : public BaseState {
public:
	DemoState();
	~DemoState();
	void sfmlEvent(sf::Event evt);
	void start();
	void pause();
	void resume();
	void exit();

	void update(int frame_time);
	void render(sf::RenderTarget* target);
};