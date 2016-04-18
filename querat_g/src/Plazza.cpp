//
// Plazza.cpp for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Sun Apr 17 16:11:56 2016 querat_g
// Last update Mon Apr 18 10:46:03 2016 querat_g
//

#include "Plazza.hh"

namespace Plazza
{
  namespace Action
  {
    t_StringToActionMap const   String({
      std::make_pair("EMAIL_ADDRESS", Plazza::Action::Type::EMAIL_ADDRESS),
      std::make_pair("PHONE_NUMBER",  Plazza::Action::Type::PHONE_NUMBER ),
      std::make_pair("IP_ADDRESS",    Plazza::Action::Type::IP_ADDRESS   )
    }); // !String
  }    // !Plazza::Action

  t_ActionToRegexMap const      Regex({
    // TODO: write the true matching regexes instead of thoses debug ones
    std::make_pair(Plazza::Action::Type::EMAIL_ADDRESS, std::regex("EMAIL")),
    std::make_pair(Plazza::Action::Type::IP_ADDRESS,    std::regex("IP"   )),
    std::make_pair(Plazza::Action::Type::PHONE_NUMBER,  std::regex("PHONE"))
  }); // !Plazza::Regex
}    // !Plazza

bool
Plazza::isAnAction(std::string const &action){
  return (Plazza::Action::String.count(action) ? true : false);
}

Plazza::Action::Type
Plazza::stringToAction(std::string const & str){
  return ((Plazza::Action::String.find(str))->second);

}
