//
// ThreadPool.cpp for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Sat Apr 23 09:54:29 2016 querat_g
// Last update Sat Apr 23 16:47:26 2016 querat_g
//

#include "ThreadPool.hh"

void            printLol(std::mutex &mutex)
{
}

void            ThreadPool::_threadCallBack()
{
  static int    id = 0;

  ++id;
  CERR(id << " starting");
  while (_isAlive)
  {
    //_mutex.lock();
    std::unique_lock<std::mutex> guard(_mutex);
    if (!_actionDeque.empty()) {
     t_FileActionPair act = _actionDeque.front();

      CERR("thread #" << id << "treating " << act.first);

      _actionDeque.pop_front();
      CERR(id << " looped");
      //_mutex.unlock();
    }
  }
  CERR((id - 1) << " has ded");
}

ThreadPool::ThreadPool(int nbThreads, t_SafeActionDeque &act, t_SafeAnswerDeque &ans)
  : _nbThreads(nbThreads)
  , _actionDeque(act)
  , _answerDeque(ans)
  , _isAlive(true)
{

  for (int i = 0; i < _nbThreads; i++) {
    _threads.push_back(std::thread([this](){this->_threadCallBack();}));
  }

}

ThreadPool::~ThreadPool()
{
  _isAlive = false;
  for (t_ThreadVector::iterator it = _threads.begin(); it != _threads.end(); ++it) {
    it->join();
  }
}
