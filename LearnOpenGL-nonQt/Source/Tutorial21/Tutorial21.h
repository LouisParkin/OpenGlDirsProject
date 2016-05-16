#ifndef TUTORIAL21_H
#define TUTORIAL21_H

#define WINDOW_WIDTH  1920
#define WINDOW_HEIGHT 1080

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/freeglut.h>

#include "ogldev_util.h"
#include "ogldev_pipeline.h"
#include "ogldev_camera.h"
#include "ogldev_texture.h"
#include "../lighting_technique.h"
#include "ogldev_glut_backend.h"
#include "ogldev_app.h"

#ifdef __TUT_VERSION
#if __TUT_VERSION == 21
struct Vertex {
  Vector3f m_pos;
  Vector2f m_tex;
  Vector3f m_normal;

  Vertex() {}

  Vertex(const Vector3f& pos, const Vector2f& tex, const Vector3f& normal)
  {
    m_pos = pos;
    m_tex = tex;
    m_normal = normal;
  }

  Vertex(Vector3f pos, Vector2f tex)
  {
    m_pos    = pos;
    m_tex    = tex;
    m_normal = Vector3f(0.0f, 0.0f, 0.0f);
  }

};

static const float FieldDepth = 20.0f;
static const float FieldWidth = 10.0f;

class Tutorial21 : public ICallbacks
{
public:
  Tutorial21()
  {
    m_pGameCamera = NULL;
    m_pTexture = NULL;
    m_pEffect = NULL;
    m_scale = 0.0f;
    m_directionalLight.Color = Vector3f(1.0f, 1.0f, 1.0f);
    m_directionalLight.AmbientIntensity = 0.0f;
    m_directionalLight.DiffuseIntensity = 0.01f;
    m_directionalLight.Direction = Vector3f(1.0f, -1.0, 0.0);

    m_persProjInfo.FOV = 60.0f;
    m_persProjInfo.Height = WINDOW_HEIGHT;
    m_persProjInfo.Width = WINDOW_WIDTH;
    m_persProjInfo.zNear = 1.0f;
    m_persProjInfo.zFar = 50.0f;
  }

  virtual ~Tutorial21()
  {
    delete m_pEffect;
    delete m_pGameCamera;
    delete m_pTexture;
  }

  bool Init(char* pVSFileName, char* pFSFileName);
  void Run();
  virtual void RenderSceneCB();
  void KeyboardCB(OGLDEV_KEY OgldevKey, OGLDEV_KEY_STATE OgldevKeyState = OGLDEV_KEY_STATE_PRESS);
  virtual void PassiveMouseCB(int x, int y);

private:

  GLuint m_VBO;
  LightingTechnique* m_pEffect;
  Texture* m_pTexture;
  Camera* m_pGameCamera;
  float m_scale;
  DirectionalLight m_directionalLight;
  PersProjInfo m_persProjInfo;

  void CreateVertexBuffer();
};

#endif
#endif

#endif // TUTORIAL21_H
