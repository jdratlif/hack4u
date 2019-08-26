EXTRA_DIST = apidocs docs/*.txt Doxyfile Info.plist vc.net/hack4u/hack4u.sln \
	vc.net/hack4u/hack4u.vcproj
SUBDIRS = source

.PHONY: allclean apidocs touch

allclean: clean
	-rm -rf apidocs
	-rm -f *.bz2 *.gz *.zip
	-find -iname "*~" -exec rm -f {} \;

apidocs: Doxyfile
	@doxygen
    
touch:
	-find -iname "*.cc" -exec touch {} \;
	-find -iname "*.hh" -exec touch {} \;
	-find -iname "*.xrc" -exec touch {} \;

