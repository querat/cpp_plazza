//
// SafeDeque.hpp for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Thu Apr 21 14:02:34 2016 querat_g
// Last update Sun Apr 24 13:51:19 2016 querat_g
//

#ifndef SAFEDEQUE_HPP_
# define SAFEDEQUE_HPP_

# include <deque>
# include <mutex>
# include <condition_variable>

//
// Thread-safe limited encapsulation of std::deque
//
template<typename T>
class SafeDeque
{
public:
  SafeDeque();
  ~SafeDeque();

private:
  std::deque<T>                 _deque;
  mutable std::mutex            _mutex;
  std::condition_variable       _cond;

public:
  void                                   push_back(const T & data);
  void                                   pop_front();
  T &                                    front();
  typename std::deque<T>::const_iterator begin() const;
  typename std::deque<T>::const_iterator end() const;
  bool                                   empty() const;
  std::condition_variable &              getCondVar();
};

template<typename T>
std::condition_variable &
SafeDeque<T>::getCondVar() {
  return (_cond);
}

template<typename T>
SafeDeque<T>::SafeDeque(){}

template<typename T>
SafeDeque<T>::~SafeDeque() {
  std::lock_guard<std::mutex> lock(_mutex);
  _deque.clear();
}

template<typename T>
void
SafeDeque<T>::push_back(const T & data) {
  std::lock_guard<std::mutex> lock(_mutex);
  _deque.push_back(data);
  _cond.notify_one();
}

template<typename T>
void
SafeDeque<T>::pop_front() {
  std::lock_guard<std::mutex> lock(_mutex);
  return (_deque.pop_front());
}

template<typename T>
T &
SafeDeque<T>::front() {
  std::lock_guard<std::mutex> lock(_mutex);
  return (_deque.front());
}

template<typename T>
typename std::deque<T>::const_iterator
SafeDeque<T>::begin() const {
  std::lock_guard<std::mutex> lock(_mutex);
  return (_deque.begin());
}

template<typename T>
typename std::deque<T>::const_iterator
SafeDeque<T>::end() const {
  std::lock_guard<std::mutex> lock(_mutex);
  return (_deque.end());
}

template<typename T>
bool
SafeDeque<T>::empty() const {
  std::lock_guard<std::mutex> lock(_mutex);
  return (_deque.empty());
}

# endif  // SAFEDEQUE_HPP_
