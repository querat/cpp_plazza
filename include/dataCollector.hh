//
// dataCollector.hh for  in /home/schmou/cpp/cpp_plazza/include
// 
// Made by schmou_a
// Login   <schmou@epitech.net>
// 
// Started on  Mon Apr 18 14:00:21 2016 schmou_a
// Last update Thu Apr 21 15:49:07 2016 schmou_a
//

#ifndef DATACOLLECTOR_HH_
# define DATACOLLECTOR_HH_

#include "../querat_g/include/PlazzaNameSpace.hh"
#include <string>
#include <regex>

class dataCollector
{

public:

  dataCollector(t_FileActionPair &file_info, std::regex reg);
  ~dataCollector();

  std::string	extract_data();

  std::string	caesarUnCipher(const std::string &to_uncipher, const unsigned short key);
  std::string	xorUnCipher(const std::string &to_uncipher, const unsigned short key);

  std::string	caesarBruteForce(const std::string &to_uncipher);
  std::string	xorBruteForce(const std::string &to_uncipher);

  bool		heuristics_ok(const std::string &to_uncipher, const unsigned short key);
private:
  std::string  	_raw_data;
  std::string  	_processed_data;
  std::regex	_reg;
  Plazza::Action::Type _to_get;
};

#endif
