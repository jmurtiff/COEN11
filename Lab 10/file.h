#include <pthread.h>

//Jordan Murtiff, Lab 10, Wednesday 11/29/17

//Header file for file prototypes and global variables.

//Prototypes for file functions.
void readFromBinary(char*);
struct waitingList* reverseLinkedLists(struct waitingList*,struct waitingList*);
void quitProgram(char*,char*);
void* autoSaveFile();

//Global variables for file functions.
extern pthread_mutex_t mtx;
extern pthread_t thr;
