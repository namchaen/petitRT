NAME = miniRT

CC := cc
FLAGS := -Wall -Werror -Wextra #-g -fsanitizer=address

LFT := libft/libft.a
#MLX := mlx/libmlx.a
#MLX := mlx/

INC := -Iinclude -Ilibft -Imlx
LIB := -Llibft -lft -Lmlx -lmlx -framework OpenGL -framework AppKit

#INC := -Iinclude -Ilibft -Imlx
#LIB := -Llibft -lft -Lmlx -lmlx -framework OpenGL -framework AppKit

MAIN_SRC := $(addprefix src/main/, main.c utils.c input.c render.c \
			  choose_object.c)
SCENE_SRC := $(addprefix src/scene/, camera.c \
			  object_utils.c object.c scene.c \
			  move_object.c rotate_object.c)
RAY_SRC := $(addprefix src/ray/, ray.c phong_lighting.c shadow.c\
			  hit_plane.c hit_record.c hit_sphere.c hit.c \
			  hit_cylinder.c )
VECTOR_SRC := $(addprefix src/vector/, length.c \
			  op_scalar.c op_vec.c product.c vector.c \
			  rotate.c)
PARSER_SRC := $(addprefix src/parser/, line_scanf.c get_next_line.c \
			  add_object.c add_object_shape.c \
			  parser.c parser_utils.c)
UTILS_SRC := $(addprefix src/utils/, utils.c)

SRC := $(MAIN_SRC) $(SCENE_SRC) $(RAY_SRC) $(VECTOR_SRC) $(PARSER_SRC) $(UTILS_SRC)
OBJ := $(patsubst src%, obj%, $(SRC:.c=.o))

obj/%.o : src/%.c
#	$(CC) $(INC) -o $@ -c $<
	$(CC) $(FLAGS) $(INC) -o $@ -c $<

all: $(LFT) obj $(NAME)
#all: $(LFT) $(MLX) obj $(NAME)

$(NAME) : $(OBJ)
#	$(CC) -o $@ $^ $(LIB)
	$(CC) $(FLAGS) -o $@ $^ $(LIB)

$(LFT):
	@$(MAKE) -s -C libft
$(MLX):
	$(MAKE) -C mlx

clean:
#	@$(MAKE) -s -C libft $@
#	@$(MAKE) -s -C mlx $@
	rm -rf obj

fclean: clean
#	@$(MAKE) -s -C libft $@
#	@$(MAKE) -s -C mlx $@
	@rm -rf $(NAME)

obj:
	@mkdir -p obj
	@mkdir -p obj/main
	@mkdir -p obj/scene
	@mkdir -p obj/ray
	@mkdir -p obj/vector
	@mkdir -p obj/parser
	@mkdir -p obj/utils

re: fclean all
