/* Robert Rico */
#include <stdio.h>
#include <wait.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>

// Size of shared memory block
// Pass this to ftruncate and mmap
#define SHM_SIZE 4096
#define SHM_NAME "OS_HW1"

// Global pointer to the shared memory block
// This should receive the return value of mmap
// Don't change this pointer in any function
void* gShmPtr;

// You won't necessarily need all the functions below
void InitShm(int, int);
void SetBufSize(int);
void SetItemCnt(int);
void SetIn(int);
void SetOut(int);
void SetHeaderVal(int, int);
int GetBufSize();
int GetItemCnt();
int GetIn();
int GetOut();
int GetHeaderVal(int);
void WriteAtBufIndex(int, int);
int ReadAtBufIndex(int);
int GetRand(int, int);
