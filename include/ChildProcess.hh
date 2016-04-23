
//
// Process.hh for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Mon Apr 18 15:01:51 2016 querat_g
// Last update Fri Apr 22 13:53:02 2016 querat_g
//

#ifndef CHILDPROCESS_HH_
# define CHILDPROCESS_HH_

// std::*
# include <deque>

// SysUnix
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

// Plazza
# include "PlazzaNameSpace.hh"
# include "NamedPipe.hh"

class ChildProcess
{
public:
  ChildProcess(pid_t pid, NamedPipe *pipe1, NamedPipe *pipe2, int nbThreads);
  ~ChildProcess();

private:
  pid_t                         _pid;
  NamedPipe *                   _pipe1; // from main to child ...
  NamedPipe *                   _pipe2; // ... And the other way around
  uint32_t                      _nbCurrentActions;
  uint32_t                      _maxActions;
  std::deque<std::string>       _answerStack;

private:

public:         // I/O operations
  void          sendData(void const *data, size_t size);
  bool          sendAction(t_FileActionPair const & fileActionPair);
  int           sendSignal(int sig) const;
  void          popPrintAnswers();
  bool          receiveAnswer(std::deque<std::string> &answerStack);

public:         // Boolean conditions
  bool          isBusy() const;
  bool          reachedMaxCharge() const;
  bool          hasAnswerReady() const;
  bool          isAlive() const;

public:         // GetSet()
  pid_t         getPid() const;
};

#endif // !PROCESS_HH_
