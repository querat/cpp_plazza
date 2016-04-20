//
// Process.cpp for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Mon Apr 18 15:04:35 2016 querat_g
// Last update Wed Apr 20 10:26:48 2016 querat_g
//

#include "ChildProcess.hh"

ChildProcess::ChildProcess(pid_t pid, NamedPipe *pipe1, NamedPipe *pipe2, int nbThreads)
  : _pid(pid)
  , _pipe1(pipe1)
  , _pipe2(pipe2)
  , _nbCurrentActions(0)
  , _maxActions(PLAZZA_MAX_ACTIONS(nbThreads))
{
  // std::cerr << "ChildProcess " << std::to_string(_pid) << "created" << std::endl;
}

ChildProcess::~ChildProcess(){
  // std::cerr << "ChildProcess " << std::to_string(_pid) << "deleted" << std::endl;
}

void
ChildProcess::sendData(void const *data, size_t size)
{
  Plazza::Packet::Header        head;

  // pas de constructeur dans le header ...
  head.magic = Plazza::Packet::MAGIC;
  head.size = size;

  // on envoie le header dans le pipe
  _pipe1->writeTo(&head, sizeof(Plazza::Packet::Header));

  // Puis les données brutes
  _pipe1->writeTo(data, size);
}

bool
ChildProcess::sendAction(t_FileActionPair const & fileActionPair)
{
  if (_nbCurrentActions >= _maxActions)
    return (false);

  (*_pipe1) << fileActionPair;

  return (true);
}

void
ChildProcess::sendSignal(int sig) const
{
  kill(this->_pid, sig);
}
