//
// Plazza.cpp for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Sun Apr 17 16:11:56 2016 querat_g
// Last update Wed Apr 20 10:41:33 2016 querat_g
//

#include "PlazzaNameSpace.hh"
#include "Plazza.hh"
#include "SubMain.hh"

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
Plazza::Main::forkPlazza()
{
  pid_t         pid = -1;
  pid = fork();
  if (pid == -1)
    {
      std::cerr << "fork failed ! " << std::endl;
      return (false);
    }

  pid_t         tmpPid = pid ? pid : getpid();
  NamedPipe     *pipe1 = new NamedPipe(Plazza::makeFifoNameFromPid(tmpPid, true));
  NamedPipe     *pipe2 = new NamedPipe(Plazza::makeFifoNameFromPid(tmpPid, false));

  if (pid) // parent
    {
      this->_childs.insert(std::make_pair(pid, ChildProcess(pid, pipe1, pipe2, _nbThreads)));

      char packet[] = "Je suis un paquet !";

      Plazza::Packet::Header head;
      head.magic = Plazza::Packet::MAGIC;
      head.size = sizeof(packet);

      std::map<pid_t, ChildProcess>::iterator it = _childs.find(pid);
      if (it != _childs.end()){
        it->second.sendAction(std::make_pair("lol.txt", Plazza::Action::Type::EMAIL_ADDRESS));
      }
      // wait(0);
    }
  else // child
    {
      SubMain   *subProcess = new SubMain(getpid(), pipe1, pipe2);
      subProcess->receiveAction();
      subProcess->printActionsToDo();

      delete (subProcess);
      exit(1);
    }

  return (true);
}
