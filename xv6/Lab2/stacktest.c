#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"

uint recursive_call(uint i) {
  return recursive_call(i+1);
}
int main(int argc, char * argv[]) {
  uint i;

  i = recursive_call(0);
  printf(1, "%d\n", i);

  exit();
}
