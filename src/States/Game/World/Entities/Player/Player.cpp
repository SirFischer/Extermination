/*
 * File: Player.cpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 8:12:50 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 24th July 2022 7:52:54 pm
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
	mResourceManager = pResourceManager;
	mSprite.setTexture(*pResourceManager->LoadTexture("assets/images/player/Soldier_01_tiles_armless.png"));
	mArmlessTexture = *pResourceManager->LoadTexture("assets/images/player/Soldier_01_tiles_armless.png");
	mArmTexture = *pResourceManager->LoadTexture("assets/images/player/Soldier_01_tiles.png");
	mSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	mArm.setOrigin(sf::Vector2f(32, 32));
	mSize = sf::Vector2f(mSprite.getGlobalBounds().width, mSprite.getGlobalBounds().height);
	LoadAnimations();

	mArm.setTexture(*pResourceManager->LoadTexture("assets/images/player/Soldier_01_arm.png"));
	mItemSprite.setScale(0.35, 0.35);
	//tmp should be added by world
	mInventory.AddItem(std::make_shared<Hands>());
}

void	Player::HandleEvents(Yuna::Core::EventHandler *pEventhandler, float mDeltaTime)
{
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
	if (pEventhandler->GetEventState((uint32_t)eAction::NEXT_ITEM))
	{
		mInventory.NextItem();
		pEventhandler->SetEventState((uint32_t)eAction::NEXT_ITEM, false);
	}

	if (pEventhandler->GetEventState((uint32_t)eAction::PREVIOUS_ITEM))
	{
		mInventory.PreviousItem();
		pEventhandler->SetEventState((uint32_t)eAction::PREVIOUS_ITEM, false);
	}
	
}

void	Player::Update(Yuna::Core::EventHandler *pEventhandler, float mDeltaTime)
{
	static Item*	lastItem = nullptr;
	Entity::Update(pEventhandler, mDeltaTime);
	mArm.setPosition(mPosition + sf::Vector2f((mFacingLeft ? 36 : 28), 38));
	mInventory.Update();
	HandleEvents(pEventhandler, mDeltaTime);

	if (mFallClock.getElapsedTime() > sf::seconds(0.8)) mCurrentAnimation = eAnimationAction::FALL;
	
	mVelocity.x *= ((mOnGround) ? 0.9f : 0.93f);
	mOnGround = false;

	if (lastItem != mInventory.GetSelectedItem())
	{
		lastItem = mInventory.GetSelectedItem();
		if (lastItem->IsHands())
			mSprite.setTexture(mArmTexture);
		else
			mSprite.setTexture(mArmlessTexture);
		if (!lastItem->IsHands())
			mItemSprite.setTexture(*mResourceManager->LoadTexture(lastItem->GetItemTexturePath()));
	}
}

void	Player::EquipItem(Item *pItem)
{
	if (pItem)
	{
		mInventory.AddItem(std::shared_ptr<Item>(pItem));
	}
}

void	Player::RenderArm(Yuna::Core::Window *pWindow)
{
	sf::Vector2f delta = sf::Vector2f(pWindow->GetViewMousePos()) - mArm.getPosition();
	
	if (mFacingLeft)
	{
		mArm.setTextureRect(
			sf::IntRect(64, 0, -64, 64));
		mItemSprite.setOrigin(sf::Vector2f(54, 38));
		mItemSprite.setTextureRect(
			sf::IntRect(64, 0, -64, 64));
		float rotation = (-(std::atan2(delta.x, delta.y) / M_PI) * 180.f) - 30.f;
		mArm.setRotation(rotation);
		mItemSprite.setRotation(rotation - 60.f);
		mItemSprite.setPosition(mArm.getPosition() - sf::Vector2f(10.f * std::cos(((rotation - 60.f) / 180.f) * M_PI), 10.f * std::sin(((rotation - 60.f) / 180.f) * M_PI)));
	}
	else
	{
		mArm.setTextureRect(
			sf::IntRect(0, 0, 64, 64));
		mItemSprite.setOrigin(sf::Vector2f(10, 38));
		mItemSprite.setTextureRect(
			sf::IntRect(0, 0, 64, 64));
		float rotation = (-(std::atan2(delta.x, delta.y) / M_PI) * 180.f) + 30.f;
		mArm.setRotation(rotation);
		mItemSprite.setRotation(rotation + 60.f);
		mItemSprite.setPosition(mArm.getPosition() + sf::Vector2f(10.f * std::cos(((rotation + 60.f) / 180.f) * M_PI), 10.f * std::sin(((rotation + 60.f) / 180.f) * M_PI)));
	}
	pWindow->Draw(mItemSprite);
	pWindow->Draw(mArm);
}


void	Player::Render(Yuna::Core::Window *pWindow)
{
	Entity::Render(pWindow);

	if (mInventory.GetSelectedItem())
	{
		mInventory.GetSelectedItem()->Render(pWindow);
	}

	if (!mInventory.GetSelectedItem()->IsHands())
	{
		RenderArm(pWindow);
	}

	auto tmpView = pWindow->GetView();
	pWindow->ResetView(true);
	mInventory.Render(pWindow);
	pWindow->SetView(tmpView);
}


