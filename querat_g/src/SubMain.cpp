//
// SubMain.cpp for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Tue Apr 19 09:58:24 2016 querat_g
// Last update Thu Apr 21 11:12:03 2016 querat_g
//

#include "SubMain.hh"

Plazza::SubMain::SubMain(pid_t pid, NamedPipe *pipe1, NamedPipe *pipe2)
  : _pid(pid)
  , _shouldExit(false)
  , _pipe1(pipe1)
  , _pipe2(pipe2)
{
  // std::cerr << "SubMain " << _pid << "created" << std::endl;
}

Plazza::SubMain::~SubMain()
{
  delete (_pipe1);
  delete (_pipe2);
  // std::cerr << "SubMain " << _pid << "deleted" << std::endl;
}

bool
Plazza::SubMain::receiveAction()
{
  std::lock_guard<std::mutex>(this->_actionMutex);
  Plazza::Packet::Raw::Action   action;

  (*_pipe1) >> action;

  if (action.magic != Plazza::Packet::MAGIC)
    {
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

  _pipe2->writeTo(&head, sizeof(head));
  _pipe2->writeTo(str.c_str(), str.size() + 1);

  return (true);
}

bool
Plazza::SubMain::mainLoop()
{
  _pipe1->openReadingEnd();
  // _pipe2->openWritingEnd();

  while (!this->_shouldExit)
    {
      if (_pipe1->isReadyToRead())
        {
          CERR("shit's ready to read yo !");
          receiveAction();
        }
      else
        {
          // receiveAction();
          CERR("nothing here !");
        }
      COUT("abc");
    }

  return (true);
}
