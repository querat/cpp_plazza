//
// ThreadPool.hh for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Sat Apr 23 09:53:14 2016 querat_g
// Last update Sat Apr 23 14:14:41 2016 querat_g
//

#ifndef THREADPOOL_HH_
# define THREADPOOL_HH_

# include <vector>

# include <mutex>
# include <condition_variable>

# include "PlazzaNameSpace.hh"

class ThreadPool
{
public:
  ThreadPool(int nbThreads, t_SafeActionDeque &act, t_SafeAnswerDeque &ans);
  ~ThreadPool();

private:
  int                   _nbThreads;
  t_ThreadVector        _threads;
  t_SafeActionDeque &   _actionDeque;
  t_SafeAnswerDeque &   _answerDeque;

public:


};

#endif
