#ifndef _CKSFV_H_
#define _CKSFV_H_

#include "config.h"

extern int use_basename;
extern int be_quiet;
extern int be_caseinsensitive;

int readsfv(char *filename, char *dir, int argc, char **argv);
int newsfv(char **);
void pusage(void);

void pnsfv_head();
void pfileinfo(char **);
void pcrc(char *fn, uint32_t val);
int crc32(int fd, uint32_t *val);
void prsfv_head(char *fn);

#endif
