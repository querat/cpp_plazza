#include <iostream>
#include <regex>
#include <string>

int	main(void)
{
  std::string input;

  std::regex	integer("(\\+|-)?[[0-9]]+");
  while (true)
    {
      std::cout << "Give me an integer !" << std::endl;
      std::cin >> input;
      if (!std::cin)
	break;
      if (input == "q")
	break;
      if (regex_match(input, integer))
	std::cout << "integer" << std::endl;
      else
	std::cout << "Invalid input" << std::endl;
    }
}
