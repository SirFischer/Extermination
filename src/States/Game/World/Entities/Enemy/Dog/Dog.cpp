#include "Dog.hpp"

Dog::Dog(/* args */)
{
}

Dog::~Dog()
{
}

void	Dog::Init(Yuna::Core::ResourceManager *pResourceManager)
{
	mSprite.setTexture(*pResourceManager->LoadTexture("assets/images/enemy/Dog/Dog.png"));
	mSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	mSprite.setScale(1.2, 1.2);
	mSize = sf::Vector2f(mSprite.getGlobalBounds().width - 10, mSprite.getGlobalBounds().height - 10);
	mPosition.x = random() % 500 + 20000;
	mPosition.y = -random() % 500 - 200;
	mSpeed = 85.f;
	mHealth = 45.f;
	mJumpForce = 550.f;
	//LoadAnimations();
}