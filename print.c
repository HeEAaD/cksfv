/* print.c - displays checksum listing
   
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

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>

void pheader()
{
  clock_t       clock;
  struct tm     *timeinfo;
  
  clock = time(NULL);
  timeinfo = localtime(&clock);
  printf("; Generated by cksfv v1.0 on ");
  printf("%02d-%02d-%02d at %02d:%02d.%02d\n", timeinfo->tm_year+1900,
         timeinfo->tm_mon, timeinfo->tm_mday, timeinfo->tm_hour,
         timeinfo->tm_min, timeinfo->tm_sec);
  printf("; Written by Bryan Call <bc@fodder.org> ");
  printf("- http://www.fodder.org/cksfv\n");
}

void pfileinfo(char **argv)
{
  char          *fn;
  struct stat   sb;
  struct tm     *timeinfo;
  
  printf(";\n");
  
  while(*argv) {
    fn = *argv++;
    if (!(stat(fn, &sb))) {
      timeinfo = localtime(&sb.st_mtime);
      printf(";%13d  %02d:%02d.%02d %02d-%02d-%02d %s\n",
             (int)sb.st_size, timeinfo->tm_hour, timeinfo->tm_min,
             timeinfo->tm_sec,
             timeinfo->tm_year+1900, timeinfo->tm_mon, timeinfo->tm_mday, fn);
    }
  }
}

void pcrc(char *fn, unsigned long val, unsigned long len)
{
  printf("%s %lX\n", fn, val);
}
