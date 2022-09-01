#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[])
{
  char path_name[100];
  ssize_t input, output, output2;
  int source, dest1, dest2;
  char buffer[1024];
  char* sourceFileName, destination1, destination2;

  if(argc != 4)
  {
    //print proper usage of the executable and exit the program
    printf("Proper Usage: [executable] [source file] [destination1] [destination2]\n");
    exit(-1);
  }

  //open file and check if it was successful
  source = open(argv[1], O_RDONLY);
  if(source == -1) {
    perror("open");
    exit(1);
  }
  //open file and check if it was successful
  dest1 = open(argv[2], O_WRONLY | O_CREAT, 0644);
  if(dest1 == -1)
  {
    perror("open");
    exit(2);
  }
  //open file and check if it was successful
  dest2 = open(argv[3], O_WRONLY | O_CREAT, 0644);
  if(dest2 == -1)
  {
    perror("open");
    exit(3);
  }

  //loop to read the source file and write the 2 copies
  while((input = read(source, &buffer, 1024)) > 0 )
  {
    output = write (dest1, &buffer, (ssize_t) input);
    if(output != input)
    {
      perror("write");
      exit(1);
    }
    output2 = write(dest2, &buffer, (ssize_t) input);
    if(output2 != input)
    {
      perror("write");
      exit(1);
    }
  }

  close(dest1);
  close(dest2);
  close(source);
  return 0;
}
