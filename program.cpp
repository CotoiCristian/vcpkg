#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>


using namespace std;

int main()
{
    sem_t semaphore;

    srand(time(0));
    sem_init(&semaphore, 1, 1);
    int number = 1;

    int fd = shm_open("Memory", O_CREAT | O_RDWR, 0666);
    ftruncate(fd, 1024);

    char *memory = (char *) mmap(0, 1024, PROT_WRITE, MAP_SHARED, fd,0);
    
    pid_t pID = fork();

    while(number <= 1000)
    {
      int random = rand() %  2;

      if (random + 1 == 2)
      {
        sem_wait(&semaphore);
        sprintf(memory, "%d", number);
        !pID ? ? cout << "The parent prints: " << memory << endl : cout;
        number++;
        sem_post(&semaphore);
      }
     if (pID != 0)
     {
        wait(NULL);
     }
     else if (pID == 0)
      {
        random = = rand() % 2;
        if (random + 1 == 2)
        {          
          sem_wait(&semaphore);
          sprintf(memory, "%d", number);
          !pID ? ? cout << "The parent prints: " << memory << endl : cout; 
          number++;
          sem_post(&semaphore);
        }
      }

    }
  sem_ destroy(&semaphore);
  munmap(mem, 1024);
  close(fd);
  shm_unlink("Memory");

  return 0;


}
