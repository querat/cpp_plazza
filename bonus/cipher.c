/*
** cipher.c for  in /home/schmou/cpp
**
** Made by schmou_a
** Login   <schmou@epitech.net>
**
** Started on  Tue Apr 19 14:35:53 2016 schmou_a
** Last update Thu Apr 21 16:46:01 2016 schmou_a
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int	main(int ac, char **av)
{
  int	fdin;
  int	fdout;
  char	buff[500001];

  if ((fdin = open(av[1], O_RDONLY)) == -1)
    {
      dprintf(STDERR_FILENO,"%m\n");
      return (-1);
    }
  if ((fdout = open("ciphered", O_RDWR)) == -1)
    {
      dprintf(STDERR_FILENO, "%m\n");
      return (-1);
    }
  memset(buff, '\0', 500000);
  if ((read(fdin, buff, 500000)) < 0)
    {
      dprintf(STDERR_FILENO, "%m\n");
      return (-1);
    }
  for(int i = 0; i < strlen(buff); i++)
      buff[i] = buff[i] + 0xe2;
  write(fdout, buff, strlen(buff));
  close(fdin);
  close(fdout);
}
