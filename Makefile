# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/09 13:26:22 by mfischer          #+#    #+#              #
#    Updated: 2019/11/10 01:41:32 by mfischer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include		Makefiles/default_vars.mk

ifdef RELEASE
CFLAGS += -O3
else
CFLAGS += -g
endif

NAME := Extermination

.PHONY:	install_dep obj clean fclean all GEN_SOURCES test check

all: install_dep Yuna.a $(OBJS) $(NAME)

$(OBJS):	| obj

Yuna.a:
	make -C Yuna/.

obj:
	@echo -e "$(_BLUE)Creating object directories...$(_END)"
	@mkdir -p $@ $(SRC_DIR)

-include $(DEPS)

obj/%.o: src/%.cpp
	@echo -e "$(_YELLOW)Compiling $(notdir $<)...$(_END)"
	@$(CC) $(CFLAGS) $(INC_DIRS) $(INCLUDES) -MMD -c $< -o $@

$(NAME): $(OBJS)
	@echo -e "$(_BLUE)Linking binary...$(_END)"
	@$(CC) $(CFLAGS) $(INCLUDES) $^ $(LIBDEP) -o $@ $(CLIBS)
	@echo -e "$(_GREEN)Done!$(_END)"

test:	all
	./$(NAME)

clean:
	@echo -e "$(_YELLOW)Cleaning OBJs...$(_END)"
	rm -rf obj

fclean: clean
	@echo -e "$(_YELLOW)Deleting executable...$(_END)"
	rm -rf $(NAME)

re: fclean all

GEN_SOURCES:
	@echo "${_BLUE}Generating source list...${_END}"
	@-rm .srcs
	@find . -type f | grep "\.cpp$$" $(foreach V, $(BLACK_LIST_SRCS), | grep -v "$(V)") | cut -f2- -d/ | grep -v " " | sed "s/$$/ \\\\/" | sed "1s/^       //" | sed "$$ s/..$$//" >> .srcs
	@echo "${_GREEN}Done!${_END}"

check:
	cppcheck --enable=all $(INCLUDES) $(SRCS)