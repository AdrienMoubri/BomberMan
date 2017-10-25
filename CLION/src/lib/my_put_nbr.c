/*
** my_put_nbr.c for my_put_nbr in /home/mathieu/Desktop/prog_c/Jour05
** 
** Made by MOUBRI Adrien
** Login   <moubri_a@etna-alternance.net>
** 
** Started on  Fri Mar 24 09:22:29 2017 MOUBRI Adrien
** Last update Fri May 12 09:36:15 2017 MOUBRI Adrien
*/

void	my_putchar(char c);

int	my_nb_len(int i)
{
  int	len;

  len = 1;
  while ((i < 10) ^ (i > -10))
    {
      len += 1;
      i = i / 10;
    }
  return (len);
}

void	my_putmin()
{
  my_putchar('2');
  my_putchar('1');
  my_putchar('4');
  my_putchar('7');
  my_putchar('4');
  my_putchar('8');
  my_putchar('3');
  my_putchar('6');
  my_putchar('4');
  my_putchar('8');
}

int	my_pow(int n, int p)
{
  int	i;
  int	puiss;

  i = 1;
  puiss = n;
  while (i < p)
    {
      n *= puiss;
      i += 1;
    }
  return (n);
}

void	my_put_nbr(int n)
{
  int	d;
  int	i;
  int	sous;

  d = my_nb_len(n) - 1;
  i = d;
  if (n < 0)
    {
      my_putchar('-');
      n *= - 1;
    }
  if (n == -2147483648)
    my_putmin();
  else
    {
    if (n >= 10)
	while (i > 0)
	  {
	    sous = n / my_pow(10, i);
	    my_putchar(sous + '0');
	    n -= sous * my_pow(10, i);
	    i -= 1;
	  }
    my_putchar(n + '0');
    }
}
