//
// ThreadPool.hh for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Sat Apr 23 09:53:14 2016 querat_g
// Last update Sat Apr 23 16:53:56 2016 querat_g
//

#ifndef THREADPOOL_HH_
# define THREADPOOL_HH_

# include <vector>

# include <atomic>
# include <mutex>
# include <condition_variable>

# include "PlazzaNameSpace.hh"

typedef std::condition_variable t_CondVar;

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

  std::atomic<bool>     _isAlive;

  t_CondVar             _cond;
  std::mutex            _mutex;

  int                   _busy;

private:
  void                  _threadCallBack();
  void                  _incrementBusyThreadsNum();
  void                  _decrementBusyThreadsNum();

public:

};

#endif
