// C Program to test write system call
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
  int sz;

  int fd = open("RWtest.txt", O_WRONLY);
  if (fd < 0)
    {
      perror("r1");
      exit(1);
    }

  sz = write(fd, "Bro, you rewrote me\n", strlen("Bro, you rewrote me\n"));

  printf("called write(% d, \"Bro, you rewrote me\\n\", %d)." "it returned %d\n", fd, strlen("Bro, you rewrote me\n"), sz);

  close(fd);
}
