# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    default_vars.mk                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/09 13:39:47 by mfischer          #+#    #+#              #
#    Updated: 2019/11/15 14:28:15 by mfischer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				:=	g++

#*#*#*#*# CHANGE PROGRAM NAME HERE #*#*#*#*#
NAME			:=	sandbox
#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*

CFLAGS			:=	-Wall -Werror -Wextra -std=c++17

CLIBS			+= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio

BLACK_LIST_SRCS :=	

SRCDIRS			:=	src

# Source auto-discovery. Test sources must never be swept into the game binary:
# a test file under src/ would be compiled into obj/ and linked into $(NAME),
# where its main() (or a test framework's main()) collides with src/main.cpp.
# Excluding any 'tests' directory here makes that safe by construction, so a
# future src/tests/ cannot break the game build. Keep unit tests in a top-level
# tests/ directory (outside $(SRCDIRS)) as well.
SRCS			+=	$(shell find $(SRCDIRS) -name '*.cpp' -not -path '*/tests/*')

INC_PATHS		:=	src

INC_PATHS		:=	$(shell find $(INC_PATHS) -type d)

INCLUDES		+=	$(foreach d, $(INC_PATHS), -I $d)

SRC_DIR			:=	$(patsubst src/%,obj/%,$(shell find src/* -type d))

OBJS			:=	$(patsubst src/%.cpp,obj/%.o,$(SRCS))

# Seam for a future unit-test binary: the game's objects without main.o, so a
# test target can link the real game code alongside a test framework's own
# main() (e.g. libgtest_main) without a duplicate-symbol collision with
# src/main.cpp. Not used by the game build itself.
GAME_OBJS_NO_MAIN	:=	$(filter-out obj/main.o,$(OBJS))

DEPS			:=	$(patsubst %.o,%.d,$(OBJS))

UNAME			:=	$(shell uname -s)

INC_DIRS		+=	Yuna/includes Yuna/mfGUI/include

INC_DIRS		:= $(foreach d, $(INC_DIRS), -I $d)

LIBDEP			:=	Yuna/Yuna.a Yuna/mfGUI/lib/libMFGUId.a


# This is a minimal set of ANSI/VT100 color codes
_END			=	\033[0;0m
_BOLD			=	\033[0;1m
_UNDER			=	\033[0;4m
_REV			=	\033[0;7m

# Colors
_GREY			=	\033[0;30m
_RED			=	\033[0;31m
_GREEN			=	\033[0;32m
_YELLOW			=	\033[0;33m
_BLUE			=	\033[0;34m
_PURPLE			=	\033[0;35m
_CYAN			=	\033[0;36m
_WHITE			=	\033[0;37m

# Inverted, i.e. colored backgrounds
_IGREY			=	\033[0;40m
_IRED			=	\033[0;41m
_IGREEN			=	\033[0;42m
_IYELLOW		=	\033[0;43m
_IBLUE			=	\033[0;44m
_IPURPLE		=	\033[0;45m
_ICYAN			=	\033[0;46m
_IWHITE			=	\033[0;47m