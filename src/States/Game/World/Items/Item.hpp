/*
 * File: Item.hpp
 * Project: Extermination
 * File Created: Wednesday, 16th February 2022 6:38:38 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Thursday, 29th December 2022 9:35:44 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */

#pragma once
#include <functional>

#include "Yuna.hpp"

class Item
{
protected:
	std::function<void()>	mPrimaryAction;
	std::function<void()>	mSecondaryAction;
	
	sf::Sprite				mIcon;
	std::string				mTexturePath;

	bool					mIsHands = false;

public:
	Item();
	~Item();

	void			UsePrimaryAction() {if (mPrimaryAction) mPrimaryAction();}
	void			AddPrimaryAction(std::function<void()> pAction) {mPrimaryAction = pAction;}
	void			UseSecondaryAction() {if (mSecondaryAction) mSecondaryAction();}
	void			AddSecondaryAction(std::function<void()> pAction) {mSecondaryAction = pAction;}

	void			SetIconPosition(const sf::Vector2f &pPosition) {mIcon.setPosition(pPosition);}

	std::string		GetItemTexturePath(){return (mTexturePath);}
	bool			IsHands(){return (mIsHands);}
	
	virtual void	Render(Yuna::Core::Window *pWindow);
	virtual void	RenderIcon(Yuna::Core::Window *pWindow);

};
