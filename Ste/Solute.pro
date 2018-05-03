TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp \
    md5/md5.cpp \
    md5/md5wrapper.cpp \
    jpeglib/jaricom.c \
    jpeglib/jcapimin.c \
    jpeglib/jcapistd.c \
    jpeglib/jcarith.c \
    jpeglib/jccoefct.c \
    jpeglib/jccolor.c \
    jpeglib/jcdctmgr.c \
    jpeglib/jchuff.c \
    jpeglib/jcinit.c \
    jpeglib/jcmainct.c \
    jpeglib/jcmarker.c \
    jpeglib/jcmaster.c \
    jpeglib/jcomapi.c \
    jpeglib/jcparam.c \
    jpeglib/jcprepct.c \
    jpeglib/jcsample.c \
    jpeglib/jctrans.c \
    jpeglib/jdapimin.c \
    jpeglib/jdapistd.c \
    jpeglib/jdarith.c \
    jpeglib/jdatadst.c \
    jpeglib/jdatasrc.c \
    jpeglib/jdcoefct.c \
    jpeglib/jdcolor.c \
    jpeglib/jddctmgr.c \
    jpeglib/jdhuff.c \
    jpeglib/jdinput.c \
    jpeglib/jdmainct.c \
    jpeglib/jdmarker.c \
    jpeglib/jdmaster.c \
    jpeglib/jdmerge.c \
    jpeglib/jdpostct.c \
    jpeglib/jdsample.c \
    jpeglib/jdtrans.c \
    jpeglib/jerror.c \
    jpeglib/jfdctflt.c \
    jpeglib/jfdctfst.c \
    jpeglib/jfdctint.c \
    jpeglib/jidctflt.c \
    jpeglib/jidctfst.c \
    jpeglib/jidctint.c \
    jpeglib/jmemmgr.c \
    jpeglib/jmemnobs.c \
    jpeglib/jpeglib.c \
    jpeglib/jquant1.c \
    jpeglib/jquant2.c \
    jpeglib/jutils.c \
    stb_image_write.c \
    JpegImage.cpp \
    stegRGB.cpp \

   HEADERS += \
    jpeglib/jconfig.h \
    jpeglib/jdct.h \
    jpeglib/jerror.h \
    jpeglib/jinclude.h \
    jpeglib/jmemsys.h \
    jpeglib/jmorecfg.h \
    jpeglib/jpegint.h \
    jpeglib/jpeglib.h \
    jpeglib/jversion.h \
    md5/md5.h \
    md5/md5wrapper.h \
    rgb_structure.h \
    stb_image_write.h \
    stegRGB.h \
    JpegImage.h \

FORMS +=

