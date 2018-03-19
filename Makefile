UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	DL_INC = -Iexternal/glfw-3.1.2/include -I./includes
	DL_FLAG = -lGLU -lGL -Lexternal/glfw-3.1.2/src -lglfw3 -lGLEW -lGLU -lGL -lXrandr -ldl -lm -lpthread -lXinerama -lXi -lXxf86vm -lXcursor -lX11
endif
ifeq ($(UNAME), Darwin)
	DL_INC = -I./includes -I $(HOME)/.brew/include
	DL_FLAG = -L./libft -L $(HOME)/.brew/lib -framework OpenGL -lglfw -lGLEW -lpthread
endif

GCC_FLAG = -g
CC = g++ $(GCC_FLAG) $(DL_INC)

NAME = ft_vox

dir_guard=@mkdir -p $(@D)

SRC =  	main.cpp \
		Shader.cpp \
		Camera.cpp

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
