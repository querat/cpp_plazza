//
// ThreadPool.cpp for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Sat Apr 23 09:54:29 2016 querat_g
// Last update Sat Apr 23 14:14:32 2016 querat_g
//

#include "ThreadPool.hh"

std::mutex      mutmut;

void            printLol() {
  mutmut.lock();
  CERR("thread callBack()");
  mutmut.unlock();
}

void            threadCallback()
{
  while (1) {
    printLol();
  }
}

ThreadPool::ThreadPool(int nbThreads, t_SafeActionDeque &act, t_SafeAnswerDeque &ans)
  : _nbThreads(nbThreads)
  , _actionDeque(act)
  , _answerDeque(ans)
{

  for (int i = 0; i < _nbThreads; i++) {
    _threads.push_back(std::thread(&threadCallback));
  }

}

ThreadPool::~ThreadPool()
{
  for (auto it = _threads.begin(); it != _threads.end(); ++it) {
    it->join();
  }

}
