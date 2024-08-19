#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <unistd.h> 
#include <sys/wait.h> 
void *thread_function(void *arg) { 
 printf("Thread created. PID: %d, TID: %lu\n", getpid(),  pthread_self()); 
 sleep(1); 
 return NULL; 
} 
int main() { 
 pid_t pid; 
 pthread_t tid; 
 int i, j; 
 for (i = 0; i < 3; i++) { 
 pid = fork(); 
 if (pid < 0) { 
 perror("fork"); 
 exit(EXIT_FAILURE); 
 } else if (pid == 0) { 
 printf("Child process created. PID: %d\n", getpid());  for (j = 0; j < 2; j++) { 
 if (pthread_create(&tid, NULL, thread_function, NULL) != 0)  { 
 perror("pthread_create");
 exit(EXIT_FAILURE); 
 } 
 pthread_join(tid, NULL);  
 } 
 exit(EXIT_SUCCESS); 
 } 
 } 
 for (i = 0; i < 3; i++) { 
 if (wait(NULL) == -1) {  
 perror("wait"); 
 exit(EXIT_FAILURE); 
 } 
 } 
 return 0; 
} 

