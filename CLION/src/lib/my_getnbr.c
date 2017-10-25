/*
** my_getnbr2.c for my_getnbr in /home/mathieu/Desktop/prog_c/Jour05/moubri_a
** 
** Made by MOUBRI Adrien
** Login   <moubri_a@etna-alternance.net>
** 
** Started on  Fri Mar 24 14:28:51 2017 MOUBRI Adrien
** Last update Wed Apr 12 19:47:42 2017 MOUBRI Adrien
*/

int	my_getnbr(char *str)
{
  int	i;
  int	neg;
  int	res;

  res = 0;
  i = 0;
  neg = 1;
  while (str[i] == '+' || str[i] == '-')
    {
      if (str[i] == '-')
	{
	  neg *= -1;
	}
      i += 1;
    }
  while (str[i] >= '0' && str[i] <= '9')
    {
      res *= 10;
      res += str[i] - '0';
      i += 1;
    }
  return (neg * res);
}
