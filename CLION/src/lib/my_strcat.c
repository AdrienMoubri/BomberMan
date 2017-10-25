/*
** my_strcat.c for my_strcat in /home/mathieu/Desktop/prog_c/Jour04/moubri_a
** 
** Made by MOUBRI Adrien
** Login   <moubri_a@etna-alternance.net>
** 
** Started on  Thu Mar 23 15:57:17 2017 MOUBRI Adrien
** Last update Thu Mar 23 16:54:19 2017 MOUBRI Adrien
*/

char	*my_strcat(char *dest, char *src)
{
  char	*adddest;

  adddest = dest;
  while (*dest)
    {
      dest += 1;
    }
  while (*src)
    {
      *dest = *src;
      dest += 1;
      src += 1;
    }
  return (adddest);
}
