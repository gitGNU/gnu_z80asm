# Makefile for the Z80 assembler by shevek
# Copyright 2002-2007  Bas Wijnen
#
# This file is part of z80asm.
#
# Z80asm is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# Z80asm is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

SUBDIRS = po src . doc tests data

owndist: clean
	! git status | grep modified
	echo $(VERSION) > VERSION
	git add VERSION
	-git commit -m "Release version $(VERSION)"
	rm -rf /tmp/z80asm-$(VERSION)
	git archive --format=tar --prefix=z80asm-$(VERSION)/ HEAD | tar xf - -C /tmp
	tar cvzf ../z80asm-$(VERSION).tar.gz -C /tmp z80asm-$(VERSION)
	rm -r /tmp/z80asm-$(VERSION)
	cd .. && gpg -b z80asm-$(VERSION).tar.gz
	scp ../z80asm-$(VERSION).tar.gz* dl.sv.nongnu.org:/releases/z80asm/
	git push

ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = config.rpath m4/ChangeLog
