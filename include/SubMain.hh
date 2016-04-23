//
// SubMain.hh for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Tue Apr 19 09:50:04 2016 querat_g
// Last update Sat Apr 23 17:22:42 2016 querat_g
//

#ifndef SUBMAIN_HH
# define SUBMAIN_HH

// std::*
# include <mutex>
# include <string>
# include <chrono>

// SysUnix
# include <sys/types.h>
# include <unistd.h>
# include <poll.h>

// C
# include <ctime>

# include "PlazzaNameSpace.hh"
# include "NamedPipe.hh"
# include "ThreadPool.hh"
# include "SafeDeque.hpp"

typedef     std::chrono::system_clock::time_point       t_TimePoint;

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
    t_SafeActionDeque   _actionsToDo;
    t_SafeAnswerDeque   _answers;

    time_t              _clock;
    time_t              _timeSinceLastEvent;

    int                 _nbThreads;
    ThreadPool          _threads;

  private:              // Internal clock and exit status
    void                _incrementTimeSinceLastEvent();

  private:              // Boolean operations
    bool                _shouldExit() const;

  public:               // I/O operations
    bool                receiveAction(void);
    bool                sendSolvedAction(std::string const & solved);

  public:
    bool                mainLoop();
  };
}

#endif  // SUBMAIN_HH
