/*
** caesar.c for  in /home/schmou/tmp/chiffrement
** 
** Made by schmou_a
** Login   <schmou@epitech.net>
** 
** Started on  Wed Apr 13 15:19:14 2016 schmou_a
** Last update Wed Apr 13 17:44:13 2016 schmou_a
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char	*xorify(char *str, short key)
{
  int	i = 0;
  int	len = strlen(str);
  char	*ret;

  if ((ret = strdup(str)) == NULL)
    return (NULL);
  while (i < len)
    {
      ret[i] = (ret[i] ^ key);
      i++;
    }
  return (ret);
}

char	*bruteforce_xorify(char *str, char *to_find)
{
  short	key = 0b000000000000000;
  char	*ret = NULL;

  while (key < 0b111111111111111)
    {
      ret = xorify(str, key);
      if (strcmp(ret, to_find) == 0)
	return (ret);
      key += 0b000000000000001;
    }
  return (NULL);
}

int	main(int ac, char **av)
{
  short key = 0b010000001001011;

  if (ac != 2)
    return (printf("ENCULÉ\n"), 1);
  printf("=========\n   XOR\n=========\n");
  printf("      Chaîne de départ :\n\n%s\n\n", av[1]);
  printf("      Une fois encrypté :\n\n%s\n\n", xorify(av[1], key));
  printf("      Et décrypté :\n\n%s\n\n", xorify(xorify(av[1], key), key));
  printf("==============================\n  Maintenant, on bruteforce :\n==============================\n\n%s\n\n",
	 bruteforce_xorify(xorify(av[1], key), av[1]));
  return (0);
}
