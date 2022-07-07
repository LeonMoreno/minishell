#Variables
NAME	= minishell
SRC_DIR	= src/
OBJ_DIR	= obj/
CFLAGS	=  -g -Werror -Wall -Wextra -I include/
CC		= gcc
RM		= rm -f

#Libft
LIBFT_A		= libft.a
LIBFT_DIR	= libft/
LIBFT		= $(addprefix $(LIBFT_DIR), $(LIBFT_A))

#ReadLIne
RD_A		= libreadline.a
RDH_A		= libhistory.a
RD_DIR		= lib/
RD			= $(addprefix $(RD_DIR), $(RD_A))
RDH			= $(addprefix $(RD_DIR), $(RDH_A))

#Sources Files
SRC_FILES =	minishell ft_expansion ft_parsing_meta ft_reading\
			ft_quoting start_builtins utils_builtins start_exec\
			ft_utils ft_init_cmd start_childs utils_childs ft_sigaction \
			ft_utils_token start_redir next_builtins ft_heredoc start_env \
			ft_utils_here ft_expansion_here utils_2buil wildcards \
			wild_utils wild_utils2 wild_utils3 utils_3buil \
#SRC
SRC		=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ		=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
OBJF	=	.cache_exists

####

all	: $(NAME)

$(NAME):	$(OBJ)
			make -C $(LIBFT_DIR)
			$(CC) $(OBJ) $(LIBFT) $(RD) $(RDH) -lcurses -lreadline -o $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJF)
				$(CC) $(CFLAGS) -c $< -o $@


$(OBJF)	:
			@mkdir -p $(OBJ_DIR)

clean	:
			$(RM) -r $(OBJ_DIR)
			make -C $(LIBFT_DIR) clean
			$(RM) $(OBJF)

fclean	:	clean
			$(RM) $(NAME)
			make -C $(LIBFT_DIR) fclean
val:
		valgrind   --leak-check=full --track-origins=yes --show-leak-kinds=all --track-fds=yes --trace-children=yes ./$(NAME)

re		: fclean all

