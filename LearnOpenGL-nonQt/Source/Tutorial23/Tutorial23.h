#ifndef TUTORIAL23_H
#define TUTORIAL23_H

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
#include "shadow_map_technique.h"
#include "ogldev_glut_backend.h"
#include "mesh.h"
#include "shadow_map_fbo.h"

#ifdef __TUT_VERSION
#if __TUT_VERSION == 23

class Tutorial23 : public ICallbacks, public OgldevApp
{

private:

  ShadowMapTechnique* m_pShadowMapTech;
  Camera* m_pGameCamera;
  float m_scale;
  SpotLight m_spotLight;
  Mesh* m_pMesh;
  Mesh* m_pQuad;
  ShadowMapFBO m_shadowMapFBO;
  PersProjInfo m_persProjInfo;

public:
  Tutorial23()
  {
    m_pShadowMapTech = NULL;
    m_pGameCamera = NULL;
    m_pMesh = NULL;
    m_pQuad = NULL;
    m_scale = 0.0f;

    m_spotLight.AmbientIntensity = 0.0f;
    m_spotLight.DiffuseIntensity = 0.9f;
    m_spotLight.Color = Vector3f(1.0f, 1.0f, 1.0f);
    m_spotLight.Attenuation.Linear = 0.01f;
    m_spotLight.Position  = Vector3f(-20.0, 20.0, 5.0f);
    m_spotLight.Direction = Vector3f(1.0f, -1.0f, 0.0f);
    m_spotLight.Cutoff =  20.0f;

    m_persProjInfo.FOV = 60.0f;
    m_persProjInfo.Height = WINDOW_HEIGHT;
    m_persProjInfo.Width = WINDOW_WIDTH;
    m_persProjInfo.zNear = 1.0f;
    m_persProjInfo.zFar = 50.0f;
  }

  virtual ~Tutorial23()
  {
    SAFE_DELETE(m_pShadowMapTech);
    SAFE_DELETE(m_pGameCamera);
    SAFE_DELETE(m_pMesh);
    SAFE_DELETE(m_pQuad);
  }

  bool Init(char* pVSFileName, char* pFSFileName);
  void Run();
  virtual void RenderSceneCB();
  virtual void ShadowMapPass();
  virtual void RenderPass();

  void KeyboardCB(OGLDEV_KEY OgldevKey, OGLDEV_KEY_STATE = OGLDEV_KEY_STATE_PRESS);
  virtual void PassiveMouseCB(int x, int y);
};

#endif
#endif

#endif // TUTORIAL23_H
