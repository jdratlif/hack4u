SUBDIRS = source
EXTRA_DIST = apidocs docs/*.txt Doxyfile sav \
	vstudio/hack4u.sln vstudio/hack4u.vcxproj \
	vstudio/hack4u.vcxproj.filters vstudio/hack4u.vcxproj.user

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
	-find -iname "*.cpp" -exec touch {} \;
	-find -iname "*.hh" -exec touch {} \;
	-find -iname "*.xrc" -exec touch {} \;
