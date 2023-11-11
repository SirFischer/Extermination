#include "Pickable.hpp"
#include <math.h>

Pickable::Pickable(Yuna::Core::ResourceManager *pResourceManager, sf::Vector2f position)
: mPosition(position)
{

	mSprite.setTexture(*pResourceManager->LoadTexture("assets/textures/Coin.png"));
	mSprite.setOrigin(mSprite.getGlobalBounds().width / 2, mSprite.getGlobalBounds().height / 2);
	mSprite.setPosition(mPosition);
	mType = PickableType::COIN;
}

Pickable::~Pickable()
{
}

void Pickable::update(float dt)
{
	mTime += dt * 3.f;
	sf::Vector2f pos = mSprite.getPosition();
	pos.y += std::sin(mTime) * 0.3f;

	mSprite.setPosition(pos);
}

void Pickable::render(Yuna::Core::Window *window)
{
	window->Draw(mSprite);
}