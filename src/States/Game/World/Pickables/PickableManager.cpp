#include "PickableManager.hpp"

PickableManager::PickableManager(/* args */)
{
}

PickableManager::~PickableManager()
{
}

void	PickableManager::update(double dt)
{
	//loop through list and update all entries
	for (auto &pickable : pickables)
		pickable.update(dt);
}

void	PickableManager::addPickable(const Pickable &pickable)
{
	pickables.push_back(pickable);
}

void	PickableManager::removePickable(const Pickable &pickable)
{
	pickables.remove(pickable);
}

Pickable	*PickableManager::checkCollision(const sf::FloatRect &rect)
{
	for (auto &pickable : pickables)
	{
		if (pickable.getGlobalBounds().intersects(rect))
			return &pickable;
	}
	return nullptr;
}


void	PickableManager::render(Yuna::Core::Window *window)
{
	for (auto &pickable : pickables)
		pickable.render(window);
}
