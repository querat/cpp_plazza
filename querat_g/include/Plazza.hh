//
// Plazza.hh for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Sun Apr 17 14:29:00 2016 querat_g
// Last update Sun Apr 17 20:26:41 2016 querat_g
//

#ifndef PLAZZA_HH
# define PLAZZA_HH

# include <regex>
# include <map>
# include <list>

# include <exception>

# define COMMAND_DELIMITERS     ";"
# define WORDS_DELIMITERS       "\t "

# define COMMAND_REGEX          "(\\s|^)(A-Z)+(\\s|$)"

//
// !! All variables declared here as extern MUST be declared in Plazza.cpp !!
//

namespace Plazza
{
  namespace Action
  {
    enum Type
      {
        UNDEFINED = 0,
        EMAIL,
        PHONE,
        IP
      };
  }

  typedef std::map<std::string, Plazza::Action::Type>   t_StringToActionMap;
  typedef std::map<Plazza::Action::Type, std::regex>    t_ActionToRegexMap;

  extern t_StringToActionMap const      String;
  extern t_ActionToRegexMap  const      Regex;
}

// Pair that contains a filename and the action to execute on this file
typedef std::pair<std::string, Plazza::Action::Type>    t_FileActionPair;

// Stack that will be sent from the main process to the subProcesses
typedef std::deque<t_FileActionPair>                    t_ActionStack;

typedef std::map<std::string, Plazza::Action::Type>     t_StringToTypeMap;

//
// Function Prototypes
//
namespace Plazza
{
  bool                  isAnAction(std::string const &action);
  Plazza::Action::Type  stringToAction(std::string const & str);
}

#endif  // PLAZZA_HH
