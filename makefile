# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 13:48:32 by zlafou            #+#    #+#              #
#    Updated: 2023/01/23 14:16:36 by zlafou           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

PARSER			= arg_cleaner_utils.c arg_cleaner.c arg_cleanrtwo_utils.c argument_cleaner.c build_nodes.c her_doc_utils.c her_doc.c parse_cmd.c parser_utils.c parser.c redirection_parser.c redirection_utils.c token.c utils.c

BUILTINS 		= env.c pwd.c unset.c exit.c cd.c export.c echo.c

UTILS			= env_utils.c mem.c env_ext.c strings.c sigs.c exec_cmd.c

SRCS			= shell.c shell_utils.c $(UTILS) $(BUILTINS) $(PARSER)

OBJS			= $(SRCS:.c=.o)

CFLAGS			= -Wall -Wextra -Werror -g -fsanitize=address

CC				= cc

READLINE_PATH 	= -lreadline -L ~/goinfre/.brew/opt/readline/lib -I ~/goinfre/.brew/opt/readline/include

VPATH 			= ./executer/builtins/:./executer/utils/:./parser

HEADER			= "\033[0;35m   █▀▄▀█ ░▀░ █▀▀▄ ░▀░ █▀▀ █░░█ █▀▀ █░░ █░░  \n   █░▀░█ ▀█▀ █░░█ ▀█▀ ▀▀█ █▀▀█ █▀▀ █░░ █░░   \n   ▀░░░▀ ▀▀▀ ▀░░▀ ▀▀▀ ▀▀▀ ▀░░▀ ▀▀▀ ▀▀▀ ▀▀▀\033[0;0m"

FOOTER			= "\033[0;35m➔\033[0;0m type \033[0;34m./$(NAME)\033[0;0m to run the shell."

vpath $(SRCS) $(VPATH)

all: $(NAME) | footer

header :
	@echo
	@echo $(HEADER)
	@echo

footer :
	@echo $(FOOTER)

.c.o: 
	@sleep 0.003
	@printf "\33[2K\r\033[1mmaking object \033[0;34m➔\033[0;0m\033[0;35m $@ \033[0;0m"
	-@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): | header $(OBJS)
	@echo
	@echo
	@echo "\033[0;35m\033[1m────── making libft ──────\033[0;0m"
	@printf "\033[2m"
	@$(MAKE) -C libft/
	@$(MAKE) bonus -C libft/
	@echo "\033[0;0m"
	@echo "\033[0;35m\033[1m────── making minishell ──────\033[0;0m"
	@printf "\033[2m"
	$(CC) ${OBJS} $(CFLAGS) ./libft/libft.a -o ${NAME} $(READLINE_PATH)
	@echo "\033[0;0"

clean: | header
	@echo "\033[0;35m\033[1m────── clean libft ──────\033[0;0m"
	@printf "\033[2m"
	@$(MAKE) clean -C libft/
	@echo "\033[0;0m"
	@echo "\033[0;35m\033[1m────── clean minishell ──────\033[0;0m"
	@printf "\033[2m"
	rm -rf $(OBJS)
	@echo "\033[0;0m"

fclean:	clean | header
	@echo "\033[0;35m\033[1m────── fclean libft ──────\033[0;0m"
	@printf "\033[2m"
	@$(MAKE) fclean -C libft/
	@echo "\033[0;0m"
	@echo "\033[0;35m\033[1m────── fclean minishell ──────\033[0;0m"
	@printf "\033[2m"
	rm -rf $(NAME)
	@echo "\033[0;0m"
				
re:	fclean all

.PHONY:	all clean fclean re minishell

