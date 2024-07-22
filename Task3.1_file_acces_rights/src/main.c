#include "main.h"


void mode_to_letters( int mode, char str[] )
{
    strcpy( str, "----------" );           /* default=no perms */

    if ( S_ISDIR(mode) )  str[0] = 'd';    /* directory?       */
    if ( S_ISCHR(mode) )  str[0] = 'c';    /* char devices     */
    if ( S_ISBLK(mode) )  str[0] = 'b';    /* block device     */

    if ( mode & S_IRUSR ) str[1] = 'r';    /* 3 bits for user  */
    if ( mode & S_IWUSR ) str[2] = 'w';
    if ( mode & S_IXUSR ) str[3] = 'x';

    if ( mode & S_IRGRP ) str[4] = 'r';    /* 3 bits for group */
    if ( mode & S_IWGRP ) str[5] = 'w';
    if ( mode & S_IXGRP ) str[6] = 'x';

    if ( mode & S_IROTH ) str[7] = 'r';    /* 3 bits for other */
    if ( mode & S_IWOTH ) str[8] = 'w';
    if ( mode & S_IXOTH ) str[9] = 'x';
}


void user_input(char filename[20], int *menu_choice) {
    printf("Введите имя файла: ");
    scanf("%s", filename);
    printf("1. Простмотр прав доступа файла.\n2. Изменение прав доступа файла.\n");
    scanf("%d", menu_choice);
}


void main_menu() {
    char filename[20] = "";
    struct stat buf;
    char str[40] = "";
    int menu_choice = 0;
    user_input(filename, &menu_choice);
    if (menu_choice == 1) {
         if ( stat(filename, &buf) == -1 )		/* cannot stat	 */
		  fprintf(stderr, "%s\n", strerror(errno));
    mode_t size = buf.st_mode;  
    mode_to_letters(buf.st_mode, str);
    printf("bytes: %u\n",size);
    printf("string: %s\n",str);
    }
}


int main() {
    main_menu();

    return 0;
}






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