/*
 * File: Utils.hpp
 * Project: Extermination
 * File Created: Saturday, 1st January 2022 10:44:45 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 1st January 2022 10:47:49 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */

#include "mfGUI.hpp"
#include "Yuna.hpp"



namespace Utils
{
	void	initBtnHover(mf::Button *pBtn, Yuna::Core::ResourceManager *pResourceManager, sf::Sound *pHoverSound);
	void	playClickSound(sf::Sound *pHoverSound);
	
}