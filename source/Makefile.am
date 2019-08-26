.rc.o:
	windres -o $@ $<

AUTOMAKE_OPTIONS = subdir-objects
EXTRA_DIST = xrc/hack4u.xrc res/ankh.ico

bin_PROGRAMS = hack4u
hack4u_SOURCES = hack4u.cc hack4u.hh \
	view/MainFrame.cc view/MainFrame.hh \
	view/FileDropTarget.cc view/FileDropTarget.hh \
	model/SaveSlot.cc model/SaveSlot.hh

if WINDOWS
hack4u_SOURCES += windows.rc
endif

