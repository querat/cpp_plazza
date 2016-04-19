//
// Process.hh for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Mon Apr 18 15:01:51 2016 querat_g
// Last update Tue Apr 19 11:11:38 2016 querat_g
//

#ifndef CHILDPROCESS_HH_
# define CHILDPROCESS_HH_

# include <sys/types.h>
# include "PlazzaNameSpace.hh"
# include "NamedPipe.hh"

class ChildProcess
{
public:
  ChildProcess(pid_t pid, NamedPipe *pipe1, NamedPipe *pipe2);
  ~ChildProcess();

private:
  pid_t         _pid;
  NamedPipe *   _pipe1;
  NamedPipe *   _pipe2;

public:
  void          sendData(void const *data, size_t size);

};

#endif // !PROCESS_HH_
