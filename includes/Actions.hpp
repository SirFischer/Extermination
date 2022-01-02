/*
 * File: Actions.hpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 11:59:25 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 2nd January 2022 8:06:12 pm
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
	CROUCH
};

std::map<uint32_t, std::string>	*GetActionNames();