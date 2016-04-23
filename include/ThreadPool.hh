//
// ThreadPool.hh for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Sat Apr 23 09:53:14 2016 querat_g
// Last update Sat Apr 23 10:16:34 2016 querat_g
//

#ifndef THREADPOOL_HH_
# define THREADPOOL_HH_

# include <mutex>

# include "PlazzaNameSpace.hh"

class ThreadPool
{
public:
  ThreadPool(int nbThreads);
  ~ThreadPool();

private:
  int                   _nbThreads;



public:


};

#endif
