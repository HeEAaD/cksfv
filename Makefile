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

VERSION="1.2"

all:
	cd src && gmake VERSION=$(VERSION)

install:
	cd src && gmake VERSION=$(VERSION) install

dist:
	gmake clean
	rm -rf ~/cksfv-$(VERSION) \
	&& cp -r . ~/cksfv-$(VERSION) && cd ~ && rm -rf cksfv-$(VERSION)/CVS \
	&& rm -rf cksfv-$(VERSION)/src/CVS \
	&& rm -rf cksfv-$(VERSION)/rpm/CVS \
	&& tar cf cksfv-$(VERSION).tar cksfv-$(VERSION) \
	&& gzip -9f cksfv-$(VERSION).tar \
	&& rm -rf ~/cksfv-$(VERSION) \

rpm:	dist
	cp ~/cksfv-$(VERSION).tar.gz /usr/src/redhat/SOURCES \
	&& cp rpm/*patch /usr/src/redhat/SOURCES \
	&& cp rpm/cksfv.spec /usr/src/redhat/SPECS \
	&& rpm -ba /usr/src/redhat/SPECS/cksfv.spec \
	&& cp /usr/src/redhat/RPMS/i386/cksfv-$(VERSION)*.i386.rpm ~ \
	&& cp /usr/src/redhat/SRPMS/cksfv-$(VERSION)*.src.rpm ~ \

full_dist: rpm
	cp ~/cksfv-$(VERSION)*.src.rpm /home/httpd/html/cksfv/
	cp ~/cksfv-$(VERSION)*.i386.rpm /home/httpd/html/cksfv/
	cp ~/cksfv-$(VERSION).tar.gz /home/httpd/html/cksfv/
	cd /home/httpd/html/cksfv/ && md5sum cksfv-$(VERSION)*.src.rpm \
	cksfv-$(VERSION)*.i386.rpm cksfv-$(VERSION).tar.gz > \
	cksfv-$(VERSION).md5 && cksfv cksfv-$(VERSION)*.src.rpm \
	cksfv-$(VERSION)*.i386.rpm cksfv-$(VERSION).tar.gz > \
	cksfv-$(VERSION).sfv \

clean:
	rm -f *.o *~ *.core core
	rm -f rpm/*.o rpm/*~ rpm/*.core rpm/core
	cd src && gmake clean
