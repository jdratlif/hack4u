# $Id: Makefile.am,v 1.12 2008/12/17 00:39:31 jdratlif Exp $

SUBDIRS = source
EXTRA_DIST = apidocs docs/*.txt Doxyfile sav \
	vstudio/hack4u/hack4u.sln vstudio/hack4u/hack4u.vcproj

sav:
	-mkdir sav
	-cp source/res/Ultima\ -\ Quest\ of\ the\ Avatar\ \(U\).sav sav

.PHONY: allclean apidocs bundle touch

allclean: clean
	-rm -rf source/hack4u.app
	-rm -rf apidocs
	-rm -f *.bz2
	-find -iname "*~" -exec rm -f {} \;

apidocs: Doxyfile
	@doxygen

bundle:
	-cd source && make hack4u.app

touch:
	-find -iname "*.cc" -exec touch {} \;
	-find -iname "*.hh" -exec touch {} \;
	-find -iname "*.xrc" -exec touch {} \;

