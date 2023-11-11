#pragma once
#include "Pickable.hpp"
#include "Yuna.hpp"

#include <list>

class PickableManager
{
private:
	std::list<Pickable> pickables;
	
public:
	PickableManager(/* args */);
	~PickableManager();

	void		update(double dt);
	void		addPickable(const Pickable &pickable);
	void		removePickable(const Pickable &pickable);
	Pickable	*checkCollision(const sf::FloatRect &rect);
	void		render(Yuna::Core::Window *window);
};

