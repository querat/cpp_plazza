//
// dataCollector.cpp for  in /home/schmou/cpp/cpp_plazza/src
// 
// Made by schmou_a
// Login   <schmou@epitech.net>
// 
// Started on  Mon Apr 18 14:00:01 2016 schmou_a
// Last update Mon Apr 18 18:36:12 2016 schmou_a
//

#include <fstream>
#include <iostream>
#include "dataCollector.hh"

dataCollector::dataCollector(t_FileActionPair &file_info, std::regex reg)
{
  std::ifstream	file(file_info.first.c_str(), std::ios::in);
  std::stringstream stream;

  if (file)
    {
      stream << file.rdbuf();
      _raw_data = stream.str();
      _reg = reg;
      _to_get = file_info.second;
      _processed_data = "";
      file.close();
    }
  else
  {
    std::cerr << "Error code:" << strerror(errno);
    _processed_data.assign("Error while constructing the data collector.");
  }
}

dataCollector::~dataCollector() {}

std::string   dataCollector::caesarUnCipher(const std::string &to_uncipher, const unsigned short key)
{
  std::string   ret;

  if (!isprint(to_uncipher[0] - key))
    return "";
  for (unsigned long i = 0; i < to_uncipher.length(); i++)
    ret.push_back(static_cast<char>(to_uncipher[i] - key));
  return (ret);
}

std::string   dataCollector::xorUnCipher(const std::string &to_uncipher, const unsigned short key)
{
  std::string   ret;

  if (!isprint(to_uncipher[0] ^ key))
    return "";
  for (unsigned long i = 0; i < to_uncipher.length(); i++)
    ret.push_back(static_cast<char>(to_uncipher[i] ^ key));
  return (ret);
}

std::string   dataCollector::caesarBruteForce(const std::string &to_uncipher)
{
  std::string	tmp;
  std::smatch	checker;
  const std::sregex_token_iterator End;

  for (unsigned short key = 1; key < 255; key++)
    {
      tmp = caesarUnCipher(to_uncipher, key);
      if (std::regex_search(tmp, checker, _reg))
      {
        for (std::sregex_token_iterator it(tmp.begin(), tmp.end(), _reg); it != End; ++it)
        {
          _processed_data += *it;
          _processed_data.push_back('\n');
        }
      }
    }
  return _processed_data;
}

std::string   dataCollector::xorBruteForce(const std::string &to_uncipher)
{
  std::string	tmp;
  std::smatch	checker;
  const std::sregex_token_iterator End;

  for (unsigned short key = 1; key < 0xFFU; key++)
    {
      tmp = xorUnCipher(to_uncipher, key);
      if (std::regex_search(tmp, checker, _reg))
      {
        for (std::sregex_token_iterator it(tmp.begin(), tmp.end(), _reg); it != End; ++it)
        {
          _processed_data += *it;
          _processed_data.push_back('\n');
        }
      }
    }
  return _processed_data;
}

std::string	dataCollector::extract_data()
{
  std::string	tmp = _raw_data;
  std::smatch	checker;
  const std::sregex_token_iterator End;

  if (std::regex_search(tmp, checker, _reg))
  {
    for (std::sregex_token_iterator it(tmp.begin(), tmp.end(), _reg); it != End; ++it)
    {
      _processed_data += *it;
      _processed_data.push_back('\n');
    }
  }
  else
    {
      caesarBruteForce(_raw_data);
      xorBruteForce(_raw_data);
    }
  return _processed_data;
}
