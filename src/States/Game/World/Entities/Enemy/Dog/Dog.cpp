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
	mSize = sf::Vector2f(mSprite.getGlobalBounds().width - 10, mSprite.getGlobalBounds().height - 10);
	mSprite.setOrigin(10, 10);
	mSprite.setScale(1.2, 1.2);
	mPosition.x = random() % 500 + 20000;
	mPosition.y = -random() % 500 - 200;
	mSpeed = 85.f;
	mHealth = 45.f;
	mJumpForce = 700.f;
	LoadAnimations();
}

void	Dog::Update(Yuna::Core::EventHandler *pEventHandler, float mDeltaTime)
{
	Enemy::Update(pEventHandler, mDeltaTime);
}

void	Dog::LoadAnimations()
{
	Animation idleAnimationLeft;
	idleAnimationLeft.AddFrame((AnimationFrame){.mRect = sf::IntRect(0, 64, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	idleAnimationLeft.AddFrame((AnimationFrame){.mRect = sf::IntRect(64, 64, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	idleAnimationLeft.AddFrame((AnimationFrame){.mRect = sf::IntRect(128, 64, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	idleAnimationLeft.AddFrame((AnimationFrame){.mRect = sf::IntRect(192, 64, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	
	Animation idleAnimationRight;
	idleAnimationRight.AddFrame((AnimationFrame){.mRect = sf::IntRect(0, 128, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	idleAnimationRight.AddFrame((AnimationFrame){.mRect = sf::IntRect(64, 128, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	idleAnimationRight.AddFrame((AnimationFrame){.mRect = sf::IntRect(128, 128, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	idleAnimationRight.AddFrame((AnimationFrame){.mRect = sf::IntRect(192, 128, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});

	Animation walkAnimationLeft;
	walkAnimationLeft.AddFrame((AnimationFrame){.mRect = sf::IntRect(0, 192, 64, 64), .mDuration = sf::seconds(0.05f), .mAction = nullptr});
	walkAnimationLeft.AddFrame((AnimationFrame){.mRect = sf::IntRect(64, 192, 64, 64), .mDuration = sf::seconds(0.05f), .mAction = nullptr});
	walkAnimationLeft.AddFrame((AnimationFrame){.mRect = sf::IntRect(128, 192, 64, 64), .mDuration = sf::seconds(0.05f), .mAction = nullptr});
	walkAnimationLeft.AddFrame((AnimationFrame){.mRect = sf::IntRect(192, 192, 64, 64), .mDuration = sf::seconds(0.05f), .mAction = nullptr});
	walkAnimationLeft.AddFrame((AnimationFrame){.mRect = sf::IntRect(256, 192, 64, 64), .mDuration = sf::seconds(0.05f), .mAction = nullptr});
	walkAnimationLeft.AddFrame((AnimationFrame){.mRect = sf::IntRect(320, 192, 64, 64), .mDuration = sf::seconds(0.05f), .mAction = nullptr});

	Animation walkAnimationRight;
	walkAnimationRight.AddFrame((AnimationFrame){.mRect = sf::IntRect(0, 256, 64, 64), .mDuration = sf::seconds(0.05f), .mAction = nullptr});
	walkAnimationRight.AddFrame((AnimationFrame){.mRect = sf::IntRect(64, 256, 64, 64), .mDuration = sf::seconds(0.05f), .mAction = nullptr});
	walkAnimationRight.AddFrame((AnimationFrame){.mRect = sf::IntRect(128, 256, 64, 64), .mDuration = sf::seconds(0.05f), .mAction = nullptr});
	walkAnimationRight.AddFrame((AnimationFrame){.mRect = sf::IntRect(192, 256, 64, 64), .mDuration = sf::seconds(0.05f), .mAction = nullptr});
	walkAnimationRight.AddFrame((AnimationFrame){.mRect = sf::IntRect(256, 256, 64, 64), .mDuration = sf::seconds(0.05f), .mAction = nullptr});
	walkAnimationRight.AddFrame((AnimationFrame){.mRect = sf::IntRect(320, 256, 64, 64), .mDuration = sf::seconds(0.05f), .mAction = nullptr});
	
	Animation hurtAnimationLeft;
	hurtAnimationLeft.AddFrame((AnimationFrame){.mRect = sf::IntRect(64, 320, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});

	Animation hurtAnimationRight;
	hurtAnimationRight.AddFrame((AnimationFrame){.mRect = sf::IntRect(64, 384, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});

	mAnimations.AddAnimation(eAnimationAction::IDLE, idleAnimationRight, idleAnimationLeft);
	mAnimations.AddAnimation(eAnimationAction::WALK, walkAnimationRight, walkAnimationLeft);
	mAnimations.AddAnimation(eAnimationAction::HURT, hurtAnimationRight, hurtAnimationLeft);
}