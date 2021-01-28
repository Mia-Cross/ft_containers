NAME = mutantstack

CXX = clang++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 #-g -fsanitize=address
SRCS = 	main.cpp 

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
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR) :
	@mkdir -p .obj

clean :
	@rm -rf $(OBJDIR)
	@rm -f *.o
	@rm -f *.out

fclean : clean
	@rm -f $(NAME)

re : fclean opti
