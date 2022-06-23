/*
 * File: Player.cpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 8:12:50 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Thursday, 23rd June 2022 7:34:17 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#include "Player.hpp"


Player::Player(/* args */)
{
	mType = EntityType::PLAYER;
}

Player::~Player()
{
}

void	Player::LoadAnimations()
{
	mAnimations[eAnimationAction::IDLE].AddFrame((AnimationFrame){.mRect = sf::IntRect(0, 0, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	mAnimations[eAnimationAction::IDLE].AddFrame((AnimationFrame){.mRect = sf::IntRect(64, 0, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	mAnimations[eAnimationAction::IDLE].AddFrame((AnimationFrame){.mRect = sf::IntRect(128, 0, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	mAnimations[eAnimationAction::IDLE].AddFrame((AnimationFrame){.mRect = sf::IntRect(192, 0, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	mAnimations[eAnimationAction::WALK].AddFrame((AnimationFrame){.mRect = sf::IntRect(0, 64, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	mAnimations[eAnimationAction::WALK].AddFrame((AnimationFrame){.mRect = sf::IntRect(64, 64, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	mAnimations[eAnimationAction::WALK].AddFrame((AnimationFrame){.mRect = sf::IntRect(128, 64, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	mAnimations[eAnimationAction::WALK].AddFrame((AnimationFrame){.mRect = sf::IntRect(192, 64, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	mAnimations[eAnimationAction::FALL].AddFrame((AnimationFrame){.mRect = sf::IntRect(0, 128, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	mAnimations[eAnimationAction::FALL].AddFrame((AnimationFrame){.mRect = sf::IntRect(64, 128, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});

}

void	Player::Init(Yuna::Core::ResourceManager *pResourceManager)
{
	mSprite.setTexture(*pResourceManager->LoadTexture("assets/images/player/Soldier_01_tiles.png"));
	mSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	mSize = sf::Vector2f(mSprite.getGlobalBounds().width, mSprite.getGlobalBounds().height);
	LoadAnimations();

	//tmp should be added by world
	mInventory.AddItem(std::make_shared<Weapon>()); //pistol
	mInventory.AddItem(std::make_shared<Weapon>()); //machine gun
}

void	Player::Update(Yuna::Core::EventHandler *pEventhandler, float mDeltaTime)
{
	Entity::Update(pEventhandler, mDeltaTime);
	mInventory.Update(pEventhandler);
	
	if (pEventhandler->GetEventState((uint32_t)eAction::MOVE_RIGHT))
	{
		WalkRight(mDeltaTime);
	}
	if (pEventhandler->GetEventState((uint32_t)eAction::MOVE_LEFT))
	{
		WalkLeft(mDeltaTime);
	}
	if (pEventhandler->GetEventState((uint32_t)eAction::JUMP) && mOnGround)
	{
		mVelocity.y = -(mJumpForce * mDeltaTime);
	}
	if (pEventhandler->GetEventState((uint32_t)eAction::CROUCH))
	{
		mVelocity.y += mSpeed * mDeltaTime;
	}
	if (pEventhandler->GetEventState((uint32_t)eAction::USE_ITEM_1))
	{
		if (mInventory.GetSelectedItem())
		{
			mInventory.GetSelectedItem()->UsePrimaryAction();
		}
	}
	if (pEventhandler->GetEventState((uint32_t)eAction::USE_ITEM_2))
	{
		if (mInventory.GetSelectedItem())
		{
			mInventory.GetSelectedItem()->UseSecondaryAction();
		}
	}
	if (mFallClock.getElapsedTime() > sf::seconds(0.8))
	{
		mCurrentAnimation = eAnimationAction::FALL;
	}
	mVelocity.x *= ((mOnGround) ? 0.9f : 0.93f);
	mOnGround = false;
}

void	Player::EquipItem(Item *pItem)
{
	if (pItem)
	{
		mInventory.AddItem(std::shared_ptr<Item>(pItem));
	}
}

void	Player::Render(Yuna::Core::Window *pWindow)
{
	Entity::Render(pWindow);

	if (mInventory.GetSelectedItem())
	{
		mInventory.GetSelectedItem()->Render(pWindow);
	}

	auto tmpView = pWindow->GetView();
	pWindow->ResetView(true);
	mInventory.Render(pWindow);
	pWindow->SetView(tmpView);
}


