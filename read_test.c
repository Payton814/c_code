// C Program to illustrate read system call
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  int n;
  printf("How many Bytes would you like to read?\n");
  scanf("%d", &n);

  int fd, sz;
  char* c = (char*)calloc(100, sizeof(char));// calloc is a function that allocates a certain amount of memory
  
  fd = open("RWtest.txt", O_RDONLY | O_CREAT);
  if (fd < 0)
    {
      perror("r1");
      exit(1);
    }

  sz = read(fd, c, n);
  printf("called read(% d, c, %d). returned that %d bytes were read.\n", fd, n,  sz);
  c[sz] = '\0';
  printf("Those bytes are as follows: % s\n", c);

  return 0;
}
