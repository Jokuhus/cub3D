CC = cc

# c compiler option
FLAG = -Wall -Wextra -Werror $(ERROR_CHECK)
MLX_L = -framework OpenGL -framework Appkit -Imlx
MMD = -MMD -MP
ERROR_CHECK = -g #-fsanitize=address

#linker option
LDFLAGS = -Imlx -I$(LIB_DIR)

#target
NAME = cub3D

#bonus target
BONUS = cub3D

#source file directory
SRC_DIR = srcs

#object file directory
OBJ_DIR = objs

#dependency file directory
DEP_DIR = dep

#source files
SRCS = $(notdir $(wildcard $(SRC_DIR)/*.c))

#object files
OBJS = $(SRCS:.c=.o)

#put path to creating object files
OBJECTS = $(patsubst %.o,$(OBJ_DIR)/%.o,$(OBJS))

#bonus source file directory
BNS_SRC_DIR = srcs_bonus
#bonus source files
BNS_SRCS = $(notdir $(wildcard $(BNS_SRC_DIR)/*_bonus.c))
#bonus object files
BNS_OBJS = $(BNS_SRCS:.c=.o)
#put path to creating object files
BNS_OBJECTS = $(patsubst %_bonus.o,$(OBJ_DIR)/%_bonus.o,$(BNS_OBJS))

#dependancy files
DEPS = $(OBJECTS:.o=.d)

#libft
LIB_DIR = ./libft
LIBFT = $(LIB_DIR)/libft.a

#mlx
MLX_DIR = ./mlx
MLX = $(MLX_DIR)/libmlx.a

all : $(NAME)

$(NAME) : $(MLX) $(LIBFT) $(OBJECTS) Makefile mandatory
	@echo "creating $(NAME)"
	@rm -rf bonus
	@$(CC) $(FLAG) $(MLX_L) $(MLX) $(LIBFT) $(OBJECTS) -o $@ $(LDFLAGS)

mandatory :
	@touch mandatory

bonus : $(MLX) $(LIBFT) $(BNS_OBJECTS) Makefile
	@echo "creating $(BONUS)"
	@rm -rf mandatory
	@touch bonus
	@$(CC) $(FLAG) $(MLX_L) $(MLX) $(LIBFT) $(BNS_OBJECTS) -o $(BONUS) $(LDFLAGS)

$(LIBFT) :
	@echo "archiving $(LIBFT)"
	@make -C $(LIB_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile | $(OBJ_DIR)
	@$(CC) $(FLAG) $(MMD) -c $< -o $@ $(LDFLAGS)

$(OBJ_DIR)/%_bonus.o: $(BNS_SRC_DIR)/%_bonus.c Makefile | $(OBJ_DIR)
	@$(CC) $(FLAG) $(MMD) -c $< -o $@ $(LDFLAGS)

$(OBJ_DIR) :
	@echo "creating $(OBJ_DIR) directory"
	@mkdir -p $(OBJ_DIR)

.PHONY: clean fclean re

clean :
	@echo "removing $(OBJ_DIR) directory"
	@rm -rf $(OBJ_DIR) mandatory bonus
	@echo "removing $(LIBFT)"
	@make fclean -C $(LIB_DIR)

fclean : clean
	@echo "removing $(NAME)"
	@rm -rf $(NAME)

re : fclean all

-include $(DEPS)
