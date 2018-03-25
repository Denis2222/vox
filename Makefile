UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	GCC_FLAG =
	DL_INC = -I./includes -I./glmc -I./libft
	DL_FLAG_DIR =
	DL_FLAG = -lGLU -lGL -lglfw -lGLEW -lGLU -lGL -ldl -lm -lpthread -lXxf86vm -lX11 -lnoise -lassimp
endif
ifeq ($(UNAME), Darwin)
	GCC_FLAG = -Wall -Werror -Wextra
	DL_INC = -I./includes -I $(HOME)/.brew/include
	DL_FLAG_DIR = -L./glmc -L./libft
	DL_FLAG = -L $(HOME)/.brew/lib -framework OpenGL -lglfw -lGLEW -lpthread
endif

GCC_FLAG = -Ofast -std=c++17
CC = g++ $(GCC_FLAG) $(DL_INC)

NAME = ft_vox

dir_guard=@mkdir -p $(@D)

SRC =  	main.cpp \
		glfw-init.cpp \
		FastNoise.cpp \
		noise.cpp \
		texture.cpp \
		Model.cpp \
		Mesh.cpp \
		Shader.cpp \
		Camera.cpp \
		Chunk.cpp \
		Map.cpp

SRCDIR = ./srcs/
OBJDIR = ./objs

SRCS=$(addprefix $(SRCDIR),$(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))

all: $(NAME)

$(addprefix $(OBJDIR)/, %.o): $(addprefix $(SRCDIR)/, %.cpp)
	$(dir_guard)
	@$(CC)  -o $@ -c $^

$(NAME): $(OBJS)
	@$(CC) -o $@ $^  $(DL_FLAG)
	@echo "[$@] Complete"

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
