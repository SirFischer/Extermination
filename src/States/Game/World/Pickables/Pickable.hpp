#pragma once
#include "Yuna.hpp"

#include <SFML/Graphics.hpp>

enum class PickableType
{
	CRATE,
	GRATE,
	COIN
};

class Pickable
{
protected:
	sf::Sprite	mSprite;
	sf::Vector2f mPosition;
	PickableType mType;

	float mTime = 0;

public:
	Pickable(Yuna::Core::ResourceManager *pResourceManager, sf::Vector2f position);
	~Pickable();

	bool operator==(const Pickable &pickable) const { return mPosition == pickable.mPosition; }

	sf::FloatRect 	getGlobalBounds() const { return mSprite.getGlobalBounds(); }
	PickableType 	getType() const { return mType; }

	virtual void update(float dt);
	virtual void render(Yuna::Core::Window *window);
};

