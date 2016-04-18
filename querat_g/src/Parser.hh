//
// Parser.hh for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Sun Apr 17 14:21:53 2016 querat_g
// Last update Mon Apr 18 13:41:57 2016 querat_g
//

#ifndef PARSER_HH
# define PARSER_HH

# include <cstring>

# include <iostream>
# include <string>

# include <utility>
# include <stack>
# include <map>
# include <list>

# include <algorithm>

# include "PlazzaNameSpace.hh"

typedef std::list<std::string>  t_StringList;

class Parser
{
public:
  Parser();
  ~Parser();

private:
  t_StringList  _cutList;
  t_StringList  _tokList;

private:
  bool          _splitStringToList(std::string const & str);
  bool          _parseActionsLine(std::string const & line, t_ActionStack & target);
  bool          _tokenizeCommand(std::string const & line);
  int           _countActions() const;
  bool          _invalidActionsNumberErrorHandler(int nbActions,
                                                  std::string const & line);
  Plazza::Action::Type  _getCommandType();

public:
  bool          parse(std::string const & str, t_ActionStack &target);
};

#endif  // PARSER_HH
