//
// ThreadPool.cpp for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Sat Apr 23 09:54:29 2016 querat_g
// Last update Sat Apr 23 15:56:48 2016 querat_g
//

#include "DataCollector.hh"
#include "ThreadPool.hh"

void            printLol(std::mutex &mutex)
{
}

void            ThreadPool::_threadCallBack()
{
  static int    id = 0;
  dataCollector dataCollector1;
  t_FileActionPair act = std::make_pair("", Plazza::Action::Type::UNDEFINED);

  ++id;
  CERR(id << " starting");
  while (_isAlive)
  {
    _mutex.lock();
    if (!_actionDeque.empty())
    {
      act = _actionDeque.front();
      CERR("thread #" << id << "treating " << act.first);
      CERR("front = " << act.second);
      _actionDeque.pop_front();
    }
    _mutex.unlock();
    if (!act.first.empty())
    {
      CERR(id << " looped");
      _answerDeque.push_back(dataCollector1.extract_data(act));
      act = std::make_pair("", Plazza::Action::Type::UNDEFINED);
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
  for (auto it = _threads.begin(); it != _threads.end(); ++it) {
    try {
      if (it->joinable())
        it->join();
    }
    catch (const std::system_error &e)
    {
      std::cout <<"meaning "<< e.what() << std::endl;
    }
  }
}
