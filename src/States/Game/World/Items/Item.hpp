/*
 * File: Item.hpp
 * Project: Extermination
 * File Created: Wednesday, 16th February 2022 6:38:38 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 6th March 2022 6:58:14 pm
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

public:
	Item();
	~Item();

	void	UsePrimaryAction() {if (mPrimaryAction) mPrimaryAction();}
	void	AddPrimaryAction(std::function<void()> pAction) {mPrimaryAction = pAction;}
	void	UseSecondaryAction() {if (mSecondaryAction) mSecondaryAction();}
	void	AddSecondaryAction(std::function<void()> pAction) {mSecondaryAction = pAction;}

	virtual void	Render(Yuna::Core::Window *pWindow);

};
