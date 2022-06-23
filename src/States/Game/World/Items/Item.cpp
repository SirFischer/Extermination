/*
 * File: Item.cpp
 * Project: Extermination
 * File Created: Wednesday, 16th February 2022 6:38:54 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Thursday, 23rd June 2022 7:39:23 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#include "Item.hpp"

Item::Item()
{

}

Item::~Item()
{
}

void	Item::Render(Yuna::Core::Window *pWindow)
{
	(void)pWindow;
}

void	Item::RenderIcon(Yuna::Core::Window *pWindow)
{
	pWindow->Draw(mIcon);
}
