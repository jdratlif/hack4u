AUTOMAKE_OPTIONS = subdir-objects
CLEANFILES = res/hack4u.cc
EXTRA_DIST = res/ankh32x32.ico res/ankh32x32.xpm res/hack4u.icns \
	res/hack4u.xrc res/Info.plist res/windows.rc

bin_PROGRAMS = hack4u

hack4u_SOURCES = hack4u.cc hack4u.hh \
	exceptions/FileIOException.cc exceptions/FileIOException.hh \
	exceptions/InvalidSRAMException.cc exceptions/InvalidSRAMException.hh \
	model/ModelConstants.hh \
	model/SaveSlot.cc model/SaveSlot.hh \
	model/SRAMFile.cc model/SRAMFile.hh \
	res/resource.cpp \
	view/FileDropTarget.cc view/FileDropTarget.hh \
	view/MainFrame.cc view/MainFrame.hh

if WINDOWS
hack4u_SOURCES += res/windows.rc
endif

.rc.o:
	windres @WX_INCLUDES@ -o $@ $<

.xrc.cc:
	wxrc -c -o $@ $<

hack4u.app: hack4u res/hack4u.icns res/Info.plist
	-mkdir hack4u.app
	-mkdir hack4u.app/Contents
	-mkdir hack4u.app/Contents/MacOS
	-mkdir hack4u.app/Contents/Resources
	cp hack4u hack4u.app/Contents/MacOS
	cp res/Info.plist hack4u.app/Contents
	cp res/hack4u.icns hack4u.app/Contents/Resources
	echo -n 'APPL????' > hack4u.app/Contents/PkgInfo
