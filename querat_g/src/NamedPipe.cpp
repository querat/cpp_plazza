//
// NamedPipe.cpp for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Tue Apr 12 17:46:41 2016 querat_g
// Last update Wed Apr 13 17:24:50 2016 querat_g
//

#include "NamedPipe.hh"

NamedPipe::NamedPipe(std::string const & name)
  : _name(std::string("/tmp/" + name))
  , _C_name(_name.c_str())
  , _fdin(-1)
  , _fdout(-1)
{
  // If the named pipe exists we can use it directly
  if (!(access(this->_C_name, F_OK)))
    return ;

  // Else we have to create it
  if ((mknod(this->_C_name, S_IFIFO | 0666, 0)) == -1)
    {
      std::cerr << "named pipe creation failed" << std::endl;
      return ;
    }

  this->_open();
}

NamedPipe::~NamedPipe()
{
  this->_close();
  unlink(this->_C_name);
}

bool
NamedPipe::_open() {

  if (!(IS_VALID_FD(this->_fdin))) // Input side of the pipe
  {
    this->_fdin = open(this->_C_name, O_RDONLY | O_NONBLOCK);
    if (this->_fdin == -1)
      std::cerr << "NamedPipe::open(): _fdin: "
                << strerror(errno) << std::endl;
    }

  if (!(IS_VALID_FD(this->_fdout))) // output side of the pipe
    {
      this->_fdout = open(this->_C_name, O_WRONLY | O_NONBLOCK);
      if (this->_fdout == -1)
        std::cerr << "NamedPipe::open(): _fdout: "
                  << strerror(errno) << std::endl;
    }
  return ((IS_VALID_FD(this->_fdin))  &&
          (IS_VALID_FD(this->_fdout)) );
}

bool
NamedPipe::_close() {
  if (IS_VALID_FD(this->_fdin))
    close(this->_fdin);
  if (IS_VALID_FD(this->_fdout))
    close(this->_fdout);
  return (true);
}

int
NamedPipe::getWritingEnd() {
  this->_open();
  return (this->_fdout);
}
int
NamedPipe::getReadingEnd() {
  this->_open();
  return (this->_fdin);
}

void
NamedPipe::writeTo(std::string const & data) {
  if (!this->_open())
    std::cerr << "can't open shit yo" << std::endl;

  std::cout <<  "writing " << data << std::endl;

  write(this->_fdout, data.c_str(), data.size());
  this->_close();
}

std::string
NamedPipe::readFrom()
{
  std::string   str("");
  char          buffer[2048];

  this->_open();

  while ((read(this->_fdin, buffer, sizeof(buffer))) > 0)
    str += buffer;

  this->_close();
  return (str);
}
