/*
** my_putchar.c for my_putchar in /home/mathieu/Desktop/prog_c/my_putchar/moubri_a/my_putchar
** 
** Made by MOUBRI Adrien
** Login   <moubri_a@etna-alternance.net>
** 
** Started on  Mon Mar 20 12:11:31 2017 MOUBRI Adrien
** Last update Mon Mar 20 12:30:50 2017 MOUBRI Adrien
*/

#include <unistd.h>

void	my_putchar(char c)
{
  write(1, &c, 1);
}
