//
// Process.hh for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Mon Apr 18 15:01:51 2016 querat_g
// Last update Tue Apr 19 09:21:37 2016 querat_g
//

#ifndef CHILDPROCESS_HH_
# define CHILDPROCESS_HH_

# include <sys/types.h>
# include "PlazzaNameSpace.hh"
# include "NamedPipe.hh"

class ChildProcess
{
public:
  ChildProcess(pid_t pid, NamedPipe &input, NamedPipe &output);
  ~ChildProcess();

private:
  pid_t         _pid;
  NamedPipe &   _input;
  NamedPipe &   _output;

public:


};

#endif // !PROCESS_HH_
