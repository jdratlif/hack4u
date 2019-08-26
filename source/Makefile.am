AUTOMAKE_OPTIONS = subdir-objects
EXTRA_DIST = res/ankh.ico res/hack4u.xrc res/icon16x16.xpm

bin_PROGRAMS = hack4u

hack4u_SOURCES = hack4u.cc hack4u.hh \
	exceptions/FileIOException.cc exceptions/FileIOException.hh \
	exceptions/InvalidSRAMException.cc exceptions/InvalidSRAMException.hh \
	model/ModelConstants.hh \
	model/SaveSlot.cc model/SaveSlot.hh \
	model/SRAMFile.cc model/SRAMFile.hh \
	res/hack4u.cc \
	view/FileDropTarget.cc view/FileDropTarget.hh \
	view/MainFrame.cc view/MainFrame.hh

if WINDOWS
hack4u_SOURCES += res/windows.rc
endif

.rc.o:
	windres @WX_INCLUDES@ -o $@ $<

.xrc.cc:
	wxrc -c -o $@ $<

