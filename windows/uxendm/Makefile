
BUILDDIR_default = obj
SRCDIR ?= .
TOPDIR = $(abspath $(SRCDIR)/../..)
include $(TOPDIR)/Config.mk

$(call include_lib,LIBVHD,../libvhd)
$(call include_lib,LIBXC,../libxc)
$(call include_lib,LIBUXENCTL,../uxenctl)
$(call include_lib,YAJL,../yajl)
$(call include_lib,LIBFILECRYPT,../filecrypt)
$(call include_lib,LIBUXENCONSOLE,../uxenconsole)
$(call include_lib,LIBUXENH264,../uxenh264)

ifeq (,$(MAKENOW))

SRCROOT = $(abspath $(TOPDIR)/dm)

VPATH = $(SRCROOT)

include $(SRCROOT)/Makefile.dm

endif # MAKENOW
