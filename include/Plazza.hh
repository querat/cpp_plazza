//
// Plazza.hh for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on Sun Apr 17 14:29:00 2016 querat_g
// Last update Tue Apr 19 09:36:57 2016 querat_g
//

#ifndef PLAZZA_HH
# define PLAZZA_HH

// std::*
# include <iostream>
# include <string>
# include <exception>
# include <stdexcept>

// stl
# include <vector>

// sysUnix
# include <sys/wait.h>

# include "PlazzaNameSpace.hh"
# include "ChildProcess.hh"

namespace Plazza
{
  class Main
  {
  public:
    Main(std::string nbThreads);
    ~Main();

  private:
    int                         _nbThreads;
    std::vector<ChildProcess>   _childs;

  public:
    bool                fork();
  };
}

#endif  // PLAZZA_HH
