//
// NamedPipe.hh for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Tue Apr 12 17:53:29 2016 querat_g
// Last update Wed Apr 13 16:32:38 2016 querat_g
//

#ifndef NAMEDPIPE_HH_
# define NAMEDPIPE_HH_

// C
# include <cstdio>

// SysUnix
# include <unistd.h>
# include <fcntl.h>
# include <error.h>
# include <sys/stat.h>
# include <sys/types.h>

// C++
# include <iostream>
# include <fstream>
# include <sstream>

class	NamedPipe
{
 public:
  NamedPipe(std::string const & name);
  ~NamedPipe();

 private:
  std::string const	_name;
  std::ifstream		_ifstream;
  std::ofstream		_ofstream;

  bool			_open();
  bool			_close();

public:
  std::ifstream &	getReadingEnd();
  std::ofstream &	getWritingEnd();

  void			write(std::string const & data);
  std::string		read();
};

#endif // NAMEDPIPE_HH_
