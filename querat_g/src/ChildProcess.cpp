//
// Process.cpp for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Mon Apr 18 15:04:35 2016 querat_g
// Last update Tue Apr 19 14:32:32 2016 querat_g
//

#include "ChildProcess.hh"

ChildProcess::ChildProcess(pid_t pid, NamedPipe *pipe1, NamedPipe *pipe2)
  : _pid(pid)
  , _pipe1(pipe1)
  , _pipe2(pipe2)
{
  // std::cerr << "ChildProcess " << std::to_string(_pid) << "created" << std::endl;
}

ChildProcess::~ChildProcess(){
  // std::cerr << "ChildProcess " << std::to_string(_pid) << "deleted" << std::endl;
}

void
ChildProcess::sendData(void const *data, size_t size)
{
  // std::cerr << "sending data from " << getpid() << std::endl;
  _pipe1->writeTo(data, size);

}
