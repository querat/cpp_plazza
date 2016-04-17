//
// NamedPipe.hh for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Tue Apr 12 17:53:29 2016 querat_g
// Last update Thu Apr 14 15:26:21 2016 querat_g
//

#ifndef NAMEDPIPE_HH_
# define NAMEDPIPE_HH_

// C
# include <cstdio>
# include <cstring> // strerror

// SysUnix
# include <unistd.h>
# include <fcntl.h>
# include <error.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/select.h>
# include <sys/time.h>

// C++
# include <iostream>
# include <fstream>
# include <sstream>

# define IS_VALID_FD(fd) ((fd != (-1)))

class	NamedPipe
{
 public:
  NamedPipe(std::string const & name);
  ~NamedPipe();

 private:
  std::string const	_name;
  char const *          _C_name;

  int                   _fdin;
  int                   _fdout;

  bool			_open();
  bool			_close();
  bool                  _openReadingEnd();
  bool                  _openWritingEnd();
  bool                  _tryCreatePipe();

public:

  void			writeTo(std::string const & data);
  std::string		readFrom();
};

#endif // NAMEDPIPE_HH_
