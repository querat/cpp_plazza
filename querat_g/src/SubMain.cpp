//
// SubMain.cpp for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Tue Apr 19 09:58:24 2016 querat_g
// Last update Tue Apr 19 14:42:21 2016 querat_g
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

void
Plazza::SubMain::doSomething()
{
  Plazza::Packet::Header  header;

  std::cerr << _pid << "Waiting for packet header ..." << std::endl;

  if (!this->_pipe1->readFrom(&header, sizeof(Plazza::Packet::Header)))
    {
      std::cerr << "invalid header size" << std::endl;
      return ;
    }

  std::cerr << "I got the packet header !" << std::endl;
  std::cerr << "magic : " << std::hex << header.magic << std::endl;
  std::cerr << "size : " << std::hex << header.size << std::endl;
}
