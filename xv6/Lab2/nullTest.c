#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "param.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"

int main()
{
	int *pointer = 0;
	int deref = *pointer;
	deref = deref;
	return 0;
}
