//
// Plazza.hh for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on Sun Apr 17 14:29:00 2016 querat_g
// Last update Wed Apr 20 17:51:31 2016 querat_g
//

#ifndef PLAZZA_HH
# define PLAZZA_HH

// std::*
# include <iostream>
# include <string>
# include <exception>
# include <stdexcept>

// stl
# include <map>

// sysUnix
# include <sys/wait.h>
# include <poll.h>

# include "PlazzaNameSpace.hh"
# include "ChildProcess.hh"
# include "Parser.hh"

namespace Plazza
{
  class Main
  {
  public:
    Main(std::string nbThreads);
    ~Main();

  private:
    int                                 _nbThreads;
    std::map<pid_t, ChildProcess>       _childs;
    t_ActionDeque                       _actionQueue;
    Parser                              _cmd;

  public:
    bool                forkPlazza();
    void                killProcesses();
  };
}

#endif  // PLAZZA_HH
