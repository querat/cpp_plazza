//
// ICipher.hh for  in /home/schmou/cpp/cpp_plazza/include
// 
// Made by schmou_a
// Login   <schmou@epitech.net>
// 
// Started on  Thu Apr 14 09:30:08 2016 schmou_a
// Last update Mon Apr 18 13:58:52 2016 schmou_a
//

#ifndef IUNCIPHER_HH_
# define IUNCIPHER_HH_

#include <string>

class IUncipher
{

public:

  IUncipher();
  virtual ~IUncipher();

  virtual std::string	uncipher(std::string &to_uncipher const, short key const, int len const) = 0;
};

#endif
