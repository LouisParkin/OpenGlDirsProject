#ifndef TUTORIAL_H
#define TUTORIAL_H

#include "Tutorials.h"
#include <functional>

class Tutorial : public Tutorials
{
public:
  virtual ~Tutorial();

  static Tutorial& getInstance(int tutorialId, int* argc, char* argv[])
  {
    static Tutorial instance(tutorialId, argc, argv);
    return instance;
  }
  static void Run();// override final;

protected:
  static void initGlut();
  static void initGlew();
  static void setWindowSize(int width = WINDOW_WIDTH_1_14, int height = WINDOW_HEIGHT_1_14);
  static void setWindowLocation(int topLeftX = WINDOW_START_X, int topLeftY = WINDOW_START_Y);
  static int createWindow(int tutorialID);


  static void renderFunction();
  static void idleFunction();
  static void createVertexBuffer();
  static void createIndexBuffer();
  static void compileShaders();
  static void addShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
  static void specialKeyboardCB(int Key, int x, int y);
  static void keyboardCB(unsigned char Key, int x, int y);
  static void passiveMouseCB(int x, int y);

private:
  explicit Tutorial(int tutorialId, int* argc, char* argv[]);

  static int _tutorialID;
  static GLuint _VBO;
  static GLuint _IBO;
  static GLuint _gWorldLocation;
  static GLuint _gScaleLocation;
  static GLuint _gWVPLocation;
  static PersProjInfo _gPersProjInfo;
  static Camera* _pGameCamera;
  static char pVSFileName[255];
  static char pFSFileName[255];
  static int _width;
  static int _height;
  static int _startX;
  static int _startY;
  static std::set<int> _myWindows;
  static GLuint _gSampler;
  static Texture* _pTexture;

#ifdef __TUT_VERSION

#if __TUT_VERSION == 17

  static Tutorial17* _tutorial;
#elif __TUT_VERSION == 18

  static Tutorial18* _tutorial;

#elif __TUT_VERSION == 19

  static Tutorial19* _tutorial;

#elif __TUT_VERSION == 20

  static Tutorial20* _tutorial;

#elif __TUT_VERSION == 21

  static Tutorial21* _tutorial;

#elif __TUT_VERSION == 22

  static Tutorial22* _tutorial;

#elif __TUT_VERSION == 23

  static Tutorial23* _tutorial;

#endif

#endif


  //  static auto _createVertexBuffer;
  //  void (*)() _createVertexBuffer;
  static std::function<void (void)>                        _createVertexBuffer;
  static std::function<void (void)>                        _createIndexBuffer;
  static std::function<void (void)>                        _compileShaders;
  static std::function<void (void)>                        _displayFunc;
  static std::function<void (void)>                        _idleFunc;
  static std::function<void (GLuint, const char*, GLenum)> _addShaderFunc;
  static std::function<void (int, int, int)>               _specialFunc;
  static std::function<void (int, int, int)>               _keyboardFunc;
  static std::function<void (int, int)>                    _passiveMouseFunc;

  static std::function<void (void)>                        makeCreateVertexBufferFunc(GLuint& vertexObjectBuffer);
  static std::function<void (void)>                        makeCreateIndexBufferFunc(GLuint& indexObjectBuffer);
  static std::function<void (void)>                        makeCompileShadersFunc();
  static std::function<void (void)>                        makeDisplayFunc();
  static std::function<void (void)>                        makeIdleFunc();
  static std::function<void (GLuint, const char*, GLenum)> makeAddShaderFunc();
  static std::function<void (int, int, int)>               makeSpecialFunc();
  static std::function<void (int, int, int)>               makeKeyboardFunc();
  static std::function<void (int, int)>                    makePassiveMouseFunc();
};

#endif // TUTORIAL_H
