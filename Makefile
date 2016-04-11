##
## Makefile for makefile in /home/lina/rendu/B4/C++/cpp_plazza
## 
## Made by lina
## Login   <lina@epitech.net>
## 
## Started on  Mon Apr 11 10:17:10 2016 lina
## Last update Mon Apr 11 10:17:10 2016 lina
##

RM	= rm -f

CC	= clang++

NAME	= plazza

CXXFLAGS	= -W -Wall -Wextra -std=c++11 -stdlib=libstdc++ -I./include

SRCS	= ./src/main.cpp

OBJS	= $(SRCS:.cpp=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) -o $(NAME) $(CXXFLAGS) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(OBJS)

re: fclean all

.PHONY: all clean fclean re
