//
// Process.cpp for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Mon Apr 18 15:04:35 2016 querat_g
// Last update Wed Apr 20 16:22:35 2016 querat_g
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

bool
ChildProcess::receiveAnswer()
{
  Plazza::Packet::Header        head;
  char                          *raw = nullptr;

  std::memset(&head, '\0', sizeof(head));

  if (!_pipe2->readFrom(&head, sizeof(head))){
    std::cerr << "Couldn't read answer header" << std::endl;
    return (false);
  }

  if (head.magic != Plazza::Packet::MAGIC) {
    std::cerr << "bad answer header magic" << std::endl;
    return (false);
  }

  raw = new char[head.size];
  if (!_pipe2->readFrom(raw, head.size)) {
    CERR("Couldn't read raw answer data");
    return (false);
  }

  _answerStack.push(std::string(raw));

  delete []raw;

  return (true);
}

void
ChildProcess::popPrintAnswers()
{
  while (!_answerStack.empty())
    {
      std::cout << _answerStack.top() << std::endl;
      _answerStack.pop();
    }
}
