//
// caesar.cpp for  in /home/schmou/cpp/cpp_plazza/src
// 
// Made by schmou_a
// Login   <schmou@epitech.net>
// 
// Started on  Thu Apr 14 10:27:38 2016 schmou_a
// Last update Mon Apr 18 13:58:24 2016 schmou_a
//

#include "Caesar.hh"

Caesar() {}

~Caesar() {}

std::string	uncipher(std::string &to_uncipher const, short key const, int len const)
{
  std::string	ret;

  for (i = 0; i < len; i++)
    ret.append(to_uncipher[i] - key);
  return (ret);
}
