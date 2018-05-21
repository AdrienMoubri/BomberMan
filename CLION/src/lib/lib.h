
#ifndef		_LIB_H_
#define		_LIB_H_

int			my_strcmp(char *str1, char *str2);
int			my_rand();
void		my_putstr_color(const char *color,const char *str);
void		my_put_nbr(int i);
int			my_getnbr(char *str);
int			my_is_odd(int i);
void		my_putstr(char *str);
char		*my_strdup(char *str);
char		*my_strcat(char *str1, char *str2);
char		*read_line();
char		*my_strupcase(char *str);

#endif //   __LIB_H__