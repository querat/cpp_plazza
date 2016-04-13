//
// Created by lina on 11/04/16.
//

#include <iostream>
#include "NamedPipe.hh"

int     main(int ac, char **av)
{
  NamedPipe	pipe("myFifo");
  int		child_pid = 0;


  child_pid = fork();
  if (child_pid == -1)
    {
      std::cerr << "ded" << std::endl;
    }

  if (child_pid) // parent
    {

      pipe.write("Allah ahkbar !");
    }
  else
    {
      std::string a = pipe.read();
      std::cout << a << std::endl;
    }
  return (0);
}
