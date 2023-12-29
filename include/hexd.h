/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   hexd.h                                                                   */
/*                                                                            */
/*   By: alkuzin <->                                                          */
/*                                                                            */
/*   Created: 2023/12/26 13:00:57 by alkuzin                                  */
/*   Updated: 2023/12/29 19:07:00 by alkuzin                                  */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEXD_H
#define HEXD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define VERSION "1.0"
#define YEAR "2023"
#define FMT_SIZE 5
#define FILENAME_SIZE 64

enum {
	BIN=0,
	OCT=1,
	HEX=2
};

// show bytes of file
extern void show_bytes(FILE* fp, int base);

// check is file open 
extern void is_open(char* arg);

// show options list
extern void show_help(void);

// show version (obvious)
extern void show_version(void);

#endif /* HEXD_H */
