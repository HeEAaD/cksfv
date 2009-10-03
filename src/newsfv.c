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

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <libgen.h>

#include "cksfv.h"
#include "config.h"


#ifdef WIN32
#include <io.h>
#define BINARY_MODE(fd) setmode(fd, O_BINARY)
#else
#define O_BINARY (0)
#define BINARY_MODE(fd) /* nothing */
#endif

/* Process files in argv array, or stdin if *argv is null */
int newsfv(char **argv)
{
    int fd, rval = 0;
    char *fn;
    uint32_t val;
    char *tmpname;
    struct stat st;
    int is_stdin = 0;

    if (NULL != *argv) {
	pnsfv_head();
	pfileinfo(argv);
    }

    do {
	fn = *argv++;
	
	if (NULL == fn) {
	    fd = STDIN_FILENO;
	    BINARY_MODE(fd);
	    fn = "stdin"; /* Just for error messages */
	    is_stdin = 1;
	} else {
	    if ((fd = open(fn, O_RDONLY | O_LARGEFILE | O_BINARY, 0)) < 0) {
		if (!TOTALLY_QUIET)
		    fprintf(stderr, "cksfv: %s: %s\n", fn, strerror(errno));
		rval = 1;
		continue;
	    }
	    if (fstat(fd, &st)) {
		if (!TOTALLY_QUIET)
		    fprintf(stderr, "cksfv: can not fstat %s: %s\n", fn,
			    strerror(errno));
		rval = 1;
		goto next;
	    }
	    if (S_ISDIR(st.st_mode)) {
		if (!TOTALLY_QUIET)
		    fprintf(stderr, "cksfv: %s: Is a directory\n", fn);
		rval = 1;
		goto next;
	    }
	}
	
	if (crc32(fd, &val)) {
	    if (!TOTALLY_QUIET)
		fprintf(stderr, "cksfv: %s: %s\n", fn, strerror(errno));
	    rval = 1;
	} else {
	    if (is_stdin) {
		pcrc(NULL, val);
	    } else if (use_basename) {
		if ((tmpname = strdup(fn)) == NULL) {
		    if (!TOTALLY_QUIET)
			fprintf(stderr, "out of memory\n");
		    exit(1);
		}
		pcrc(basename(tmpname), val);
		free(tmpname);
	    } else {
		pcrc(fn, val);
	    }
	}
      next:
	if (!is_stdin) {
	    close(fd);
	}
    } while (!is_stdin && *argv);

    return rval;
}
