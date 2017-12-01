#include "EntityManager.h"
#include "Entity.h"

EntityManager::EntityManager() = default;
EntityManager::~EntityManager() = default;

void EntityManager::add(Entity* entity) {
	push_queue_.push_back(entity);
}

EntityList* EntityManager::getEntities() {
	return &entities_;
}

void EntityManager::update(int frame_time) {
	for (auto& it : entities_) {
		it->update(frame_time);
	}

	for (auto it = entities_.begin(); it != entities_.end();) {
		if ((*it)->toDestroy()) {
			it = entities_.erase(it);
		}
		else {
			it++;
		}
	}

	for (auto it = push_queue_.begin(); it != push_queue_.end();) {
		entities_.push_back(std::unique_ptr<Entity>(*it));
		it = push_queue_.erase(it);
	}
}

void EntityManager::render(sf::RenderTarget* target) {
	for (auto& it : entities_) {
		it->render(target);
	}
}