//
// SafeDeque.hpp for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Thu Apr 21 14:02:34 2016 querat_g
// Last update Thu Apr 21 15:42:19 2016 querat_g
//

#ifndef SAFEDEQUE_HPP_
# define SAFEDEQUE_HPP_

# include <deque>
# include <mutex>

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
  std::deque<T>         _deque;
  mutable std::mutex    _mutex;

public:
  void                                   push_back(const T & data);
  void                                   pop_front();
  T &                                    front();
  typename std::deque<T>::const_iterator begin() const;
  typename std::deque<T>::const_iterator end() const;
  bool                                   empty() const;
};

template<typename T>
SafeDeque<T>::SafeDeque(){}

template<typename T>
SafeDeque<T>::~SafeDeque() {
  _deque.clear();
}

template<typename T>
void
SafeDeque<T>::push_back(const T & data) {
  std::lock_guard<std::mutex> lock(_mutex);
  _deque.push_back(data);
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
  return (_deque.empty());
}

# endif  // SAFEDEQUE_HPP_
