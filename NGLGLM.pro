# -------------------------------------------------
# Project created by QtCreator 2009-11-05T12:31:57
# -------------------------------------------------
# qt 5 wants this may cause errors with 4
isEqual(QT_MAJOR_VERSION, 5) {cache() }

# We will use the built in Qt lib template
TEMPLATE = lib
QT += opengl
QT += core
QT += gui
QT -=xml

CONFIG+=c++11

# use this to remove any marked as deprecated classes from NGL
DEFINES += REMOVEDDEPRECATED
# What image library to use change to 1 of these depending on what platform
# QImage USEQIMAGE
# ImageMagick USEIMAGEMAGIC
# OpenImageIO USEOIIO
IMAGELIB=USEQIMAGE
# add this to the global defines
DEFINES +=$$IMAGELIB
equals(IMAGELIB,"USEIMAGEMAGIC"){
	QMAKE_CXXFLAGS+=$$system(Magick++-config --cppflags )
	LIBS+=$$system(Magick++-config --ldflags --libs )
	message("Using Image Magick config is")
	message($$system(Magick++-config --cppflags ) )
	message($$system(Magick++-config --ldflags --libs ))
}
equals(IMAGELIB,"USEOIIO"){
	LIBS+=-L/usr/local/lib/ -lOpenImageIO
}

# to ensure we don't get any ABI issues use c++ and correct libs on mac

# as I want to support 4.8 and 5 this will set a flag for some of the mac stuff
# mainly in the types.h file for the setMacVisual which is native in Qt5
isEqual(QT_MAJOR_VERSION, 5) {DEFINES +=QT5BUILD }

# define this if you want to include the stanford data sets
# these are very big and make compilation time huge
DEFINES+=ADDLARGEMODELS
# set the base directory of our project so Qt knows where to find them
# we can use shell vars but need to use $$

NGLGLMPATH=$$(NGLGLMDIR)

isEmpty(NGLGLMPATH){ # note brace must be here
  BASE_DIR=$$(HOME)/NGLGLM
}
else{ # note brace must be here
  BASE_DIR=$$(NGLGLMDIR)
}

message($${BASE_DIR})

# This is the output target we want to create
TARGET = $$BASE_DIR/lib/NGLGLM
# this is where we want to put the intermediate build files ( ../obj)
OBJECTS_DIR = $$BASE_DIR/obj
QMAKE_LFLAGS-= -headerpad_max_install_names
QMAKE_LFLAGS_SHLIB -= -single_module
QMAKE_LFLAGS_VERSION=
QMAKE_LFLAGS_COMPAT_VERSION=
QMAKE_LFLAGS_SONAME=
# use this to suppress some warning from boost
unix:QMAKE_CXXFLAGS_WARN_ON += "-Wno-unused-parameter"
macx:QMAKE_MAC_SDK=macosx10.12
# define the NGL_DEBUG flag for the graphics lib
DEFINES += NGL_DEBUG
# if you install boost to /usr/local/include/ we can find it from this line
# basically all you need to do is copy the headers from the boost source to this
# location cp -R boost_1_49_0/boost /usr/local/include under linux use apt-get install
unix:INCLUDEPATH+=/usr/local/include
#set some flags for sse etc
QMAKE_CFLAGS+= -DGLEW_NO_GLU -DGLEW_STATIC
unix:QMAKE_CXXFLAGS_WARN_ON += -Wno-builtin-macro-redefined -isystem
macx:DEFINES +=GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
macx {
QMAKE_POST_LINK = install_name_tool -id @rpath/$$PWD/lib/libNGLGLM.1.0.0.dylib $$PWD/lib/libNGLGLM.1.0.0.dylib
}

# this is where to look for includes
INCLUDEPATH += $$BASE_DIR/include/ngl
INCLUDEPATH += $$BASE_DIR/glew/
INCLUDEPATH += $$BASE_DIR/src/ngl
INCLUDEPATH +=$$BASE_DIR/src/shaders
INCLUDEPATH +=$$BASE_DIR/include/rapidjson
# using the fmt library https://github.com/fmtlib/fmt but header only.
DEFINES+=FMT_HEADER_ONLY
INCLUDEPATH +=$$BASE_DIR/include/fmt

unix:LIBS += -L/usr/local/lib
LIBS+= -lboost_system
# set the SRC_DIR so we can find the project files
SRC_DIR = $$BASE_DIR/src


# and the include files
INC_DIR = $$BASE_DIR/include/ngl
DEPENDPATH= $$INC_DIR
DEPENDPATH +=$$SRC_DIR/ngl/
DEPENDPATH +=$$SRC_DIR/shaders/
QMAKE_CXXFLAGS+=-Wall
macx:{
  QMAKE_CXXFLAGS+=  -fPIC
	LIBS+= -L/System/Library/Frameworks/OpenGL.framework/Libraries -framework OpenGL
	LIBS+=  -Wl,-framework,Cocoa
	#DEFINES += DARWIN
}

# in this case unix is also mac so we need to exclude mac from the unix build
win32|unix:!macx{
	# now define some linux specific flags
	unix:QMAKE_CXXFLAGS+=  -march=native
	#unix:DEFINES += LINUX
	unix:LIBS+= -L/usr/lib64 -lGL -lGLU -lX11

}


# The windows configuration is very frustrating however I seem to have it working now
# you will need to install boost in the path below
# once you have done this set the PATH environment variable to look in
# c:/NGL/lib to find the DLL
win32{
				message("Using Windows check to see what needs to be installed")
				CONFIG+=staticlib
				INCLUDEPATH +=C:/boost/
        INCLUDEPATH += C:/SDKs/ #for university STEM build
				DEFINES+=_USE_MATH_DEFINES
				# Silence some boost warnings
				DEFINES+= _SCL_SECURE_NO_WARNINGS
				DESTDIR=c:/
				DEFINES += NO_DLL
				DEFINES += GLEW_STATIC
}


SOURCES += 		$$SRC_DIR/ShaderLib.cpp \
		$$SRC_DIR/NGLInit.cpp \
		$$SRC_DIR/Shader.cpp \
    $$SRC_DIR/ShaderProgram.cpp \
    $$SRC_DIR/Util.cpp
#exclude this from iOS
win32|unix|macx:{
	SOURCES+=glew/glew.c
}

ios {
	message("IOS BUILD")
	DEFINES+=USINGIOS_
}



HEADERS += $$INC_DIR/Singleton.h \
		$$INC_DIR/Types.h \
		$$INC_DIR/ShaderLib.h \
		$$INC_DIR/NGLassert.h \
		$$INC_DIR/NGLInit.h \
		$$INC_DIR/Shader.h \
    $$INC_DIR/Util.h \
		$$INC_DIR/ShaderProgram.h \
		$$SRC_DIR/shaders/TextShaders.h \
		$$SRC_DIR/shaders/ColourShaders.h \
		$$SRC_DIR/shaders/DiffuseShaders.h \
		$$SRC_DIR/shaders/ToonShaders.h \

#unix:PRECOMPILED_HEADER += $$SRC_DIR/ngl/Meshes.h \


OTHER_FILES+= Doxyfile \
              README.md \
              CMakeLists.txt


