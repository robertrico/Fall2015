/* Robert Rico */
#include "libshm.h"
#include <stdio.h>
#include <wait.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>

void Producer(int, int, int);

