UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	GCC_FLAG = -std=c++14 -Ofast
	DL_INC = -I./includes -I./glmc -I./libft
	DL_FLAG_DIR =
	DL_FLAG = -lGLU -lglfw -lGLEW -lGL -ldl -lm -lpthread -lXxf86vm -lX11 -lassimp -lnoise -lXrandr -lXi
endif
ifeq ($(UNAME), Darwin)
	GCC_FLAG = -std=c++14 -Ofast
	DL_INC = -I./includes -I $(HOME)/.brew/include
	DL_FLAG_DIR = -L./glmc -L./libft
	DL_FLAG = -L $(HOME)/.brew/lib -framework OpenGL -lglfw -lGLEW -lpthread -lassimp  -lnoise
endif

CC = g++ $(GCC_FLAG) $(DL_INC)

NAME = ft_vox

dir_guard=@mkdir -p $(@D)

SRC =  	main.cpp \
		utils.cpp \
		Scene.cpp \
		Voxel.cpp \
		Camera.cpp \
		GameObject/Skybox.cpp \
		GameObject/Terrain.cpp \
		GameObject/Model.cpp \
		GameObject/Mesh.cpp \
		GameObject/Shader.cpp \
		GameObject/Map/Chunk.cpp \
		GameObject/GameObject.cpp \
		GameObject/Map/Map.cpp

SRCDIR = ./srcs/
OBJDIR = ./objs

SRCS=$(addprefix $(SRCDIR),$(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))

all: check $(NAME)

check:
	@echo "apt-get install libgl-dev libglew-dev libglfw3 libglfw3-dev libnoise-dev libglm-dev libgl1-mesa-dev"
	@echo "If	-lGL error : check : /usr/lib/libGL.so"
	@echo "IFNOT=>  ln -s /usr/lib/libGL.so.1 /usr/lib/libGL.so"

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
