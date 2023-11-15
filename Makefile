# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/06 14:08:48 by emcnab            #+#    #+#              #
#    Updated: 2023/11/15 17:01:37 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DOCKER   = docker run --rm -v .:/app trantorian/criterion:2.4.2.v
VALGRIND = valgrind --trace-children=yes --leak-check=full --show-leak-kinds=all
CORES    = $(($(nproc) + 1))

# **************************************************************************** #
#                               COMPILATIONS TASKS                             #
# **************************************************************************** #

all: final

clean:

fclean: fclean_debug fclean_test fclean_final

re: fclean_dynamic fclean_final
	@echo "$(BOLD)$(BLUE)[ Rebuilding Final binary ]$(RESET)"
	make --silent final

# **************************************************************************** #
#                                   SUBMODULES                                 #
# **************************************************************************** #

dynamic:
	@echo ">> dynamic"
	@make --silent --directory=./vendor/dynamic final
	@echo "<< dynamic"

fclean_dynamic:
	@echo ">> dynamic"
	@make --silent --directory=./vendor/dynamic fclean
	@echo << dynamic

# **************************************************************************** #
#                                   FINAL TASK                                 #
# **************************************************************************** #

final: dynamic
	@echo "$(BOLD)$(BLUE)[ Building in Final Mode ]$(RESET)"
	@make -j$(CORES) --silent --file=./build/build_final.mf

clean_final:
	@echo "$(BOLD)$(BLUE)[ Removing all Final objects ]$(RESET)"
	@make clean --silent --file=./build/build_final.mf

fclean_final:
	@echo "$(BOLD)$(BLUE)[ Removing all Final files ]$(RESET)"
	@make fclean --silent --file=./build/build_final.mf

-include ./build/colors.mf



.PHONY: all fclean re                                    \
	    debug clean_debug fclean_debug re_debug          \
	    test test_verbose clean_test fclean_test re_test \
	    final clean_final fclean_final re_final
