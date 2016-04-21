//
// SubMain.hh for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Tue Apr 19 09:50:04 2016 querat_g
// Last update Wed Apr 20 16:58:24 2016 querat_g
//

#ifndef SUBMAIN_HH
# define SUBMAIN_HH

// std::*
# include <mutex>
# include <string>

// SysUnix
# include <sys/types.h>
# include <unistd.h>
# include <poll.h>

# include "PlazzaNameSpace.hh"
# include "NamedPipe.hh"

namespace Plazza
{
  class SubMain
  {
  public:
    SubMain(pid_t pid, NamedPipe *pipe1, NamedPipe *pipe2);
    ~SubMain();

  private:
    pid_t               _pid;
    bool                _shouldExit;
    NamedPipe *         _pipe1;
    NamedPipe *         _pipe2;
    t_ActionDeque       _actionsToDo;
    std::mutex          _actionMutex;

  public:               // I/O operations
    bool                receiveAction(void);
    void                printActionsToDo(void) const;
    bool                sendSolvedAction(std::string const & solved);

  public:
    bool                mainLoop();
  };
}

#endif  // SUBMAIN_HH
