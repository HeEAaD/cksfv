/* newsfv.c - creates a new checksum listing
   
   Copyright (C) 2000 Bryan Call <bc@fodder.org>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. */

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

extern void pheader();
extern void pfileinfo(char**);
extern void pcrc(char*, unsigned long, unsigned long);
extern int  crc32(int, unsigned long*, unsigned long*);

int newsfv(char **argv)
{
  int           fd, rval = 0;
  char          *fn;
  unsigned long len, val;
  
  pheader();
  pfileinfo(argv);
  
  while (*argv) {
    fn = *argv++;
    if ((fd = open(fn, O_RDONLY, 0)) < 0) {
      fprintf(stderr, "cksfv: %s: %s\n", fn, strerror(errno)); 
      rval = 1;
      continue;
    }
    
    if (crc32(fd, &val, &len)) {
      fprintf(stderr, "cksfv: %s: %s\n", fn, strerror(errno)); 
      rval = 1;
    } else
      pcrc(fn, val, len);
    close(fd);
  }

  return(rval);
}
