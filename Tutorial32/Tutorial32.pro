TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++0x -Wall -pedantic

INCLUDEPATH += \
           /home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Source \
           /home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Include \
           /home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Include/assimp \
           /home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Include/ATB \
           /home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Common/FreetypeGL \
           /home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Include/ImageMagick-6

INCLUDEPATH += \
           /home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Lib

DEPENDPATH += \
           /home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Lib

SOURCES += \
    Tutorial32.cpp

SOURCES += \
           /home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Common/FreetypeGL/font-manager.c \
           /home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Common/FreetypeGL/texture-atlas.c \
           /home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Common/FreetypeGL/vector.c \
           /home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Common/FreetypeGL/texture-font.c \
           /home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Common/FreetypeGL/texture-glyph.c \
           /home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Common/FreetypeGL/vertex-buffer.c \
           /home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Common/ogldev_util.cpp \
           /home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Common/math_3d.cpp \
           /home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Common/pipeline.cpp \
           /home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Common/camera.cpp \
           /home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Common/ogldev_atb.cpp \
           /home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Common/ogldev_backend.cpp \
           /home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Common/glut_backend.cpp \
           /home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Common/ogldev_glfw_backend.cpp \
           /home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Common/ogldev_texture.cpp \
           /home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Common/ogldev_app.cpp \
           /home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Common/ogldev_basic_lighting.cpp \
           /home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Common/technique.cpp \
           /home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Common/FreetypeGL/freetypeGL.cpp \
           /home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Common/ogldev_shadow_map_fbo.cpp \
           /home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Common/FreetypeGL/font_shader.cpp \
           /home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Common/cubemap_texture.cpp \
           /home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Common/ogldev_basic_mesh.cpp

include(deployment.pri)
qtcAddDeployment()

LIBS +=  -L/home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Lib

LIBS += -lGL -lglut -lGLEW -lAntTweakBar -lglfw -lcurses -lMagickCore -lMagickWand -lMagick++ -lfontconfig -lfreetype -lassimp

