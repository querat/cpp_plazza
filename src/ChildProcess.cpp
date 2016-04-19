//
// Process.cpp for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Mon Apr 18 15:04:35 2016 querat_g
// Last update Tue Apr 19 09:21:23 2016 querat_g
//

#include "ChildProcess.hh"

ChildProcess::ChildProcess(pid_t pid, NamedPipe &input, NamedPipe &output)
  : _pid(pid)
  , _input(input)
  , _output(output)
{
  std::cerr << "ChildProcess " << std::to_string(_pid) << "created" << std::endl;
}

ChildProcess::~ChildProcess(){
  std::cerr << "ChildProcess " << std::to_string(_pid) << "deleted" << std::endl;
}
