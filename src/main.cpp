//
// main.cpp for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Wed Apr 13 22:43:06 2016 querat_g
// Last update Thu Apr 21 17:58:11 2016 schmou_a
//

#include <stdexcept>
#include <iostream>
#include "Plazza.hh"
#include "dataCollector.hh"

// int     elFork(char **av)
// {
//   NamedPipe	pipe("myFifo");
//   int		child_pid = 0;

//   child_pid = fork();
//   if (child_pid == -1)
//     {
//       std::cerr << "fork has ded" << std::endl;
//       return (1);
//     }
//   if (child_pid) // parent
//     {
//       std::string a = pipe.readFrom();
//       a = pipe.readFrom();
//       std::cout << "reading " << a << std::endl;
//       wait(0);
//     }
//   else
//     {
//       pipe.writeTo(av[1]);
//     }

//   return (true);
// }

int     main(int ac, char **av)
{
  Plazza::Main  *plazza = nullptr;
  t_FileActionPair      fileInfo;
  std::regex            regex_phone(DEF_EMAIL_REGEX);
  fileInfo = std::make_pair("/home/schmou/cpp/cpp_plazza/FichierTests/ciphered_1_caesar_phone_mail", Plazza::Action::Type::PHONE_NUMBER);
  dataCollector         data(fileInfo, regex_phone);

  std::cout << data.extract_data();

  if (ac != 2)
    {
      std::cerr << PLAZZA_USAGE << std::endl;
      return (1);
    }

  try
  {
    plazza = new Plazza::Main(av[1]);
  }
  catch (std::invalid_argument const & exception) {
    std::cerr << exception.what() << std::endl;
    return (1);
  }

  // plazza->fork();

  return (0);
}
