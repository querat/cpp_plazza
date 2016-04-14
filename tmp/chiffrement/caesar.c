/*
** caesar.c for  in /home/schmou/tmp/chiffrement
** 
** Made by schmou_a
** Login   <schmou@epitech.net>
** 
** Started on  Wed Apr 13 15:19:14 2016 schmou_a
** Last update Wed Apr 13 17:13:42 2016 schmou_a
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char	*encrypt(char *str, short key)
{
  int	i = 0;
  int	len = strlen(str);
  char	*ret;

  if ((ret = strdup(str)) == NULL)
    return (NULL);
  while (i < len)
    {
      ret[i] = (ret[i] + key); //% sizeof(short);
      i++;
    }
  return (ret);
}

char	*decrypt(char *str, short key)
{
  int	i = 0;
  int	len = strlen(str);
  char	*ret;

  if ((ret = strdup(str)) == NULL)
    return (NULL);
  while (i < len)
    {
      ret[i] = (ret[i] - key); // % sizeof(short);
      i++;
    }
  return (ret);
}

int	main(int ac, char **av)
{
  short key = 0b00100000010010111;

  if (ac != 2)
    return (printf("ENCULÉ\n"), 1);
  printf("=========\n  CESAR\n=========\n");
  printf("      Chaîne de départ :\n\n%s\n\n", av[1]);
  printf("      Une fois encrypté :\n\n-%s\n\n", encrypt(av[1], key));
  printf("      Et décrypté :\n\n%s\n\n", decrypt(encrypt(av[1], key), key));
  return (0);
}
