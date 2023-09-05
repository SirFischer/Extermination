/*
 * File: AddHoverEffect.cpp
 * Project: Extermination
 * File Created: Saturday, 1st January 2022 10:45:17 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Thursday, 6th January 2022 6:40:08 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#include "Utils/Utils.hpp"
#include <SFML/Audio.hpp>

namespace Utils {

void initBtnHover(mf::Button *pBtn, Yuna::Core::ResourceManager *pResourceManager, sf::Sound *pHoverSound)
{
	pBtn->AddEventListener(mf::eEvent::ENTERED, [pBtn, pResourceManager, pHoverSound](){
		pHoverSound->setPlayingOffset(sf::seconds(0.10f));
		pHoverSound->play();
	
		pBtn->SetBackground(*(pResourceManager->LoadTexture("assets/textures/button-hover.png")));
		pBtn->SetTextPosition(10 + (4 * (pBtn->GetSize().x / 128)), 9);
	});
	pBtn->AddEventListener(mf::eEvent::EXITED, [pBtn, pResourceManager](){
		pBtn->SetBackground(*(pResourceManager->LoadTexture("assets/textures/button.png")));
		pBtn->SetTextPosition(10, 5);
	});
}

}
