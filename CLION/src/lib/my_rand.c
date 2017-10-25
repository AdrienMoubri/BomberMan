/*
** my_rand.c for La Roulette in /home/mathieu/Desktop/prog_c/La Roulette/moubri_a
** 
** Made by MOUBRI Adrien
** Login   <moubri_a@etna-alternance.net>
** 
** Started on  Sat Mar 25 09:57:35 2017 MOUBRI Adrien
** Last update Wed Apr 12 18:44:35 2017 MOUBRI Adrien
*/

#include <stdlib.h>
#include <time.h>

int	my_rand()
{
  int	random;

  random = (rand() % 100);
  return (random);
}
