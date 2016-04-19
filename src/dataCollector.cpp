//
// dataCollector.cpp for  in /home/schmou/cpp/cpp_plazza/src
// 
// Made by schmou_a
// Login   <schmou@epitech.net>
// 
// Started on  Mon Apr 18 14:00:01 2016 schmou_a
// Last update Mon Apr 18 18:36:12 2016 schmou_a
//

#include "dataCollector.hh"
#include <fstream>

dataCollector::dataCollector(t_FileActionPair &file_info, std::regex reg)
{
  std::ifstream	file(file_info.first.c_str());

  if (file.is_open())
    {
      file >> _raw_data;
      _reg = reg;
      _to_get = file_info.second;
    }
  else
    _processed_data.assign("Error while constructing the data collector.");
}

dataCollector::~dataCollector() {}

std::string   dataCollector::caesarUnCipher(const std::string &to_uncipher, const unsigned short key)
{
  std::string   ret;
  int		len = to_uncipher.size();

  for (int i = 0; i < len; i++)
    ret.push_back(to_uncipher[i] - key);
  return (ret);
}

std::string   dataCollector::xorUnCipher(const std::string &to_uncipher, const unsigned short key)
{
  std::string   ret;
  int		len = to_uncipher.size();

  for (int i = 0; i < len; i++)
    ret.push_back(to_uncipher[i] ^ key);
  return (ret);
}

std::string   dataCollector::caesarBruteForce(const std::string &to_uncipher)
{
  std::string	tmp;
  std::smatch	checker;

  for (unsigned short key = 0; key < 256; key++)
    {
      tmp = caesarUnCipher(to_uncipher, key);
      std::regex_search(tmp, checker, _reg);
      if (checker[1].str().length() > 0)
	_processed_data += checker[1].str();
    }
  return _processed_data;
}

std::string   dataCollector::xorBruteForce(const std::string &to_uncipher)
{
  std::string	tmp;
  std::smatch	checker;

  for (unsigned short key = 0; key < 256; key++)
    {
      tmp = xorUnCipher(to_uncipher, key);
      std::regex_search(tmp, checker, _reg);
      if (checker[1].str().length() > 0)
	_processed_data += checker[1].str();
    }
  return _processed_data;
}

std::string	dataCollector::extract_data()
{
  std::string	tmp;
  std::smatch	checker;

  std::regex_search(tmp, checker, _reg);
  if (checker[1].str().length() > 0)
    _processed_data += checker[1].str();
  else
    {
      caesarBruteForce(_raw_data);
      xorBruteForce(_raw_data);
    }
  return _processed_data;
}
