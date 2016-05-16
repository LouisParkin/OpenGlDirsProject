#ifndef TUTORIAL22_H
#define TUTORIAL22_H

#define WINDOW_WIDTH  1920
#define WINDOW_HEIGHT 1080

#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "ogldev_util.h"
#include "ogldev_app.h"
#include "ogldev_pipeline.h"
#include "ogldev_camera.h"
#include "ogldev_basic_lighting.h"
#include "ogldev_glut_backend.h"
#include "mesh.h"

#ifdef __TUT_VERSION
#if __TUT_VERSION == 22

static const float FieldDepth = 10.0f;

class Tutorial22 : public ICallbacks
{

private:

  BasicLightingTechnique* m_pEffect;
  Camera* m_pGameCamera;
  float m_scale;
  DirectionalLight m_directionalLight;
  Mesh* m_pMesh;
  PersProjInfo m_persProjInfo;

public:
  Tutorial22()
  {
    m_pGameCamera = NULL;
    m_pEffect = NULL;
    m_scale = 0.0f;
    m_directionalLight.Color = Vector3f(1.0f, 1.0f, 1.0f);
    m_directionalLight.AmbientIntensity = 1.0f;
    m_directionalLight.DiffuseIntensity = 0.01f;
    m_directionalLight.Direction = Vector3f(1.0f, -1.0, 0.0);

    m_persProjInfo.FOV = 60.0f;
    m_persProjInfo.Height = WINDOW_HEIGHT;
    m_persProjInfo.Width = WINDOW_WIDTH;
    m_persProjInfo.zNear = 1.0f;
    m_persProjInfo.zFar = 50.0f;
  }

  ~Tutorial22()
  {
    delete m_pEffect;
    delete m_pGameCamera;
    delete m_pMesh;
  }
  bool Init(char* pVSFileName, char* pFSFileName);
  void Run();
  virtual void RenderSceneCB();
  void KeyboardCB(OGLDEV_KEY OgldevKey, OGLDEV_KEY_STATE OgldevKeyState = OGLDEV_KEY_STATE_PRESS);
  virtual void PassiveMouseCB(int x, int y);
};

#endif
#endif

#endif // TUTORIAL22_H
