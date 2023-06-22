//This code takes a given file and will use the c open(), write(), and read() commands
// to acess and manipulate the contents of the file

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  char file_name[100];
  int file;
  int file_WR;
  int file_RD;
  char* c = (char*)calloc(100, sizeof(char));
  char message[100];

  printf("What file would you like to manipulate?\n");
  scanf("%s", file_name);

  printf("What message would you like to write?\n");
  scanf("%s", message); // You cannot write a message with spaces
  printf(message);
  file = open(file_name, O_CREAT, 0644); // The 0644 gives the user permission to read and write to the file that is being created
  close(file);
  file = open(file_name, O_RDWR);
  if (file < 0)
    {
      // print the type of error thats in the code
      printf("Error Number % d\n", errno);

      perror("Program");
    }

  file_WR = write(file, message, strlen(message));
  close(file);

  file = open(file_name, O_RDWR);
  if (file < 0)
    {
      printf("Error Number % d\n", errno);
      perror("Program");
    }

  file_RD = read(file, c, strlen(message));
  
  //printf("% s\n", c);

  close(file);
  

  return 0;
}
