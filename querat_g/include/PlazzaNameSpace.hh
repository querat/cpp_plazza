//
// Plazza.hh for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Sun Apr 17 14:29:00 2016 querat_g
// Last update Tue Apr 19 14:26:31 2016 querat_g
//

#ifndef PLAZZANAMESPACE_HH
# define PLAZZANAMESPACE_HH

# include <iostream>
# include <iomanip>

# include <regex>
# include <map>
# include <list>

# include <exception>

# include <sys/types.h>

# define PLAZZA_USAGE           "plazza: usage: ./plazza nb_threads"

# define COMMAND_DELIMITERS     ";"
# define WORDS_DELIMITERS       "\t "

# define DEF_EMAIL_REGEX        "reg"
# define DEF_PHONE_REGEX        "reg"
# define DEF_IP_REGEX           "reg"

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
        EMAIL_ADDRESS,
        PHONE_NUMBER,
        IP_ADDRESS
      };
  } // !Plazza::Action

  namespace String {
    typedef std::map<std::string, Plazza::Action::Type> t_StringToActionMap;
    extern t_StringToActionMap const                    mapToEnum;
  } // !Plazza::String

  namespace Regex {
    typedef std::map<Plazza::Action::Type, std::regex>  t_ActionToRegexMap;
    extern t_ActionToRegexMap const                     map;
  } // !Plazza::Regex

} // !Plazza

// Pair that contains a filename and the action to execute on this file
typedef std::pair<std::string, Plazza::Action::Type>    t_FileActionPair;
// Stack that will be sent from the main process to the subProcesses
typedef std::deque<t_FileActionPair>                    t_ActionDeque;
// used by the parser to associate a string to a Plazza::Action::Type
typedef std::map<std::string, Plazza::Action::Type>     t_StringToTypeMap;

//
// Plazza::Packet::*
//
namespace Plazza
{
  namespace Packet
  {
    // we all need some 0xC0FFEE, even for named pipes
    extern uint32_t const MAGIC;

    // sent to fifo before the actual packet
    struct      Header
    {
      size_t    magic;
      size_t    size;
    }; // !struct Header

    struct        Raw
    {
      char      data[0];
    }; // !struct Raw
  }   // !Plazza::Packet
}    // !Plazza

//
// Function Prototypes
//
namespace Plazza
{
  bool                  isAnAction(std::string const &action);
  Plazza::Action::Type  stringToAction(std::string const & str);
  std::string           makeFifoNameFromPid(pid_t pid, bool toMain);
}

#endif  // PLAZZANAMESPACE_HH
