#define T_DIR  1   // Directory
#define T_FILE 2   // File
#define T_DEV  3   // Device

struct stat {
	short type;		// Type of file
	short nlink;	// NUmber of links to file
	int dev;		// File system's disk device
	uint ino;		// Inode number
	uint size;		//Size of file in bytes
};
