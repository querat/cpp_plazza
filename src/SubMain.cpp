//
// SubMain.cpp for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Tue Apr 19 09:58:24 2016 querat_g
// Last update Sat Apr 23 17:57:48 2016 querat_g
//

#include "SubMain.hh"
#include "SafeDeque.hpp"

Plazza::SubMain::SubMain(pid_t pid, NamedPipe *pipe1, NamedPipe *pipe2, int nbThreads)
  : _pid(pid)
  , _pipe1(pipe1)
  , _pipe2(pipe2)
  , _clock(time(NULL))
  , _timeSinceLastEvent(0)
  , _nbThreads(nbThreads)
  , _threads(nbThreads, _actionsToDo, _answers)
{
  // std::cerr << "SubMain " << _pid << "created" << std::endl;
}

Plazza::SubMain::~SubMain()
{
  delete (_pipe1);
  delete (_pipe2);
  DEBUG(_pid << " Plazza::SubMain::~SubMain(): no tasks for 5 seconds, exiting");
}

bool
Plazza::SubMain::receiveAction()
{
  Plazza::Packet::Raw::Action   action;

  DEBUG("receiving action...");
  (*_pipe1) >> action;
  DEBUG("... Ok");

  if (action.magic != Plazza::Packet::MAGIC) {
    std::cerr << _pid << " could not get action from _pipe1" << std::endl;
    return (false);
  }

  this->_actionsToDo.push_back(std::make_pair(action.fileName, action.type));

  return (true);
}

void
Plazza::SubMain::printActionsToDo() const
{
  t_ActionDeque::const_iterator it = _actionsToDo.begin();

  while (it != _actionsToDo.end())
    {
      std::cout << it->second << " " << it->first  << std::endl;
      ++it;
    }
}

bool
Plazza::SubMain::sendSolvedAction(std::string const & str)
{
  Plazza::Packet::Header        head;

  head.magic = Plazza::Packet::MAGIC;
  head.size = str.size() + 1;

  DEBUG("sending answer back to Main process ...");
  _pipe2->writeTo(&head, sizeof(head));
  _pipe2->writeTo(str.c_str(), str.size() + 1);
  DEBUG("Answer sent !");

  // sleep(2);

  return (true);
}

void
Plazza::SubMain::_incrementTimeSinceLastEvent() {
  time_t now = time(NULL);

  _timeSinceLastEvent += (now - _clock);
  _clock = now;
}

void
Plazza::SubMain::_resetTimeSinceLastEvent() {
  DEBUG("resetting clock()");
  _timeSinceLastEvent = 0;
}

bool
Plazza::SubMain::_shouldExit() const {
  return ((_timeSinceLastEvent > 5.0f) &&
          (_actionsToDo.empty())  &&
          (_answers.empty()));
}

bool
Plazza::SubMain::mainLoop()
{
  _pipe1->openReadingEnd();

  while (!this->_shouldExit())
    {
      if (_pipe1->isReadyToRead())
        {
          DEBUG("shit's ready to read yo !");
          receiveAction();
        }

      if (!_answers.empty()) {
        sendSolvedAction(_answers.front());
        _answers.pop_front();
      }

      _incrementTimeSinceLastEvent();
    }

  return (true);
}

bool
Plazza::SubMain::processAction()
{
  if (_actionsToDo.empty())
    return (false);
  _resetTimeSinceLastEvent();
  // the deque is supposed to be thread safe
  t_FileActionPair      &action = _actionsToDo.front();

  DEBUG("_action being done: " << action.first << " & " << action.second);

  std::string TODO("this is an answer from pid ");
  sendSolvedAction(TODO);

  _actionsToDo.pop_front();
  return (true);
}
