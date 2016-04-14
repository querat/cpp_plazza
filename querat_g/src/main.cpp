//
// main.cpp for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Wed Apr 13 22:43:06 2016 querat_g
// Last update Thu Apr 14 10:59:31 2016 querat_g
//

#include <sys/wait.h>

#include <iostream>
#include "NamedPipe.hh"

int     elFork(char **av)
{
  NamedPipe	pipe("myFifo");
  int		child_pid = 0;

  child_pid = fork();
  if (child_pid == -1)
    {
      std::cerr << "fork has ded" << std::endl;
      return (1);
    }
  if (child_pid) // parent
    {
      std::string a = pipe.readFrom();
      std::cout << "reading " << a << std::endl;
    }
  else
    {
      pipe.writeTo(av[1]);
      wait(0);
    }

  return (true);
}

int     main(int ac, char **av)
{
  if (ac < 2)
    return (1);

  elFork(av);
  return (0);
}
