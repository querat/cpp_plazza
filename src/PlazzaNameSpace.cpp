//
// Plazza.cpp for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Sun Apr 17 16:11:56 2016 querat_g
// Last update Fri Apr 22 13:11:44 2016 querat_g
//

#include "PlazzaNameSpace.hh"

namespace Plazza
{
  const int POLL_TIMEOUT = DEF_POLL_TIMEOUT;

  namespace Action
  {
    namespace String
    {
      const std::string         EMAIL_ADDRESS("EMAIL_ADDRESS");
      const std::string         IP_ADDRESS("IP_ADDRESS");
      const std::string         PHONE_NUMBER("PHONE_NUMBER");

      Plazza::String::t_StringToActionMap const mapToEnum({
          std::make_pair(EMAIL_ADDRESS, Plazza::Action::Type::EMAIL_ADDRESS),
          std::make_pair(PHONE_NUMBER,  Plazza::Action::Type::PHONE_NUMBER ),
          std::make_pair(IP_ADDRESS,    Plazza::Action::Type::IP_ADDRESS   )
      }); // !Plazza::Action::String::mapToEnum
    }    // !Plazza::Action::String

    Plazza::Action::t_ActionToStringMap const mapToString({
        std::make_pair(Plazza::Action::Type::EMAIL_ADDRESS, String::EMAIL_ADDRESS),
        std::make_pair(Plazza::Action::Type::PHONE_NUMBER , String::PHONE_NUMBER ),
        std::make_pair(Plazza::Action::Type::IP_ADDRESS   , String::IP_ADDRESS   )
    }); // !Plazza::Action::mapToString
  }    // !Plazza::Action

  namespace Regex
  {
    std::regex                  EMAIL_ADDRESS(DEF_EMAIL_REGEX);
    std::regex                  IP_ADDRESS(DEF_IP_REGEX);
      std::regex                  PHONE_NUMBER(DEF_PHONE_REGEX);
      std::regex                  UNDEFINED(DEF_UNDEFINED_REGEX);

    t_ActionToRegexMap const    map({
        // TODO: write the true matching regexes instead of thoses debug ones
        std::make_pair(Plazza::Action::Type::EMAIL_ADDRESS, EMAIL_ADDRESS),
        std::make_pair(Plazza::Action::Type::IP_ADDRESS,    IP_ADDRESS),
        std::make_pair(Plazza::Action::Type::PHONE_NUMBER,  PHONE_NUMBER),
        std::make_pair(Plazza::Action::Type::UNDEFINED,  UNDEFINED)
    }); // !Plazza::Regex::map
  }    // !Plazza::Regex

  namespace Packet
  {
    uint32_t const MAGIC = DEF_MAGIC ;
  } // !Plazza::Packet
}  // !Plazza

bool
Plazza::isAnAction(std::string const &action)
{
  return (Plazza::Action::String::mapToEnum.count(action) ? true : false);
}

Plazza::Action::Type
Plazza::stringToAction(std::string const & str) {
  return ((Plazza::Action::String::mapToEnum.find(str))->second);
}

std::string
Plazza::makeFifoNameFromPid(pid_t pid, bool toMain) {
  if (toMain)
    return (std::string("fifo_in_pid_") + std::to_string(pid));
  return (std::string("fifo_out_pid_") + std::to_string(pid));
}

void
Plazza::printAction(Plazza::Action::Type act, bool toErr /* = 0*/)
{
  if (toErr)
    std::cerr << Plazza::Action::mapToString.find(act)->second;
  else
    std::cout << Plazza::Action::mapToString.find(act)->second;
}

bool
Plazza::pollFd(int fd) {

  struct pollfd myPoll =
    {
      .fd               = fd,
      .events           = POLLIN,
      .revents          = 0
    };
  int           status = 0;

  if ((status = poll(&myPoll, 1, 0)) < 0) {
    CERR("poll() failed on fd " << fd << ": " << strerror(errno));
    return (false);
  }

  return ((status && (myPoll.revents & POLLIN)) ? true : false);
}

std::ostream &
operator<<(std::ostream &os, Plazza::Action::Type act)
{
  Plazza::printAction(act);
  return (os);
}
