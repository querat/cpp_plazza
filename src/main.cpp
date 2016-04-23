//
// main.cpp for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Wed Apr 13 22:43:06 2016 querat_g
// Last update Sat Apr 23 19:17:43 2016 querat_g
//

#include <stdexcept>

#include <sys/wait.h>

#include <iostream>
#include "Plazza.hh"

int     main(int ac, char **av)
{
  Plazza::Main  *plazza = nullptr;

  if (ac != 2)
    {
      std::cerr << PLAZZA_USAGE << std::endl;
      return (1);
    }

  try {
    plazza = new Plazza::Main(av[1]);
  }
  catch (std::invalid_argument const & exception) {
    std::cerr << exception.what() << std::endl;
    return (1);
  }

  plazza->mainLoop();
  plazza->killProcesses();
  return (0);
}
