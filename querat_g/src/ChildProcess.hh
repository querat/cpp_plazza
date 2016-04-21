//
// Process.hh for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Mon Apr 18 15:01:51 2016 querat_g
// Last update Wed Apr 20 17:31:32 2016 querat_g
//

#ifndef CHILDPROCESS_HH_
# define CHILDPROCESS_HH_

# include <signal.h>
# include <sys/types.h>

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
  std::stack<std::string>       _answerStack;

private:

public:         // I/O operations
  void          sendData(void const *data, size_t size);
  bool          sendAction(t_FileActionPair const & fileActionPair);
  void          sendSignal(int sig) const;
  void          popPrintAnswers();
  bool          receiveAnswer();

public:         //
  bool          isBusy() const;
  bool          reachedMaxCharge() const;

  pid_t         getPid() const;
};

#endif // !PROCESS_HH_
