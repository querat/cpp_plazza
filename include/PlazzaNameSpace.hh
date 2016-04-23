//
// Plazza.hh for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Sun Apr 17 14:29:00 2016 querat_g
// Last update Sat Apr 23 14:13:21 2016 querat_g
//

#ifndef PLAZZANAMESPACE_HH
# define PLAZZANAMESPACE_HH

# include <iostream>
# include <iomanip>

# include <thread>
# include <mutex>

# include <regex>

# include <vector>
# include <deque>
# include <map>
# include <list>

# include <exception>

# include <poll.h>
# include <sys/types.h>
# include <time.h>

# include "SafeDeque.hpp"

/*
** Colors
*/
# define RED                    "\033[1;31m"
# define GREEN                  "\033[1;32m"
# define YELLOW                 "\033[1;33m"
# define BROWN                  "\033[0;33m"
# define BLUE                   "\033[1;34m"
# define PINK                   "\033[1;35m"
# define CYAN                   "\033[1;36m"
# define WHITE                  "\033[0m"
# define WWHITE                 "\033[1;0m"

# define DEF_MAGIC              0xC0FFEE

# define PLAZZA_USAGE           "plazza: usage: ./plazza nb_threads"
# define PLAZZA_MAX_ACTIONS(x)  ((2 * x))

// Defined by the Makefile rule debug and debugre
# ifndef _DEBUG_
#  define DEBUG(...)            {}
# else
#  define DEBUG(...)            std::cerr << __VA_ARGS__ << std::endl;
# endif

#  define COUT(...)             std::cout << __VA_ARGS__ << std::endl;
#  define CERR(...)             std::cout << __VA_ARGS__ << std::endl;

# define FILENAME_SIZE          0x400

# define COMMAND_DELIMITERS     ";"
# define WORDS_DELIMITERS       "\t "

# define DEF_EMAIL_REGEX        "(?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*|\"(?:[\\x01-\\x08\\x0b\\x0c\\x0e-\\x1f\\x21\\x23-\\x5b\\x5d-\\x7f]|\\\\[\
\\x01-\\x09\\x0b\\x0c\\x0e-\\x7f])*\")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\\[(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0\
-5]|2[0-4][0-9]|[01]?[0-9][0-9]?|[a-z0-9-]*[a-z0-9]:(?:[\\x01-\\x08\\x0b\\x0c\\x0e-\\x1f\\x21-\\x5a\\x53-\\x7f]|\\\\[\\x01-\\x09\\x0b\\x0c\\x0e-\\x7f])+)\\])"
# define DEF_PHONE_REGEX        "(0[1-9][[:space:]]?)([[:digit:]]{2}[[:space:]]?){4}"
# define DEF_IP_REGEX           "(?:(?:0|1[\\d]{0,2}|2(?:[0-4]\\d?|5[0-5]?|[6-9])?|[3-9]\\d?)\\.){3}(?:0|1[\\d]{0,2}|2(?:[0-4]\\d?|5[0-5]?|[6-9])?|[3-9]\\d?)"
# define DEF_UNDEFINED_REGEX    ""
# define DEF_POLL_TIMEOUT       10
# define EOF_CHAR               4

//
// !! All variables declared here as extern MUST be declared in Plazza.cpp !!
//

namespace Plazza
{
  extern const int      POLL_TIMEOUT;

  namespace Action
  {
    enum Type
      {
        UNDEFINED = 0,
        EMAIL_ADDRESS,
        PHONE_NUMBER,
        IP_ADDRESS
      };
    typedef std::map<Plazza::Action::Type, std::string> t_ActionToStringMap;
    extern t_ActionToStringMap const                    mapToString;
  } // !Plazza::Action

  namespace String {
    typedef std::map<std::string, Plazza::Action::Type> t_StringToActionMap;
    extern t_StringToActionMap const                    mapToEnum;
  } // !Plazza::String

  namespace Regex {
    typedef std::map<Plazza::Action::Type, std::regex>  t_ActionToRegexMap;
    extern t_ActionToRegexMap const                     map;
  } // !Plazza::Regex
}  // !Plazza

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

    // All the stuff defined here is meant to
    namespace Raw
    {
      struct      Action : public Plazza::Packet::Header
      {
        Plazza::Action::Type    type;
        char                    fileName[FILENAME_SIZE];
      };// !Plazza::Packet::Raw::Action
      // Sent from the child to the main process
      struct      Answer : public Plazza::Packet::Header
      {
        char                    data[0];
      };// !Plazza::Packet::Raw::Answer
    }  // !Plazza::Packet::Raw
  }   // !Plazza::Packet
}    // !Plazza

  //
 // Functions Prototypes
//
namespace Plazza
{
  bool                  isAnAction(std::string const &action) ;
  Plazza::Action::Type  stringToAction(std::string const & str);
  std::string           makeFifoNameFromPid(pid_t pid, bool toMain);
  void                  printAction(Plazza::Action::Type act, bool toErr = false);
  bool                  pollFd(int fd);
}

typedef std::deque<std::string>                                 t_AnswerDeque;
typedef SafeDeque<std::pair<std::string, Plazza::Action::Type>> t_SafeActionDeque;
typedef SafeDeque<std::string>                                  t_SafeAnswerDeque;
typedef std::vector<std::thread>                                t_ThreadVector;

std::ostream &          operator<<(std::ostream &os, Plazza::Action::Type act);

#endif  // PLAZZANAMESPACE_HH
