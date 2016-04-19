//
// SubMain.cpp for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Tue Apr 19 09:58:24 2016 querat_g
// Last update Tue Apr 19 18:26:56 2016 querat_g
//

#include "SubMain.hh"

Plazza::SubMain::SubMain(pid_t pid, NamedPipe *pipe1, NamedPipe *pipe2)
  : _pid(pid)
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

void *
Plazza::SubMain::receiveData()
{
  Plazza::Packet::Header  header;

  std::cerr << _pid << "Waiting for packet header ..." << std::endl;

  if (!this->_pipe1->readFrom(&header, sizeof(Plazza::Packet::Header)))
    {
      std::cerr << "invalid header read() size" << std::endl;
      return (nullptr);
    }

  std::cerr << "I got the packet header !" << std::endl;
  std::cerr << "magic : " << std::hex << header.magic << std::endl;
  std::cerr << "size : " << std::hex << header.size << std::endl;

  char *dataBuffer = new char[header.size];

  if (!this->_pipe1->readFrom(dataBuffer, header.size))
    {
      std::cerr << "Could not read Plazza::Packet's raw data" << std::endl;
      delete (dataBuffer);
      return (nullptr);
    }

  return (dataBuffer);
}

void
Plazza::SubMain::testReceive()
{
  Plazza::Packet::Header  header;

  std::cerr << _pid << "Waiting for packet header ..." << std::endl;

  if (!this->_pipe1->readFrom(&header, sizeof(Plazza::Packet::Header)))
    {
      std::cerr << "invalid header read size" << std::endl;
      return ;
    }

  if (header.magic != Plazza::Packet::MAGIC)
    {
      std::cerr << "invalid Plazza::Packet::MAGIC code" << std::endl;
      return ;
    }

  std::cerr << "I got the packet header !" << std::endl;
  std::cerr << "magic : " << std::hex << header.magic << std::endl;
  std::cerr << "size : " << std::hex << header.size << std::endl;

  char *dataBuffer = new char[header.size];

  if (!this->_pipe1->readFrom(dataBuffer, header.size))
    {
      std::cerr << "Could not read" << std::endl;
      return ;
    }
  std::cerr << "I got the packet" << std::endl;
  delete (dataBuffer);
}

bool
Plazza::SubMain::receiveAction()
{
  std::lock_guard<std::mutex>(this->_actionMutex);
  Plazza::Packet::Header        header;
  Plazza::Packet::Raw::Action   action;

  std::cerr << _pid << "Waiting for packet header ..." << std::endl;

  if (!this->_pipe1->readFrom(&header, sizeof(Plazza::Packet::Header))) {
    std::cerr << "invalid header read size" << std::endl;
    return (false);
  }
  if (header.magic != Plazza::Packet::MAGIC) {
    std::cerr << "invalid Plazza::Packet::MAGIC code" << std::endl;
    return (false);
  }

  if (!this->_pipe1->readFrom(&action, sizeof(action))) {
    std::cerr << "invalid Plazza::Packet::Raw::Action read size" << std::endl;
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
      Plazza::printAction(it->second);
      std::cout << " " << it->first  << std::endl;
      ++it;
    }
}
