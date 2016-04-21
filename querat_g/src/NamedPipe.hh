//
// NamedPipe.hh for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Tue Apr 12 17:53:29 2016 querat_g
// Last update Thu Apr 21 11:02:52 2016 querat_g
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
# include <poll.h>

// C++
# include <iostream>
# include <fstream>
# include <sstream>

# include "PlazzaNameSpace.hh"

# define IS_VALID_FD(fd) ((fd != (-1)))

class    NamedPipe
{
public:                // Ctor Dtor
  NamedPipe(std::string const & name);
  ~NamedPipe();

private:               // Attributes
  std::string const     _name;
  char const *          _C_name;

  int                   _fdin;
  int                   _fdout;

  bool                  _open();
  bool                  _close();
  bool                  _tryCreatePipe();

private:                // Private member functions
  int                   _readASync(void *buffer, size_t size);

public:                 // I/O operations
  bool                  openWritingEnd();
  bool                  openReadingEnd();
  void                  writeTo(void const *data, size_t size);
  bool                  readFrom(void *buffer, size_t size);

public:                 // GetSet
  int                   getFdIn() const;
  int                   getFdOut() const;

public:                 // Bool
  bool                  isReadyToRead();

};

NamedPipe &             operator<<(NamedPipe &dis, t_FileActionPair const & pair);
NamedPipe &             operator>>(NamedPipe &dis, t_FileActionPair & pair);
NamedPipe &             operator>>(NamedPipe &dis, Plazza::Packet::Raw::Action & act);

#endif // NAMEDPIPE_HH_
