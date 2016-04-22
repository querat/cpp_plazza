//
// Plazza.hh for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on Sun Apr 17 14:29:00 2016 querat_g
// Last update Fri Apr 22 16:31:21 2016 querat_g
//

#ifndef PLAZZA_HH
# define PLAZZA_HH

# define ERR_NOTANUMBER "plazza: Argument should be a number"
# define ERR_INVALIDNUM "plazza: Argument should be an unsigned number"

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
# include <signal.h>

# include "PlazzaNameSpace.hh"
# include "ChildProcess.hh"
# include "Parser.hh"

typedef         std::map<pid_t, ChildProcess>   t_ChildrenMap;
typedef         t_ChildrenMap::iterator         t_ChildrenMapIt;

namespace Plazza
{
  class Main
  {
  public:
    Main(std::string nbThreads);
    ~Main();

  private:
    int                                 _nbThreads;
    t_ChildrenMap                       _childs;
    t_ActionDeque                       _actionQueue;
    t_AnswerDeque                       _answers;

    std::string                         _stdinString;

bool                                _stdinIsClosed;
bool                                _forcedExit;

  private:              // Boolean Operations
    bool                _shouldExit() const;

  private:              // I/O operations
    void                _readStdin();
    void                _dumpAnswers();

  private:              // misc
    t_ChildrenMapIt     _firstAvailableProcess();
    bool                _forkPlazza();
    void                _pollAndGetAnswers();
    void                _cleanDeadChildren();

  public:               // Boolean operations
    bool                isBusy() const;

  public:               // I/O Operations
    void                printActionsQueue() const;

public:
void                    setForcedExitState();

  public:               // misc
    void                killProcesses();
    int                 mainLoop();
  };
}

#endif  // PLAZZA_HH
