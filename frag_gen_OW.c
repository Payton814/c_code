// manipulate the contents of the file
//
// This code was originally written to test out
// the TURF fagment generator firmware
//
//
//
//****************************************************
// To-Do/Notes:
// 1. get rid of prompts, hardcode files in
// 2. event_size_out needs 32 bits/ 4 Bytes
// 3. event_out needs 64 bits/ 8 Bytes
// 4.
//
//
//
//
//
//***************************************************

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <curses.h>

#define NUMBER_OF_QWORDS 2040

int main()
{
  // We know we are going to open ./xillybus_event_out, ./xillybus_event_size_out, and ./xillybus_mmreq
  // we only need to write to event_out, and event_size_out, but mmreq needs to be open for the request to go through
  int n_files = 3;
  int i;
  int j;
  int close_break = 0;
  //printf("How many files would you like to manipulate?\n");
  //scanf("%d", &n_files);
  char file_name[n_files][100];
  int file[n_files + 1];
  //int file_WR[n_files];
  // int file_RD[n_files];
  char* c = (char*)calloc(100, sizeof(char));
  // Remember 1 Byte is 2 hex numbers
  uint32_t addr = 0;
  //uint32_t d_event_size_out = 0x12345678;
  uint64_t d_event_out = 0x112233445566778b;
  uint32_t ev_length = NUMBER_OF_QWORDS*sizeof(d_event_out);
  uint32_t tag = ((addr&0xFFF << 20))|(ev_length&0xFFFFF);

  printf("tag = %4.4x\n", tag);
  uint64_t buf[NUMBER_OF_QWORDS];
  for (int i=0;i<NUMBER_OF_QWORDS;i++) buf[i] = d_event_out + i;
 
  // printf("youre here\n");

  file[0] = open("/dev/xillybus_mmreq", O_WRONLY);
  file[1] = open("/dev/xillybus_event_size_out", O_WRONLY); // data size is 32 bits
  file[2] = open("/dev/xillybus_event_out", O_WRONLY); // data size is 64 bits
 

  // Simply checks if something went wring trying to open the files
  if(file[0] < 0 || file[1] < 0 || file[2] < 0)
    {
      // print the type of error that in the code
      printf("Error Number % d\n", errno);
      perror("Program");
    }

write(file[1], &tag, sizeof(tag));
write(file[2], &buf, NUMBER_OF_QWORDS*sizeof(d_event_out));
write(STDOUT_FILENO, &buf, NUMBER_OF_QWORDS*sizeof(d_event_out));

//printf("Enter '1' to close all the files\n");

while (1)
  {
    scanf("%d", &close_break);
    if(close_break == 1)
      {
	break;
      }
  }
 
 
for (j = 0; j < n_files + 1; j++)
  {
    close(file[j]);
  }
 

return 0;
}
