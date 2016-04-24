//
// Plazza.hh for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on Sun Apr 17 14:29:00 2016 querat_g
// Last update Sun Apr 24 14:19:18 2016 querat_g
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
    /// isBusy()
    /// retourne true si l'objet est en train de traiter des tâches,
    /// et false sinon
    bool                isBusy() const;

  public:
    /// setForcedExitState()
    /// set l'attribut _forcedExit à true, ce qui force la sortie
    /// de mainLoop()
    void                setForcedExitState();

  public:               // misc
    /// killProcesses()
    /// envoie un signal qui termine les processus fils
    /// et vide l'attribut _childrens
    void                killProcesses();

    /// mainLoop()
    /// boucle principale du plazza
    /// lit STDIN_FILENO, parse les commandes et les répartit
    /// entre les processus childs (ou créée ces derniers si ils
    /// n'existent pas).
    int                 mainLoop();
  };
}

#endif  // PLAZZA_HH
