/*
** cipher.c for  in /home/schmou/cpp
**
** Made by schmou_a
** Login   <schmou@epitech.net>
**
** Started on  Tue Apr 19 14:35:53 2016 schmou_a
** Last update Thu Apr 21 17:52:22 2016 schmou_a
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	disp_usage()
{
  dprintf(STDERR_FILENO,
	  "usage: ./cipher path_to_file encryption_type(xor | caesar) key(1 byte for caesar, 2 for xor)\n");
  return (1);
}

int	main(int ac, char **av)
{
  int	fdin;
  char	buff[500001];
  int	key;
  int	len;

  if (ac != 4)
    return (disp_usage());
  if ((fdin = open(av[1], O_RDONLY)) == -1)
    {
      dprintf(STDERR_FILENO,"%m\n");
      return (-1);
    }
  memset(buff, '\0', 500000);
  if ((read(fdin, buff, 500000)) < 0)
    {
      dprintf(STDERR_FILENO, "%m\n");
      return (-1);
    }
  close(fdin);
  key = atoi(av[3]);
  len = strlen(buff);
  if (!strcmp(av[2], "xor"))
    {
      for (int i = 0; i < len; i++)
	{
	  buff[i] = buff[i] ^ (key >> 8);
	  buff[i + 1] = buff[i + 1] ^ key;
	  i++;
	}
    }
  else if (!strcmp(av[2], "caesar"))
    {
      for (int i = 0; i < len; i++)
	buff[i] += key;
    }
  else
    return (disp_usage());
  write(1, buff, len);
  return (0);
}
