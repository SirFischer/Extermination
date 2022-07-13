/*
 * File: Entity.hpp
 * Project: Extermination
 * File Created: Saturday, 23rd October 2021 12:20:07 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Tuesday, 12th July 2022 8:42:39 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once

#include "Yuna.hpp"
#include "Animation.hpp"
#include "Config.hpp"
#include "../Items/Item.hpp"

enum class EntityType {
	ENTITY,
	PLAYER,
	ENEMY
};

class Entity
{
protected:
	enum class				eAnimationAction
	{
		IDLE,
		WALK,
		FALL
	};

	sf::Sprite				mSprite;
	sf::Vector2f			mPosition = sf::Vector2f(100, -400);
	sf::Vector2f			mSize = sf::Vector2f(48, 64);
	sf::Vector2f			mOrigin = sf::Vector2f(0, 0);
	sf::Vector2f			mVelocity = sf::Vector2f(0, 0);
	sf::Vector2f			mTarget = sf::Vector2f(0, 0);
	float					mHealth = 100.f;
	float					mSpeed = 100.f;
	float					mJumpForce = 650.f;
	bool					mFacingLeft = false;
	bool					mOnGround = false;

	//Time
	sf::Clock				mFallClock;
	sf::Clock				mPathRecalculationClock;

	std::shared_ptr<Item>	mEquipedItem;
	EntityType				mType = EntityType::ENTITY;
	std::vector<
	Yuna::AI::PathNode>		mPath;

	std::map<
		eAnimationAction,
		Animation>			mAnimations;
	eAnimationAction		mCurrentAnimation = eAnimationAction::IDLE;
	
public:
	friend class Map;

	Entity(/* args */);
	~Entity();

	virtual void	Init(Yuna::Core::ResourceManager *pResourceManager);
	

	virtual void	Update(Yuna::Core::EventHandler *pEventHandler, float mDeltaTime);
	virtual void	Render(Yuna::Core::Window *pWindow);

	virtual void	Attack(Entity *pTarget);
	virtual void	TakeDamage(float pDamage);
	virtual void	TakeDamage(float pDamage, float pAngle, float pPower);

	void			ResolveCollision(Entity *pEntity);

	void			SetSize(float pX, float pY) {mSize = sf::Vector2f(pX, pY);}
	void			SetOrigin(float pX, float pY) {mOrigin = sf::Vector2f(pX, pY);}
	void			SetPath(const std::vector<Yuna::AI::PathNode> &pPath) {mPath = pPath; mPathRecalculationClock.restart();}
	void			SetTarget(const sf::Vector2f &pTarget) {mTarget = pTarget;}
	void			SetPosition(const sf::Vector2f &pPosition) {mPosition = pPosition;}

	bool			IsAlive(){return (mHealth > 0.f);}
	bool			IsFacingLeft(){return (mFacingLeft);}

	sf::Vector2f	GetPosition() {return (mPosition);}
	sf::Vector2f	GetVelocity() {return (mVelocity);}
	sf::FloatRect	GetGlobalBounds() {return (sf::FloatRect(mPosition + mOrigin, mSize));}
	EntityType		GetType() {return (mType);}
	sf::Time		GetPathRecalcTime() {return (mPathRecalculationClock.getElapsedTime());}
	sf::Vector2f	GetTarget() {return (mTarget);}

	/**
	 * Controls
	 **/
	virtual void	WalkLeft(float mDeltaTime);
	virtual void	WalkRight(float mDeltaTime);
	virtual void	Jump(float mDeltaTime);
};

