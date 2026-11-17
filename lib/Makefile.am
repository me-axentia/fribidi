EXTRA_DIST = fribidi.def

lib_LTLIBRARIES = libfribidi.la

AM_CPPFLAGS =

libfribidi_la_LDFLAGS = -no-undefined -version-info $(LT_VERSION_INFO)
libfribidi_la_LIBADD =
libfribidi_la_DEPENDENCIES =

if !OS_WIN32
libfribidi_la_LDFLAGS += -export-symbols-regex "^fribidi_.*"
endif # OS_WIN32

include Headers.mk
pkginclude_HEADERS = $(libfribidi_la_headers)
nodist_pkginclude_HEADERS = fribidi-config.h

libfribidi_la_SOURCES =	\
		bidi-type.tab.i \
		bidi-types.h \
		common.h \
		debug.h \
		fribidi.c \
		fribidi-bidi.c \
		fribidi-bidi-types.c \
		fribidi-char-sets.c \
		fribidi-char-sets-cap-rtl.c \
		fribidi-char-sets-cp1255.c \
		fribidi-char-sets-cp1256.c \
		fribidi-char-sets-iso8859-6.c \
		fribidi-char-sets-iso8859-8.c \
		fribidi-char-sets-utf8.c \
		fribidi-char-sets-cap-rtl.h \
		fribidi-char-sets-cp1255.h \
		fribidi-char-sets-cp1256.h \
		fribidi-char-sets-iso8859-6.h \
		fribidi-char-sets-iso8859-8.h \
		fribidi-char-sets-utf8.h \
		fribidi-deprecated.c \
		fribidi-brackets.c \
		fribidi-run.c \
		brackets.tab.i \
		brackets-type.tab.i \
		run.h

shaping_sources = \
		arabic-misc.tab.i \
		arabic-shaping.tab.i \
		fribidi-arabic.c \
		fribidi-joining.c \
		fribidi-joining-types.c \
		fribidi-shape.c \
		joining-type.tab.i \
		joining-types.h

mirroring_sources = \
		fribidi-mirroring.c \
		mirroring.tab.i

# Optional sources are kept in the tarball even when not built.
if ENABLE_SHAPING
libfribidi_la_SOURCES += $(shaping_sources)
else
EXTRA_DIST += $(shaping_sources)
endif

if ENABLE_MIRRORING
libfribidi_la_SOURCES += $(mirroring_sources)
else
EXTRA_DIST += $(mirroring_sources)
endif

libfribidi_la_CPPFLAGS = @FRIBIDI_CPPFLAGS@ -DFRIBIDI_BUILD

SHAPING_GENERATEDSOURCES = \
		arabic-shaping.tab.i \
		joining-type.tab.i

MIRRORING_GENERATEDSOURCES = \
		mirroring.tab.i

# All generated sources can always be made (e.g. for "make dist"), but
# only those needed by the configured build are built by default.
GENERATEDSOURCES = \
		fribidi-unicode-version.h \
		bidi-type.tab.i \
		brackets.tab.i \
		brackets-type.tab.i \
		$(SHAPING_GENERATEDSOURCES) \
		$(MIRRORING_GENERATEDSOURCES)

BUILT_SOURCES = \
		fribidi-unicode-version.h \
		bidi-type.tab.i \
		brackets.tab.i \
		brackets-type.tab.i \
		fribidi-config.h

if ENABLE_SHAPING
BUILT_SOURCES += $(SHAPING_GENERATEDSOURCES)
endif

if ENABLE_MIRRORING
BUILT_SOURCES += $(MIRRORING_GENERATEDSOURCES)
endif

$(GENERATEDSOURCES):
	@(cd $(top_builddir)/gen.tab && \
	$(MAKE) $(AM_MAKEFLAGS) $@) && \
	(test -f $@ || mv $(top_builddir)/gen.tab/$@ .)

# re-generate all built sources:
gen:
	@(cd $(top_builddir)/gen.tab && \
	$(MAKE) $(AM_MAKEFLAGS) $@) && \
	$(RM) $(BUILT_SOURCES)
	$(MAKE) $(AM_MAKEFLAGS) $(BUILT_SOURCES)

MAINTAINERCLEANFILES = $(GENERATEDSOURCES) fribidi-config.h

$(top_builddir)/config.h: $(top_srcdir)/config.h.in
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) config.h

.PHONY: gen

-include $(top_srcdir)/git.mk
