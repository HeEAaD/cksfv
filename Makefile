# Makefile for cksfv (Check SFV)

# Copyright (C) 2000 Bryan Call <bc@fodder.org>

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

all:
	cd src && gmake

install:
	cd src && gmake install

dist:
	gmake clean
	rm -rf ~/cksfv-1.1 && \
	cp -r . ~/cksfv-1.1 && cd ~ && rm -rf cksfv-1.1/CVS \
	&& rm -rf cksfv-1.1/src/CVS && tar cf cksfv-1.1.tar cksfv-1.1 \
	&& gzip -9f cksfv-1.1.tar

rpm:	dist
	cp ~/cksfv-1.1.tar.gz /usr/src/redhat/SOURCES && \
	cp rpm/*patch /usr/src/redhat/SOURCES && \
	cp rpm/cksfv.spec /usr/src/redhat/SPECS && \
	rpm -ba /usr/src/redhat/SPECS/cksfv.spec

clean:
	rm -f *.o *~ *.core
	rm -f rpm/*.o rpm/*~ rpm/*.core
	cd src && gmake clean
