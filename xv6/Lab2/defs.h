struct buf;
struct context;
struct file;
struct inode;
struct pipe;
struct proc;
struct rtcdate;
struct spinlock;
struct sleeplock;
struct stat;
struct superblock;

// bio.c
struct buf*     bread(uint, uint);
void			binit(void);
void            brelse(struct buf*);
void            bwrite(struct buf*);
// console.c
void            consoleinit(void);
void            cprintf(char*, ...);
void            consoleintr(int(*)(void));
void            panic(char*) __attribute__((noreturn));
// exec.c
int             exec(char*, char**);
// file.c
struct file*    filealloc(void);
struct file*    filedup(struct file*);
void			fileclose(struct file*);
void            fileinit(void);
int             fileread(struct file*, char*, int);
int             filestat(struct file*, struct stat*);
int             filewrite(struct file*, char*, int);
// fs.c
struct inode*   dirlookup(struct inode*, char*, uint*);
struct inode*   ialloc(uint, short);
struct inode*   idup(struct inode*);
struct inode*	namei(char*);
struct inode*	nameiparent(char*, char*);
void            iinit(int);
void            ilock(struct inode*);
void            iput(struct inode*);
void            iunlock(struct inode*);
void            iunlockput(struct inode*);
void            iupdate(struct inode*);
void			readsb(int dev, struct superblock *sb);
void			stati(struct inode*, struct stat*);
int             namecmp(const char*, const char*);
int				dirlink(struct inode*, char*, uint);
int             readi(struct inode*, char*, uint, uint);
int             writei(struct inode*, char*, uint, uint);
// ide.c
void            ideinit(void);
void            ideintr(void);
void            iderw(struct buf*);
// ioapic.c
void            ioapicenable(int, int);
void			ioapicinit(void);
extern uchar    ioapicid;
// kalloc.c
char*           kalloc(void);
void            kfree(char*);
void            kinit1(void*, void*);
void            kinit2(void*, void*);
// kbd.c
void            kbdintr(void);
// lapic.c
int             cpunum(void);
extern volatile uint*    lapic;
void			cmostime(struct rtcdate *r);
void            lapiceoi(void);
void            lapicinit(void);
void            lapicstartap(uchar, uint);
void            microdelay(int);
// log.c
void            initlog(int dev);
void            log_write(struct buf*);
void            begin_op();
void            end_op();
// mp.c
extern int      ismp;
void            mpinit(void);
// picirq.c
void            picenable(int);
void            picinit(void);
// pipe.c
void            pipeclose(struct pipe*, int);
int				pipealloc(struct file**, struct file**);
int             piperead(struct pipe*, char*, int);
int             pipewrite(struct pipe*, char*, int);
//PAGEBREAK: 16
// proc.c
int             fork(void);
int             growproc(int);
int             kill(int);
int				wait(int*);
int				v2p(int*, int*);
void			exit(int);
void            pinit(void);
void            procdump(void);
void            scheduler(void) __attribute__((noreturn));
void            sched(void);
void            sleep(void*, struct spinlock*);
void            userinit(void);
void            wakeup(void*);
void            yield(void);
// swtch.S
void            swtch(struct context**, struct context*);
// spinlock.c
int				holding(struct spinlock*);
void            acquire(struct spinlock*);
void            getcallerpcs(void*, uint*);
void            initlock(struct spinlock*, char*);
void            release(struct spinlock*);
void            pushcli(void);
void            popcli(void);
// sleeplock.c
void            acquiresleep(struct sleeplock*);
void            releasesleep(struct sleeplock*);
void            initsleeplock(struct sleeplock*, char*);
int				holdingsleep(struct sleeplock*);
// string.c
void*           memmove(void*, const void*, uint);
void*           memset(void*, int, uint);
char*           safestrcpy(char*, const char*, int);
char*			strncpy(char*, const char*, int);
int				memcmp(const void*, const void*, uint);
int             strlen(const char*);
int             strncmp(const char*, const char*, uint);
// syscall.c
int             argint(int, int*);
int             argptr(int, char**, int);
int             argstr(int, char**);
int             fetchint(uint, int*);
int             fetchstr(uint, char**);
void            syscall(void);
// timer.c
void            timerinit(void);
// trap.c
void            idtinit(void);
void			tvinit(void);
extern uint     ticks;
extern struct spinlock tickslock;
// uart.c
void            uartinit(void);
void            uartintr(void);
void            uartputc(int);
// vm.c
void            seginit(void);
void            kvmalloc(void);
void			freevm(pde_t*);
void			inituvm(pde_t*, char*, uint);
void			switchuvm(struct proc*);
void			switchkvm(void);
void			clearpteu(pde_t*, char*);
pde_t*          setupkvm(void);
pde_t*			copyuvm(pde_t*, uint);
char*           uva2ka(pde_t*, char*);
int             allocuvm(pde_t*, uint, uint);
int             deallocuvm(pde_t*, uint, uint);
int             loaduvm(pde_t*, char*, struct inode*, uint, uint);
int             copyout(pde_t*, uint, void*, uint);
// number of elements in fixed-size array
#define NELEM(x) (sizeof(x)/sizeof((x)[0]))
