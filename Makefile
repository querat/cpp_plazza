##
## Makefile for makefile in /home/lina/rendu/B4/C++/cpp_plazza
## 
## Made by lina
## Login   <lina@epitech.net>
## 
## Started on  Mon Apr 11 10:17:10 2016 lina
## Last update Sat Apr 23 12:14:23 2016 querat_g
##

CYAN		= 	"\e[1;36m"
PURPLE		= 	"\e[1;35m"
BLUE		= 	"\e[1;34m"
YELLOW		= 	"\e[1;33m"
GREEN		= 	"\e[1;32m"
RED		= 	"\e[1;31m"
WHITE		= 	"\e[0m"

RM		= 	rm -f

CXX		= 	clang++

NAME		= 	plazza

CXXFLAGS	=	-W -Wall -Wextra 
CXXFLAGS	+=	-std=c++11 -stdlib=libc++
CXXFLAGS	+=	-I./include
CXXFLAGS	+=	-I./src
CXXFLAGS	+=	-pthread

SRCS		= 	src/main.cpp \
			src/NamedPipe.cpp \
			src/Parser.cpp \
			src/PlazzaNameSpace.cpp \
			src/Plazza.cpp \
			src/ChildProcess.cpp \
			src/SubMain.cpp \
			src/SafeDeque.cpp \
			src/ThreadPool.cpp \
			src/DataCollector.cpp \

OBJS		= 	$(SRCS:.cpp=.o)

all:			$(NAME)

$(NAME):		$(OBJS)
			@`which echo` -e $(YELLOW)"[LINKING] "$@$(WHITE)
			@$(CXX) -o $(NAME) $(CXXFLAGS) $(SRCS)

.cpp.o:
			@`which echo` -e $(CYAN)"[COMPILING] "$@$(WHITE)
			@$(CXX) -c -o $@ $(CXXFLAGS) $< 2>&1 | head -n20

clean:
			@`which echo` -e $(RED)"[RM] "$(OBJS)$(WHITE)
			@$(RM) $(OBJS)
			@$(RM) ./fifo_*

fclean:			clean
			@`which echo` -e $(RED)"[RM] "$(NAME)$(WHITE)
			@$(RM) $(NAME)

re:			fclean all

debug:			CXXFLAGS += -D_DEBUG_=1 -g
debug:			$(NAME)

debugre:		CXXFLAGS += -D_DEBUG_=1 -g
debugre:		re

.PHONY:			all clean fclean re .cpp.o
