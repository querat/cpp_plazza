//
// Process.cpp for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Mon Apr 18 15:04:35 2016 querat_g
// Last update Fri Apr 22 22:05:57 2016 querat_g
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
  // delete(_pipe1);
  // delete(_pipe2);
  // std::cerr << "ChildProcess " << std::to_string(_pid) << "deleted" << std::endl;
}

bool
ChildProcess::sendAction(t_FileActionPair const & fileActionPair)
{
  if (this->reachedMaxCharge()) {
    CERR(_pid << " reached max actions, canceling sendAction()");
    return (false);
  }

  DEBUG("sending stuff ...");
  (*_pipe1) << fileActionPair;
  ++this->_nbCurrentActions;
  DEBUG("... sent stuff");

  return (true);
}

bool
ChildProcess::hasAnswerReady() {
  return (_pipe2->isReadyToRead());
}

bool
ChildProcess::receiveAnswer(std::deque<std::string> &answerStack)
{
  Plazza::Packet::Header        head;
  char                          *raw = nullptr;

  std::memset(&head, '\0', sizeof(head));

  if (!_pipe2->readFrom(&head, sizeof(head))) {
    CERR("Couldn't read answer header");
    return (false);
  }

  if (head.magic != Plazza::Packet::MAGIC) {
    CERR("bad answer header magic");
    return (false);
  }

  raw = new char[head.size];
  if (!_pipe2->readFrom(raw, head.size)) {
    CERR("Couldn't read raw answer data");
    return (false);
  }

  answerStack.push_back(std::string(raw));

  delete []raw;

  --this->_nbCurrentActions;

  return (true);
}

bool
ChildProcess::reachedMaxCharge() const {
  return (_nbCurrentActions >= _maxActions);
}

bool
ChildProcess::isBusy() const {
  return (_nbCurrentActions > 0);
}

void
ChildProcess::popPrintAnswers()
{
  while (!_answerStack.empty())
    {
      std::cout << _answerStack.front() << std::endl;
      _answerStack.pop_front();
    }
}

pid_t
ChildProcess::getPid() const {
  return (_pid);
}

int
ChildProcess::sendSignal(int sig) const {
  return (kill(this->_pid, sig));
}

bool
ChildProcess::isAlive() const {
   // Necessary, otherwise the process will be a zombie, and
  // kill() will still consider it alive !
  waitpid(this->_pid, nullptr, WNOHANG);

  // no signal sent, 0 just ckecks for the existence of _pid
  return (((kill(this->_pid, 0)) == 0));
}
