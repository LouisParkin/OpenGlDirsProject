# Qt-Creaor generated content.
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

#  Add the C++11 standard to allow use of lambda functions
QMAKE_CXXFLAGS += -std=c++0x -Wall -pedantic

#  The version number greater than 16 to be added as option 'h' on the menu.
TUT_VERSION = 23

# Add the menu-option 'h' as a compile-time define.
TUT_DEFINE  = __TUT_VERSION=$$TUT_VERSION
DEFINES += $$TUT_DEFINE

# Print out the above information to the compile output, ensure that it can be verified.
message(TUT_VERSION = $$TUT_VERSION)
message(TUT_DEFINE  = $$TUT_DEFINE )

# Add all paths the compiler should check for header files.
INCLUDEPATH += \
           $$PWD/../../Source \
           $$PWD/../../Include \
           $$PWD/../../Include/assimp \
           $$PWD/../../Include/ATB \
           $$PWD/../../Common/FreetypeGL \
           $$PWD/../../Include/ImageMagick-6

# Include a search-path for custom libs.
INCLUDEPATH += \
           $$PWD/../../Lib

# Make the existence of the libs folder a dependency.
DEPENDPATH += \
           $$PWD/../../Lib

# All sources that do not belong to a library, but are required by the linker.
SOURCES += \
           $$PWD/../../Common/FreetypeGL/font-manager.c \
           $$PWD/../../Common/FreetypeGL/texture-atlas.c \
           $$PWD/../../Common/FreetypeGL/vector.c \
           $$PWD/../../Common/FreetypeGL/texture-font.c \
           $$PWD/../../Common/FreetypeGL/texture-glyph.c \
           $$PWD/../../Common/FreetypeGL/vertex-buffer.c \
           $$PWD/../../Source/main.cpp\
           $$PWD/../../Common/ogldev_util.cpp \
           $$PWD/../../Common/math_3d.cpp \
           $$PWD/../../Common/pipeline.cpp \
           $$PWD/../../Common/camera.cpp \
           $$PWD/../../Common/ogldev_atb.cpp \
           $$PWD/../../Common/ogldev_backend.cpp \
           $$PWD/../../Common/glut_backend.cpp \
           $$PWD/../../Common/ogldev_glfw_backend.cpp \
           $$PWD/../../Common/ogldev_texture.cpp \
           $$PWD/../../Common/ogldev_app.cpp \
           $$PWD/../../Common/ogldev_basic_lighting.cpp \
           $$PWD/../../Common/technique.cpp \
           $$PWD/../../Common/FreetypeGL/freetypeGL.cpp \
           $$PWD/../../Common/FreetypeGL/font_shader.cpp \
           $$PWD/../../Source/Tutorials.cpp \
           $$PWD/../../Source/Tutorial.cpp



# Print out what Tutorials will appear on the application menu.
message(Building for Tutorials 4-16 and $$TUT_VERSION)

# For some reason, qmake refuses to see the .cpp extension if added directly to a file name.
# Yet, it is fine if it is define as was done below.
FILE_EXT = ".cpp"
greaterThan(TUT_VERSION,16) {

  # For when menu option 'h' is 17 or greater.
  greaterThan(TUT_VERSION,16) {                                       # Brace Opening #1

    # For when menu option 'h' is 21 or below.
    lessThan(TUT_VERSION,22) {                                        # Brace Opening #2

      # So for tutorials 17 to 21, a file name lighting_technique.cpp will be compiled and linked.
      message(adding version $$TUT_VERSION-specific source file: Source/lighting_technique$$FILE_EXT)
      SOURCES += $$PWD/../../Source/lighting_technique.cpp
      HEADERS += $$PWD/../../Source/lighting_technique.h

    }                                                                 # Brace Closing #2

    # For when menu option 'h' is 22 or greater.
    greaterThan(TUT_VERSION,21) {                                     # Brace Opening #3

      # So for tutorials 22 and later, a file name mesh.cpp will be compiled and linked.
      message(adding version $$TUT_VERSION-specific source file: Source/mesh$$FILE_EXT)
        SOURCES += $$PWD/../../Source/mesh.cpp

      # For when menu option 'h' is 23 or greater.
      greaterThan(TUT_VERSION,22) {                                   # Brace Opening #4

        # So for tutorials 23 and later, a file name shadow_map_technique.cpp will be compiled and linked.
        message(adding version $$TUT_VERSION-specific source file: Source/Tutorial$$TUT_VERSION/shadow_map_technique$$FILE_EXT)

        # So for tutorials 23 and later, a file name ogldev_shadow_map_fbo.cpp will be compiled and linked.
        message(adding version $$TUT_VERSION-specific source file: Common/ogldev_shadow_map_fbo$$FILE_EXT)

        SOURCES += $$PWD/../../Source/Tutorial$$TUT_VERSION/shadow_map_technique.cpp \
                   $$PWD/../../Common/ogldev_shadow_map_fbo.cpp

      }                                                               # Brace Closing #4
    }                                                                 # Brace Closing #3

    message(adding version $$TUT_VERSION-specific source file: Tutorial$$TUT_VERSION/Tutorial$$TUT_VERSION$$FILE_EXT)
        SOURCES += $$PWD/../../Source/Tutorial$$TUT_VERSION/Tutorial$$TUT_VERSION$$FILE_EXT

  }                                                                   # Brace Closing #1

}
# The project headers in the Source directory
HEADERS  += \
           $$PWD/../../Source/Tutorials.h \
           $$PWD/../../Source/Tutorial.h

HEADERS += \
           $$PWD/../../Include/ogldev_app.h


# Add libs dir into the library search path.
LIBS +=  -L$$PWD/../../Lib

# Add libraries to link for this application.
LIBS += -lGL -lglut -lGLEW -lAntTweakBar -lglfw -lcurses -lMagickCore -lMagickWand -lMagick++ -lfontconfig -lfreetype -lassimp

# Qt-Creaor generated content.
include(deployment.pri)
qtcAddDeployment()

