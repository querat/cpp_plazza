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

int	main(int ac, char **av)
{
  int	fdin;
  int	fdout;
  char	buff[500001];

  fdin = open(av[1], O_RDONLY);
  fdout = open("ciphered", O_RDWR);

  memset(buff, '\0', 500000);
  read(fdin, buff, 500000);
  for(int i = 0; i < strlen(buff); i++)
    {
      
      buff[i] = buff[i] + 0xe2;
    }
  write(fdout, buff, strlen(buff));
  close(fdin);
  close(fdout);
}
