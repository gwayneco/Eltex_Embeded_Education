#include "main.h"


void init_structure(options *flags) {
    flags->g = 0;
    flags->minus = 0;
    flags->o = 0;
    flags->plus = 0;
    flags->r = 0;
    flags->ravno = 0;
    flags->u = 0;
    flags->w = 0;
    flags->x = 0;
}


void 


void print_structure(options *flags) {
    printf("flags->g = %d\n", flags->g);
    printf("flags->minus = %d\n", flags->minus);
    printf("flags->o = %d\n", flags->o);
    printf("flags->plus = %d\n", flags->plus);
    printf("flags->r = %d\n", flags->r);
    printf("flags->ravno = %d\n", flags->ravno);
    printf("flags->g = %d\n", flags->u);
    printf("flags->w = %d\n", flags->w);
    printf("flags->x = %d\n", flags->x);
}


void mode_to_letters( int mode, char str[] )
{
    strcpy( str, "---------" );           /* default=no perms */

    if ( mode & S_IRUSR ) str[0] = 'r';    /* 3 bits for user  */
    if ( mode & S_IWUSR ) str[1] = 'w';
    if ( mode & S_IXUSR ) str[2] = 'x';

    if ( mode & S_IRGRP ) str[3] = 'r';    /* 3 bits for group */
    if ( mode & S_IWGRP ) str[4] = 'w';
    if ( mode & S_IXGRP ) str[5] = 'x';

    if ( mode & S_IROTH ) str[6] = 'r';    /* 3 bits for other */
    if ( mode & S_IWOTH ) str[7] = 'w';
    if ( mode & S_IXOTH ) str[8] = 'x';
}


void stat_printer(char filename[20], struct stat buf) {
    char str[40] = "";
    if ( stat(filename, &buf) == -1 )		/* cannot stat	 */
    		  fprintf(stderr, "%s\n", strerror(errno));
    mode_t rights_bits = buf.st_mode;  
    mode_to_letters(buf.st_mode, str);
    printf("bytes: %u\n",rights_bits);
    printf("string: %s\n",str);
}

void user_input(char filename[20], int *menu_choice) {
    printf("Введите имя файла: ");
    scanf("%s", filename);
    printf("1. Простмотр прав доступа файла.\n2. Изменение прав доступа файла.\n");
    scanf("%d", menu_choice);
}


void parsing_string(char *ptr, options *flags) {
    printf("prt: %c\n", *ptr);
    switch (*ptr)
    {
    case 'u':
        flags->u = 1;
        break;
    case 'g':
        flags->g = 1;
        break;
    case 'o':
        flags->o = 1;
        break;
    case 'r':
        flags->r = 1;
        break;
    case 'w':
        flags->w = 1;
        break;
    case 'x':
        flags->x = 1;
        break;
    case '+':
        flags->plus = 1;
        break;
    case '-':
        flags->minus = 1;
        break;
    case '=':
        flags->ravno = 1;
        break;
    default:
        break;
    }
}

void changing_rights(struct stat buf, options *flags) {
    mode_t rights_bits = buf.st_mode & 0777;
    char input_string[20] = {0};
    char *ptr = input_string;
    printf("Введите права доступа: ");
    scanf("%s", input_string);
    while (*ptr != '\0') {
        parsing_string(ptr, flags);
        // printf("%c\n", *ptr);
        ptr++;
    }
    printf("u: %d\n", flags->u);
}


void main_menu() {
    options flags;
    init_structure(&flags);
    char filename[20] = "";
    struct stat buf;
    int menu_choice = 0;
    user_input(filename, &menu_choice);
    if (menu_choice == 1) {
        stat_printer(filename, buf);
    } else if (menu_choice == 2) {
        changing_rights(buf, &flags);
        print_structure(&flags);
    }
}


int main() {
    main_menu();
    return 0;
}


// regmatch_t pmatch[strlen(source_line)];
// int len = pmatch[0].rm_eo - pmatch[0].rm_so;
// 			memcpy(temp, source_line + pmatch[0].rm_so, len);
		// if ((res = regexec(&regex_expression, source_line, len, pmatch, 0)) == 0) {
		// 	result = source_line;


// #include <stdio.h>
// #include <sys/stat.h>
// #include <string.h>
// #include <errno.h>

// int main(int argc, char **argv)
// {
//   struct stat  file_stat;

//   while (argc-- > 1)
//     {
//       if (stat(argv[argc], &file_stat) == -1)
//         fprintf(stderr, "%s\n", strerror(errno));
//       else
//         {
//           fprintf(stdout, "Links\tUid\tGid\tSize\tName\n");
//           fprintf(stdout, "%u\t%u\t%u\t%u\t%s\n", file_stat.st_nlink,
//                   file_stat.st_uid, file_stat.st_gid, file_stat.st_size,
//                   argv[argc]);
//           printf("%s\n", argv[argc]);
//         }
//     }
//   return 0;
// }