//
// ThreadPool.hh for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Sat Apr 23 09:53:14 2016 querat_g
// Last update Sun Apr 24 14:47:42 2016 querat_g
//

#ifndef THREADPOOL_HH_
# define THREADPOOL_HH_

// STL
# include <vector>

// std::thread
# include <atomic>
# include <mutex>
# include <condition_variable>

// SysUnix
# include <unistd.h>
# include <sys/types.h>
# include <pthread.h>

// Plazza
# include "PlazzaNameSpace.hh"

# define GETTID()       std::this_thread::get_id()

typedef std::condition_variable t_CondVar;

/// Creates and manage threads
class ThreadPool
{
public:
  /// Constructor
  /// nbThreads : number of desired threads
  /// act : thread safe actions deque reference
  /// ans : thread safe answer deque reference
  ThreadPool(int nbThreads, t_SafeActionDeque &act, t_SafeAnswerDeque &ans);
  /// destructor
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
