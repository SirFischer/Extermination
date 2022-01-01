/*
 * File: AddHoverEffect.cpp
 * Project: Extermination
 * File Created: Saturday, 1st January 2022 10:45:17 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 1st January 2022 10:50:31 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#include "Utils/Utils.hpp"

namespace Utils {

void initBtnHover(mf::Button *pBtn, Yuna::Core::ResourceManager *pResourceManager)
{
	pBtn->AddEventListener(mf::eEvent::ENTERED, [pBtn, pResourceManager](){
		pBtn->SetBackground(*(pResourceManager->LoadTexture("assets/textures/Button_01_hover.png")));
	});
	pBtn->AddEventListener(mf::eEvent::EXITED, [pBtn, pResourceManager](){
		pBtn->SetBackground(*(pResourceManager->LoadTexture("assets/textures/Button_01.png")));
	});
}

}
