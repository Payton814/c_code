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
  int n_files;
  printf("How many files would you like to manipulate?\n");
  scanf("%d", &n_files);
  char file_name[n_files][100];
  int file[n_files];
  int file_WR[n_files];
  int file_RD[n_files];
  char* c = (char*)calloc(100, sizeof(char));
  char message[100];
  int close_break;
  printf("youre here\n");
  for ( int i = 0; i < n_files; i++)
    {
      printf("What file would you like to manipulate?\n");
      scanf("%s", file_name[i]);

      printf("What message would you like to write in % s\n", file_name);
      scanf("%s", message); // You cannot write a message with spaces
      printf(message);
      file[i] = open(file_name[i], O_CREAT, 0644); // The 0644 gives the user permission to read and write to the file that is being created
      close(file[i]);
      file[i] = open(file_name[i], O_RDWR);
      if (file[i] < 0)
	{
	  // print the type of error thats in the code
	  printf("Error Number % d\n", errno);

	  perror("Program");
	}

      file_WR[i] = write(file[i], message, strlen(message));
    }

  while (1)
    {
      printf("type '1' if you would like to close all the files\n");
	scanf("%d", &close_break);
      if (close_break == 1)
	{
	  for (int j = 0; j < n_files; j++)
	    {
	      close(file[j]);
	    }
	  break;
	}
    }

      /**  file = open(file_name, O_RDWR);
  if (file < 0)
    {
      printf("Error Number % d\n", errno);
      perror("Program");
    }

    file_RD = read(file, c, strlen(message));**/
  
  //printf("% s\n", c);

      // close(file);
  

  return 0;
}
