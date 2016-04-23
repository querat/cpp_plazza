//
// SubMain.hh for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Tue Apr 19 09:50:04 2016 querat_g
// Last update Sat Apr 23 14:12:07 2016 querat_g
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
# include "ThreadPool.hh"
# include "SafeDeque.hpp"

namespace Plazza
{
  class SubMain
  {
  public:
    SubMain(pid_t pid, NamedPipe *pipe1, NamedPipe *pipe2, int nbThreads);
    ~SubMain();

  private:
    pid_t               _pid;
    NamedPipe *         _pipe1;
    NamedPipe *         _pipe2;
    std::mutex          _mutex;
    t_SafeActionDeque   _actionsToDo;
    t_SafeAnswerDeque   _answers;
    // t_ActionDeque _actionsToDo;

    clock_t             _clock;
    double              _timeSinceLastEvent;

    ThreadPool          _threads;

  private:              // Internal clock and exit status
    void                _incrementTimeSinceLastEvent();
    void                _resetTimeSinceLastEvent();

  private:              // Boolean operations
    bool                _shouldExit() const;

  public:               // I/O operations
    bool                receiveAction(void);
    void                printActionsToDo(void) const;
    bool                sendSolvedAction(std::string const & solved);

  public:
    bool                mainLoop();
    bool                processAction();
  };
}

#endif  // SUBMAIN_HH
