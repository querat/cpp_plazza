//
// Parser.cpp for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Sun Apr 17 14:24:34 2016 querat_g
// Last update Sun Apr 17 20:27:24 2016 querat_g
//

#include "Parser.hh"

Parser::Parser()
  : _cutList()
{}

Parser::~Parser(){}

bool
Parser::_splitStringToList(std::string const &str)
{
  char          *copy = strdup(str.c_str());

  if (!copy) {
    std::cerr << "Parser::_splitStringToList: "
              << strerror(errno) << std::endl;
    return (false);
  }

  char const    *tok = strtok(copy, COMMAND_DELIMITERS);

  while (copy && tok != 0) {
    _cutList.push_back(std::string(tok));
    tok = strtok(nullptr, COMMAND_DELIMITERS);
  }
  free(copy);

  return (true);
}

bool
Parser::_tokenizeCommand(std::string const &line)
{
  char          *copy = strdup(line.c_str());

  if (!copy) {
    std::cerr << "Parser::_tokenizeCommand: "
              << strerror(errno) << std::endl;
    return (false);
  }

  char const    *tok = strtok(copy, WORDS_DELIMITERS);

  while (tok != 0) {
    _tokList.push_back(std::string(tok));
    tok = strtok(nullptr, WORDS_DELIMITERS);
  }
  free(copy);

  return (true);
}

int
Parser::_countActions() const {
  return (std::count_if(_tokList.begin(), _tokList.end(), Plazza::isAnAction));
}

bool
Parser::_invalidActionsNumberErrorHandler(int nbActions, std::string const & line) {
  _tokList.clear();

  if (nbActions < 1){
    std::cerr << "No action detected in line \"" << line << "\"" << std::endl;
  }
  else if (nbActions > 1) {
    std::cerr << "more than one action in line \"" << line << "\"" << std::endl;
  }
  return (false);
}

Plazza::Action::Type
Parser::_getCommandType()
{
  Plazza::Action::Type  type;

  for (t_StringList::iterator it = _tokList.begin(); it != _tokList.end(); ++it)
    {
      type = Plazza::stringToAction(*it);
      if (type != Plazza::Action::Type::UNDEFINED)
        return (type);
    }
  return (Plazza::Action::Type::UNDEFINED);
}

bool
Parser::_parseActionsLine(std::string const &line, t_ActionStack &target)
{
  Plazza::Action::Type  type;
  int                   nbActions;

  // cut the command line at spaces and tabulations
  if (!_tokenizeCommand(line))
    return (false);

  // count the Action tokens such as EMAIL, IP or PHONE
  nbActions = this->_countActions();
  if (nbActions != 1)
    return (_invalidActionsNumberErrorHandler(nbActions, line));

  // get, then remove the command type
  type = this->_getCommandType();
  if (type == Plazza::Action::Type::UNDEFINED) // that can't happen, but hey
    throw(std::runtime_error("Parser::_parseActionsLine: UNDEFINED Action"));
  _tokList.erase(std::remove_if(_tokList.begin(), _tokList.end(), Plazza::isAnAction), _tokList.end());

  if (_tokList.empty())
    {
      std::cerr << "No file path in Command \"" << line << "\"" << std::endl;
      return (false);
    }

  // push every command into the command stack reference
  for (t_StringList::iterator it = _tokList.begin(); it != _tokList.end(); ++it)
    target.push_back(std::make_pair(std::string(*it), type));

  // remove everything from the token stack for the next call
  _tokList.clear();
  return (true);
}

bool
Parser::parse(std::string const &str, t_ActionStack &target)
{
  if (!_splitStringToList(str))
    return (false);

  for (t_StringList::iterator it = _cutList.begin(); it != _cutList.end(); ++it)
    {
      if (!_parseActionsLine((*it), target))
        return (false);
    }
  _cutList.clear();
  return (true);
}
