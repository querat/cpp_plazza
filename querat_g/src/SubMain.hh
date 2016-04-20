//
// SubMain.hh for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Tue Apr 19 09:50:04 2016 querat_g
// Last update Wed Apr 20 16:21:56 2016 querat_g
//

#ifndef SUBMAIN_HH
# define SUBMAIN_HH

# include <mutex>
# include <string>

# include <sys/types.h>
# include <unistd.h>

# include "PlazzaNameSpace.hh"
# include "NamedPipe.hh"

namespace Plazza
{
  class SubMain
  {
  public:
    SubMain(pid_t pid, NamedPipe *pipe1, NamedPipe *pipe2);
    ~SubMain();

  private:
    pid_t               _pid;
    NamedPipe *         _pipe1;
    NamedPipe *         _pipe2;
    t_ActionDeque       _actionsToDo;
    std::mutex          _actionMutex;

  public:
    bool                receiveAction(void);
    void                printActionsToDo(void) const;
    bool                sendSolvedAction(std::string const & solved);
  };
}

#endif  // SUBMAIN_HH
