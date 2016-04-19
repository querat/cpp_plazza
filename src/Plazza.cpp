//
// Plazza.cpp for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Sun Apr 17 16:11:56 2016 querat_g
// Last update Tue Apr 19 09:38:15 2016 querat_g
//

#include "Plazza.hh"
#include "PlazzaNameSpace.hh"

# define ERR_NOTANUMBER "plazza: Argument should be a number"
# define ERR_INVALIDNUM "plazza: Argument should be an unsigned number"

Plazza::Main::Main(std::string nbThreads)
  : _nbThreads(1)
{
  std::regex    isNum("^\\-?[0-9]+$");

  if (!std::regex_match(nbThreads, isNum))
    throw (std::invalid_argument(ERR_NOTANUMBER));

  this->_nbThreads = std::atoi(nbThreads.c_str());
  if (this->_nbThreads <= 0)
    throw (std::invalid_argument(ERR_INVALIDNUM));
}

Plazza::Main::~Main(){}

bool
Plazza::Main::fork()
{
  pid_t         pid = -1;
  NamedPipe     pipe1(Plazza::makeFifoNameFromPid(pid, true));
  NamedPipe     pipe2(Plazza::makeFifoNameFromPid(pid, true));

  pid = fork();
  if (pid == -1)
    {
      std::cerr << "fork failed ! " << std::endl;
      return (false);
    }

  if (pid) // parent
    {


      wait(0);
    }
  else // child
    {



      exit(1);
    }

  return (true);
}
