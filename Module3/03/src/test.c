// #include <stdio.h>
// #include <fcntl.h>
// #include <unistd.h>
// #include <string.h>

// int main() {
//     int fd;
//     int sz;
//     if ((fd = open("foo.txt", O_WRONLY | O_CREAT, 0644))) == -1) {
//         printf("open error\n");
//     }
//     //     printf("open error\n");
//     // }
//     char* str = "test";
//     sz = write(fd, "hello geeks\n", strlen("hello geeks\n"));
//     close(fd); 
//     return 0;
// }

// #include<stdio.h> 
// #include <fcntl.h> 
// main() 
// { 
// int sz; 
 
// int fd = open("foo.txt", O_WRONLY | O_CREAT , 0644); 
// if (fd < 0) 
// { 
//     perror("r1"); 
//     exit(1); 
// } 
 
// sz = write(fd, "hello geeks\n", strlen("hello geeks\n")); 

 
// close(fd); 
// } 