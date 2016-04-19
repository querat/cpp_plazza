//
// Caesar.hh for  in /home/schmou/cpp/cpp_plazza/include
// 
// Made by schmou_a
// Login   <schmou@epitech.net>
// 
// Started on  Thu Apr 14 09:48:33 2016 schmou_a
// Last update Mon Apr 18 13:59:00 2016 schmou_a
//

#ifndef CAESAR_HH_
# define CAESAR_HH_

#include "IUncipher.hh"

class Caesar : public IUncipher
{

public:

  Caesar();
  ~Caesar();

  std::string   uncipher(std::string &to_uncipher const, short key const, int len const);

};

#endif
