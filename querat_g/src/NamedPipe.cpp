//
// NamedPipe.cpp for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Tue Apr 12 17:46:41 2016 querat_g
// Last update Wed Apr 13 16:40:49 2016 querat_g
//

#include "NamedPipe.hh"

NamedPipe::NamedPipe(std::string const & name)
  : _name(std::string("/tmp/" + name))
{
  // If the named pipe exists we can use it directly
  if (!(access(this->_name.c_str(), F_OK)))
    return ;

  // Else we have to create it
  if ((mknod(this->_name.c_str(), S_IFIFO | 0666, 0)) == -1)
    {
      std::cerr << "named pipe creation failed" << std::endl;
      return ;
    }

  // this->_open();
}

NamedPipe::~NamedPipe()
{
  // this->_close();
  // if (!(access(this->_name.c_str(), F_OK)))
  //   unlink(this->_name.c_str());
}

bool
NamedPipe::_open() {
  if (!this->_ifstream)
    this->_ifstream.open(this->_name.c_str());
  if (!this->_ofstream)
    this->_ofstream.open(this->_name.c_str());

  return (this->_ifstream && this->_ofstream);
}

bool
NamedPipe::_close() {
  if (this->_ifstream)
    this->_ifstream.close();
  if (this->_ofstream)
    this->_ofstream.close();
  return (true);
}

std::ofstream &
NamedPipe::getWritingEnd() {
  this->_ofstream.open(_name.c_str());
  return (this->_ofstream);
}
std::ifstream &
NamedPipe::getReadingEnd() {
  this->_ifstream.open(_name.c_str());
  return (this->_ifstream);
}

void
NamedPipe::write(std::string const & data) {
  this->_open();
  this->_ofstream.open(_name.c_str());
  if (!_ofstream) std::cerr << "can't write" << std::endl;

  std::cout <<  "writing " << data << std::endl;
  _ofstream << data;
  this->_close();
}

std::string
NamedPipe::read()
{
  std::stringstream buf;

  this->_open();
  buf << this->_ifstream.rdbuf();
  this->_close();
  return (buf.str());
}
