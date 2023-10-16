# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/06 14:08:48 by emcnab            #+#    #+#              #
#    Updated: 2023/10/10 09:51:15 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DOCKER   = docker run --rm -v .:/app trantorian/criterion:2.4.2.v
VALGRIND = valgrind --trace-children=yes --leak-check=full --show-leak-kinds=all
CORES    = $(($(nproc) + 1))

# **************************************************************************** #
#                               COMPILATIONS TASKS                             #
# **************************************************************************** #

all: debug

fclean: fclean_debug fclean_test fclean_final

# **************************************************************************** #
#                                   DEBUG TASK                                 #
# **************************************************************************** #

debug:
	@echo "$(BOLD)$(RED)[ Building in Debug Mode ]$(RESET)"
	@$(DOCKER) make -j$(CORES) --silent --file=./build/build_debug.mf

clean_debug:
	@echo "$(BOLD)$(RED)[ Removing all Debug objects ]$(RESET)"
	@make fclean --silent --file=./build/build_debug.mf

fclean_debug:
	@echo "$(BOLD)$(RED)[ Removing all Debug files ]$(RESET)"
	@make fclean --silent --file=./build/build_debug.mf

re_debug:
	@echo "$(BOLD)$(RED)[ Rebuilding Debug binary ]$(RESET)"
	@make fclean --silent --file=./build/build_debug.mf

# **************************************************************************** #
#                                    TEST TASK                                 #
# **************************************************************************** #

test: debug
	@echo "$(BOLD)$(YELLOW)[ Building in Test Mode ]$(RESET)"
	@$(DOCKER) make --silent --file=./build/build_test.mf

test_verbose:
	@echo "$(BOLD)$(YELLOW)[ Building in Test Mode ]$(RESET)"
	@$(DOCKER) make --silent --file=./build/build_test.mf

clean_test:
	@echo "$(BOLD)$(YELLOW)[ Removing all Test objects ]$(RESET)"
	@make clean --silent --file=./build/build_test.mf

fclean_test:
	@echo "$(BOLD)$(YELLOW)[ Removing all Test files ]$(RESET)"
	@make fclean --silent --file=./build/build_test.mf

re_test:
	@echo "$(BOLD)$(YELLOW)[ Rebuilding Test binary ]$(RESET)"
	@make fclean --silent --file=./build/build_test.mf
	@make test

# **************************************************************************** #
#                                   FINAL TASK                                 #
# **************************************************************************** #

final: test
	@echo "$(BOLD)$(BLUE)[ Building in Final Mode ]$(RESET)"
	@make -j$(CORES) --silent --file=./build/build_final.mf

clean_final:
	@echo "$(BOLD)$(BLUE)[ Removing all Final objects ]$(RESET)"
	@make clean --silent --file=./build/build_final.mf

fclean_final:
	@echo "$(BOLD)$(BLUE)[ Removing all Final files ]$(RESET)"
	@make fclean --silent --file=./build/build_final.mf

re_final:
	@echo "$(BOLD)$(BLUE)[ Rebuilding Final binary ]$(RESET)"
	@make fclean --silent --file=./build/build_final.mf
	@make final

-include ./build/colors.mf



.PHONY: all fclean                                       \
	    debug clean_debug fclean_debug re_debug          \
	    test test_verbose clean_test fclean_test re_test \
	    final clean_final fclean_final re_final
