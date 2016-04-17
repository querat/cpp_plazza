//
// NamedPipe.cpp for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Tue Apr 12 17:46:41 2016 querat_g
// Last update Thu Apr 14 15:26:32 2016 querat_g
//

#include "NamedPipe.hh"

NamedPipe::NamedPipe(std::string const & name)
  : _name(std::string("/tmp/" + name))
  , _C_name(_name.c_str())
  , _fdin(-1)
  , _fdout(-1)
{
  this->_tryCreatePipe();
  // this->_open();
}

NamedPipe::~NamedPipe()
{
  this->_close();
  unlink(this->_C_name);
}

bool
NamedPipe::_tryCreatePipe()
{
  // If the named pipe exists we can use it directly
  if (!(access(this->_C_name, F_OK)))
    return (true);

  // Else we have to create it
  if ((mknod(this->_C_name, S_IFIFO | 0666, 0)) == -1)
    {
      std::cerr << "named pipe creation failed" << std::endl;
      return (false);
    }
  return (true);
}

bool
NamedPipe::_open() {
  this->_openWritingEnd();
  this->_openReadingEnd();
  return ((IS_VALID_FD(this->_fdout)) &&
          (IS_VALID_FD(this->_fdin )) );
}

bool
NamedPipe::_openWritingEnd()
{
  this->_tryCreatePipe();
  if (!(IS_VALID_FD(this->_fdout))) // Input side of the pipe
  {
    this->_fdout = open(this->_C_name, O_WRONLY); //  | O_NONBLOCK
    if (this->_fdout == -1)
      std::cerr << "NamedPipe::open(): _fdout: "
                << strerror(errno) << std::endl;
    }
  return (this->_fdout != (-1));
}

bool
NamedPipe::_openReadingEnd()
{
  this->_tryCreatePipe();
  if (!(IS_VALID_FD(this->_fdin))) // Input side of the pipe
    {
      this->_fdin = open(this->_C_name, O_RDONLY); //  | O_NONBLOCK
      if (this->_fdin == -1)
        std::cerr << "NamedPipe::open(): _fdin: "
                  << strerror(errno) << std::endl;
    }
  return (this->_fdin != (-1));
}

bool
NamedPipe::_close() {
  if (IS_VALID_FD(this->_fdin))
    close(this->_fdin);
  if (IS_VALID_FD(this->_fdout))
    close(this->_fdout);
  this->_fdin = (-1);
  this->_fdout = (-1);

  unlink(this->_C_name);

  return (true);
}

void
NamedPipe::writeTo(std::string const & data) {
  this->_openWritingEnd();

  std::cout <<  "writing " << data << std::endl;

  write(this->_fdout, data.c_str(), (data.size() + 1));
  this->_close();
}

#define RF_BUFSIZE      2048

std::string
NamedPipe::readFrom()
{
  std::string   str("");
  char          buffer[RF_BUFSIZE + 1];

  this->_openReadingEnd();

  while ((read(this->_fdin, buffer, RF_BUFSIZE)) > 0)
    str += buffer;

  this->_close();
  return (str);
}
