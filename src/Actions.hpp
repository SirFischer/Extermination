/*
 * File: Actions.hpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 11:59:25 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 12th June 2022 7:26:33 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once
#include <string>
#include <cstdint>
#include <map>

enum class eAction {
	CONSOLE_CONFIRM,
	CONSOLE_TOGGLE,
	CONSOLE_NEXT_IN_HISTORY,
	CONSOLE_PREVIOUS_IN_HISTORY,
	MOVE_RIGHT,
	MOVE_LEFT,
	JUMP,
	CROUCH,
	USE_ITEM_1,
	USE_ITEM_2,
	NEXT_ITEM,
	PREVIOUS_ITEM
};

std::map<uint32_t, std::string>	*GetActionNames();