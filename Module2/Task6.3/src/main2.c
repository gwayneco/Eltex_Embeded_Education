#include "main.h"

void print();

int main() {
    void *handle;
    char *error;

      handle = dlopen("./libtest.so", RTLD_LAZY);
      if (!handle) {
        fputs(dlerror(), stderr);
        exit(1);
      }

      void (*test)();

      test = dlsym(handle, "print");
       if ((error = dlerror()) != NULL) {
        printf("\n\ngdfgf\n");
    fprintf(stderr, "%s\n", error);
    exit(EXIT_FAILURE);
  }
  test();
  dlclose(handle);
  handle = dlopen("./lib/libsub.so", RTLD_LAZY);
      if (!handle) {
        fputs(dlerror(), stderr);
        exit(1);
      }
      int (*test2)(int firest, int second);
      test2 = dlsym(handle, "sub");
      printf("hi: %d\n", test2(1,5));
      // printf("%d\n\n", (*test)(2,5));

  return EXIT_SUCCESS;
}