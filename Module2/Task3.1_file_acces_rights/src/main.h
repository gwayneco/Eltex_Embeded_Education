#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <ctype.h>

#define	S_R	(S_IRUSR|S_IRGRP|S_IROTH) /* Read by all.  */
#define	S_W	(S_IWUSR|S_IWGRP|S_IWOTH) /* Write by all.  */
#define	S_X	(S_IXUSR|S_IXGRP|S_IXOTH) /* Execute by all.  */

typedef struct
{
    int u;
    int g;
    int o;
    int r;
    int w;
    int x;
    int plus;
    int minus;
    int ravno;
    int octal;
} options;


void user_input(int *menu_choice);
void decimal_to_binary(int n);
char* decimalToOctal(int decimal);
void print_structure(options flags);
void printer_func(unsigned int result_in_int, char str[40]);
void mode_to_letters( int mode, char str[]);
void stat_printer(char filename[20], struct stat buf);