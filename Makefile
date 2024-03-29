SRC = \
      map/test_map_capacity.cpp \
      map/test_map.cpp \
      map/test_map_element_access.cpp \
      map/test_map_iterator.cpp \
      map/test_map_lookup.cpp \
      map/test_map_modifiers.cpp \
      map/test_map_non_member.cpp \
      map/test_map_observers.cpp \
      stack/test_stack.cpp \
      vector/test_vector.cpp \
      vector/test_vector_capacity.cpp \
      vector/test_vector_element_access.cpp \
      vector/test_vector_iterators.cpp \
      vector/test_vector_modifiers.cpp \
      vector/test_vector_non_member.cpp \
      main42.cpp

SRCSDIR = ./test

OBJDIR_FT = $(SRCSDIR)/objects_ft
OBJDIR_STD = $(SRCSDIR)/objects_std

SRCS = ${SRC:%.cpp=$(SRCSDIR)/%.cpp}

OBJS_FT = $(SRCS:.cpp=.o)
OBJS_STD = $(SRCS:.cpp=_std.o)

NAME = ft_containers

CXX = c++

CXXFLAGS_FT= -Wall -Wextra -Werror -std=c++98 -I./includes/ -I./test/include/ -fsanitize=address -DNAMESPACE=ft
CXXFLAGS_STD= -Wall -Wextra -Werror -std=c++98 -I./includes/ -I./test/include/ -DNAMESPACE=std

RM = rm -rf

.cpp.o :
	$(CXX) $(CXXFLAGS_FT) -c $< -o ${<:.cpp=.o}
	$(CXX) $(CXXFLAGS_STD) -c $< -o ${<:.cpp=_std.o}

$(NAME): $(OBJS_FT) $(OBJS_STD)
	$(CXX) $(CXXFLAGS_FT) -o $@ ${OBJS_FT}
	$(CXX) $(CXXFLAG_STD) -o $@_std ${OBJS_STD}

all: $(NAME)

clean:
	$(RM) $(OBJS_FT)
	$(RM) $(OBJS_STD)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME)_std

re: fclean all

.PHONY: all clean fclean re
