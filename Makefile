UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	DL_INC = -Iexternal/glfw-3.1.2/include -I./includes -I./glmc -I./libft
	DL_FLAG = -L./glmc -L./libft -lglmc -lGLU -lGL -Lexternal/glfw-3.1.2/src -lglfw3 -lGLEW -lGLU -lGL -lXrandr -ldl -lm -lpthread -lXinerama -lXi -lXxf86vm -lXcursor -lX11
endif
ifeq ($(UNAME), Darwin)
	DL_INC = -I./includes -I $(HOME)/.brew/include
	DL_FLAG = -L./libft -L $(HOME)/.brew/lib -framework OpenGL -lglfw -lGLEW -lpthread
endif

GCC_FLAG = -x c
CC = g++ $(GCC_FLAG) $(DL_INC)

NAME = scop

dir_guard=@mkdir -p $(@D)

SRC =  main.c \
		shader.c \
		Shader.cpp

SRCDIR = ./srcs/
OBJDIR = ./objs

SRCS=$(addprefix $(SRCDIR),$(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

all: test
	@#if [ -a ./assets/AK ]; then echo "Assets OK"; else echo "Download Assets : " ; curl -O http://denis-moureu.fr/42/assets-scop.zip; echo "Unzip to ./assets/" ;unzip assets-scop.zip -d ./assets ; rm -rf ./assets-scop.zip ; fi;
$(addprefix $(OBJDIR)/, %.o): $(addprefix $(SRCDIR)/, %.c)
	$(dir_guard)
	@$(CC)  -o $@ -c $^

$(NAME): $(OBJS)
	@$(CC) -o $@ $^  $(DL_FLAG)
	@echo "[$@] Complete"

$(LIBFT):
	@make -j99 -C ./libft

test:
	g++ -x c++ $(SRCS) -I ./includes -I ~/.brew/include -lglfw -L ~/.brew/lib -lGLEW -framework OpenGL -o vox

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
