//
// Created by lina on 11/04/16.
//

#include <iostream>
#include "NamedPipe.hh"

int     main(int ac, char **av)
{
  NamedPipe	pipe("myFifo");
  int		child_pid = 0;


  if (ac < 2)
    return (1);

  child_pid = fork();
  if (child_pid == -1)
    {
      std::cerr << "ded" << std::endl;
    }

  if (child_pid) // parent
    {

      pipe.writeTo(av[1]);
    }
  else
    {
      std::string a = pipe.readFrom();
      std::cout << a << std::endl;
    }
  return (0);
}
