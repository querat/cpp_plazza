//
// dataCollector.cpp for  in /home/schmou/cpp/cpp_plazza/src
//
// Made by schmou_a
// Login   <schmou@epitech.net>
//
// Started on  Mon Apr 18 14:00:01 2016 schmou_a
// Last update Sat Apr 23 11:07:31 2016 querat_g
//

#include <sstream>
#include <fstream>
#include <iostream>
#include "DataCollector.hh"

dataCollector::dataCollector()
{
}

dataCollector::~dataCollector()
{
}

int		dataCollector::my_isprint(char c)
{
  return (isprint(c) || c == '\n' || c == '\t' || c == '\a' ||
          c == '\v' || c == '\r');
}

std::string   dataCollector::caesarUnCipher(const std::string &to_uncipher, const unsigned short key)
{
  std::string   ret;

  if (!heuristicsCaesar(to_uncipher, key))
    return "";
  for (unsigned long i = 0; i < to_uncipher.length(); i++)
    ret.push_back(static_cast<char>(to_uncipher[i] - key));
  return (ret);
}

bool		dataCollector::heuristicsCaesar(const std::string &to_uncipher, const unsigned short key)
{
  unsigned long       len = to_uncipher.length();
  unsigned long       nb_printable_chars = 0;
  unsigned long       i = 0;

  for (; i <= 100 && i < len; i++)
  {
    if (my_isprint((char) (to_uncipher[i] - key)))
      nb_printable_chars++;
  }
  return nb_printable_chars >= i;
}

bool		dataCollector::heuristicsXor(const std::string &to_uncipher, const unsigned short key)
{
  unsigned long       len = to_uncipher.length();
  unsigned long       nb_printable_chars = 0;
  unsigned long       i = 0;
  char		          strong = key >> 8;

  for (; i <= 100 && i < len; i++)
    {
      if (my_isprint(to_uncipher[i] ^ strong))
	nb_printable_chars++;
      if (my_isprint(to_uncipher[i + 1] ^ key))
	nb_printable_chars++;
      i++;
    }
  return nb_printable_chars >= i;
}

std::string   dataCollector::xorUnCipher(const std::string &to_uncipher, const unsigned short key)
{
  std::string   ret;

  if (!heuristicsXor(to_uncipher, key))
    return "";
  for (unsigned long i = 0; i < to_uncipher.length(); i++)
    {
      ret.push_back(static_cast<char>(to_uncipher[i] ^ (key >> 8)));
      ret.push_back(static_cast<char>(to_uncipher[i + 1] ^ key));
      i++;
    }
  return (ret);
}

std::string   dataCollector::xorBruteForce(const std::string &to_uncipher)
{
  std::string	tmp;
  std::smatch	checker;
  const std::sregex_token_iterator End;

  for (unsigned short key = 1; key < 0xFFFF; key++)
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

std::string   dataCollector::caesarBruteForce(const std::string &to_uncipher)
{
  std::string	tmp;
  std::smatch	checker;
  const std::sregex_token_iterator End;

  for (unsigned short key = 1; key < 0xFF; key++)
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

std::string	dataCollector::extract_data(t_FileActionPair &file_info)
{
  std::string	tmp = _raw_data;
  std::smatch	checker;
  const std::sregex_token_iterator End;
  std::ifstream	file(file_info.first.c_str(), std::ios::in);
  std::stringstream stream;

  if (file)
  {
    stream << file.rdbuf();
    _raw_data = stream.str();
    _to_get = file_info.second;
    _processed_data = "";
    file.close();
  }
  else
    _processed_data.assign("Error while constructing the data collector. (No such file or directory)");
  switch (_to_get)
  {
    case Plazza::Action::EMAIL_ADDRESS:
      _reg.assign(Plazza::Regex::map.at(Plazza::Action::Type::EMAIL_ADDRESS));
          break;
    case Plazza::Action::IP_ADDRESS:
      _reg.assign(Plazza::Regex::map.at(Plazza::Action::Type::IP_ADDRESS));
          break;
    case Plazza::Action::PHONE_NUMBER:
      _reg.assign(Plazza::Regex::map.at(Plazza::Action::Type::PHONE_NUMBER));
          break;
    default:
      _reg.assign(Plazza::Regex::map.at(Plazza::Action::Type::UNDEFINED));
          break;
  }
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
