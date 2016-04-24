//
// SubMain.hh for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Tue Apr 19 09:50:04 2016 querat_g
// Last update Sun Apr 24 14:45:10 2016 querat_g
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
  /// Used by the sub Processes
  /// receive tasks from the main process and answers it through named pipes
  /// Holds a thread pool to dispatch tasks and solve them faster
  class SubMain
  {
  public:
    /// Constructor
    /// pid : pid of this process
    /// pipe1 : pointer to NamedPipe object going from main to subProcess
    /// pipe2 : pointer to NamedPipe object going from subProcess to main
    /// nbThreads : number of desired threads
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
    /// increments the internal clock that timeouts the process after 5 inactive seconds
    void                _incrementTimeSinceLastEvent();

  private:              // Boolean operations
    /// checks the exit state of the process
    bool                _shouldExit() const;

  public:               // I/O operations
    /// Receive an action from the main process through _pipe1
    bool                receiveAction(void);

    /// Sends a scrapped answer from the file to the main process through _pipe2
    bool                sendSolvedAction(std::string const & solved);

  public:
    /// main loop of the sub Process
    /// receive tasks from _pipe1 from the main process, dispatch them to threads
    /// then answers to the main process via _pipe2
    bool                mainLoop();
  };
}

#endif  // SUBMAIN_HH
