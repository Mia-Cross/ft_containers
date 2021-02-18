NAME = ft_containers

CXX = clang++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g -fsanitize=address
SRCS = 	main.cpp \
		testList.cpp \
		#testMap.cpp \
		testQueue.cpp \
		testStack.cpp \
		testVector.cpp

INCLUDES =	-I containers/
OBJDIR =	.obj
OBJS =	$(addprefix $(OBJDIR)/, $(SRCS:.cpp=.o))
DPDCS =	$(OBJS:.o=.d)

-include $(DPDCS)

opti:
	@make -j all

all :
	@make $(NAME)

$(NAME) : $(OBJS)
	@printf "[$(NAME)] "
	$(CXX) $(CXXFLAGS) -o $(NAME) ${OBJS}
	@echo Compiled $(NAME) successfully !

$(OBJDIR)/%.o : %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR) :
	@mkdir -p .obj

clean :
	@rm -rf $(OBJDIR)
	@rm -f *.o
	@rm -f *.out

fclean : clean
	@rm -f $(NAME)

re : fclean opti