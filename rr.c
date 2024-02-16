#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

typedef uint32_t u32;
typedef int32_t i32;

struct process
{
  u32 pid;
  u32 arrival_time;
  u32 burst_time;

  TAILQ_ENTRY(process) pointers;

  /* Additional fields here */
  u32 remaining_time;
  u32 remaining_cycle_time;
  u32 start_exec_time;
  u32 waiting_time;
  u32 response_time;
  /* End of "Additional fields here" */
};

TAILQ_HEAD(process_list, process);

u32 next_int(const char **data, const char *data_end)
{
  u32 current = 0;
  bool started = false;
  while (*data != data_end)
  {
    char c = **data;

    if (c < 0x30 || c > 0x39)
    {
      if (started)
      {
        return current;
      }
    }
    else
    {
      if (!started)
      {
        current = (c - 0x30);
        started = true;
      }
      else
      {
        current *= 10;
        current += (c - 0x30);
      }
    }

    ++(*data);
  }

  printf("Reached end of file while looking for another integer\n");
  exit(EINVAL);
}

u32 next_int_from_c_str(const char *data)
{
  char c;
  u32 i = 0;
  u32 current = 0;
  bool started = false;
  while ((c = data[i++]))
  {
    if (c < 0x30 || c > 0x39)
    {
      exit(EINVAL);
    }
    if (!started)
    {
      current = (c - 0x30);
      started = true;
    }
    else
    {
      current *= 10;
      current += (c - 0x30);
    }
  }
  return current;
}

void init_processes(const char *path,
                    struct process **process_data,
                    u32 *process_size)
{
  int fd = open(path, O_RDONLY);
  if (fd == -1)
  {
    int err = errno;
    perror("open");
    exit(err);
  }

  struct stat st;
  if (fstat(fd, &st) == -1)
  {
    int err = errno;
    perror("stat");
    exit(err);
  }

  u32 size = st.st_size;
  const char *data_start = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (data_start == MAP_FAILED)
  {
    int err = errno;
    perror("mmap");
    exit(err);
  }

  const char *data_end = data_start + size;
  const char *data = data_start;

  *process_size = next_int(&data, data_end);

  *process_data = calloc(sizeof(struct process), *process_size);
  if (*process_data == NULL)
  {
    int err = errno;
    perror("calloc");
    exit(err);
  }

  for (u32 i = 0; i < *process_size; ++i)
  {
    (*process_data)[i].pid = next_int(&data, data_end);
    (*process_data)[i].arrival_time = next_int(&data, data_end);
    (*process_data)[i].burst_time = next_int(&data, data_end);
  }

  munmap((void *)data, size);
  close(fd);
}

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    return EINVAL;
  }
  struct process *data;
  u32 size;
  init_processes(argv[1], &data, &size);

  u32 quantum_length = next_int_from_c_str(argv[2]);

  struct process_list list;
  TAILQ_INIT(&list);

  u32 total_waiting_time = 0;
  u32 total_response_time = 0;

  /* Your code here */
  u32 current_time = 0;

  //Initialize all other fields in process node
  TAILQ_FOREACH(current_node, &data, pointers){
    current_node->remaining_time = current_node->burst_time;
    current_node->start_exec_time = -1;
  }

  struct process *current_node, *next_node;


  for(u32 current_time = 0; ; ++current_time){
    for (i = 0; i < size; i++)
    {
      if((*data)[i].arrival_time == current_time){
        //Add to queue
      }

    }







  }





  //Loop and execute Round Robin
  while(!TAILQ_EMPTY(&list))
  {
    current_node = TAILQ_FIRST(&list);
    while(current_node != NULL)
    {
      next_node = TAILQ_NEXT(current_node, pointers);

      if(current_node->start_exec_time == -1)
      {
        current_node->start_exec_time = current_time;
        current_node->response_time = current_node->start_exec_time - current_node->arrival_time;
        total_response_time += current_node->response_time;
      }

      if(current_node->remaining_time <= quantum_length)
      {
        current_time += current_node->remaining_time;
        current_node->waiting_time = current_time - current_node->arrival_time - current_node->burst_time;
        total_waiting_time += current_node->waiting_time;
        TAILQ_REMOVE(&list, current_node, pointers);
        free(current_node);
      }
      else
      {
        current_node->remaining_time -= quantum_length;
        current_time += quantum time;
      }


      //if start_exec_time is -1
        //current_node->start_exec_time = current_time;
        //current_node->response_time = current_node->start_exec_time - current_node->arrival_time;

      
      //If remaining time is less than or equal to quantum time
        //current_time += remaining time
        //current_node->waiting_time = current_time - current_node->arrival_time - current_node->burst_time;
        //remove from queue (cleanup)
      //else
        ////current_time += quantum time
        //subtract quantum time from remaining time
        
      current_node = next_node;
    }
  }
  /* End of "Your code here" */

  printf("Average waiting time: %.2f\n", (float)total_waiting_time / (float)size);
  printf("Average response time: %.2f\n", (float)total_response_time / (float)size);

  free(data);
  return 0;
}
