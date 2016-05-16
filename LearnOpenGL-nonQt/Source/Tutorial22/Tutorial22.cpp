#include "Tutorial22.h"

#ifdef __TUT_VERSION
#if __TUT_VERSION == 22

bool Tutorial22::Init(char* pVSFileName, char* pFSFileName)
{
  Vector3f Pos(3.0f, 7.0f, -10.0f);
  Vector3f Target(0.0f, -0.2f, 1.0f);
  Vector3f Up(0.0, 1.0f, 0.0f);

  m_pGameCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT, Pos, Target, Up);

  m_pEffect = new BasicLightingTechnique();

  if (!m_pEffect->Init(pVSFileName, pFSFileName)) {
    printf("Error initializing the lighting technique\n");
    return false;
  }

  m_pEffect->Enable();

  m_pEffect->SetColorTextureUnit(0);

  m_pMesh = new Mesh();

  return m_pMesh->LoadMesh("/home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Project/Content/phoenix_ugv.md2");
}

void Tutorial22::Run()
{
  GLUTBackendRun(this);
}

void Tutorial22::RenderSceneCB()
{
  m_scale += 0.01f;

  m_pGameCamera->OnRender();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  PointLight pl[2];
  pl[0].DiffuseIntensity = 0.25f;
  pl[0].Color = Vector3f(1.0f, 0.5f, 0.0f);
  pl[0].Position = Vector3f(3.0f, 1.0f, FieldDepth * (cosf(m_scale) + 1.0f) / 2.0f);
  pl[0].Attenuation.Linear = 0.1f;
  pl[1].DiffuseIntensity = 0.25f;
  pl[1].Color = Vector3f(0.0f, 0.5f, 1.0f);
  pl[1].Position = Vector3f(7.0f, 1.0f, FieldDepth * (sinf(m_scale) + 1.0f) / 2.0f);
  pl[1].Attenuation.Linear = 0.1f;
  m_pEffect->SetPointLights(2, pl);

  SpotLight sl;
  sl.DiffuseIntensity = 0.9f;
  sl.Color = Vector3f(0.0f, 1.0f, 1.0f);
  sl.Position = m_pGameCamera->GetPos();
  sl.Direction = m_pGameCamera->GetTarget();
  sl.Attenuation.Linear = 0.1f;
  sl.Cutoff = 10.0f;

  m_pEffect->SetSpotLights(1, &sl);

  Pipeline p;
  p.Scale(0.1f, 0.1f, 0.1f);
  p.Rotate(0.0f, m_scale, 0.0f);
  p.WorldPos(0.0f, 0.0f, 10.0f);
  p.SetCamera(m_pGameCamera->GetPos(), m_pGameCamera->GetTarget(), m_pGameCamera->GetUp());
  p.SetPerspectiveProj(m_persProjInfo);
  m_pEffect->SetWVP(p.GetWVPTrans());
  m_pEffect->SetWorldMatrix(p.GetWorldTrans());
  m_pEffect->SetDirectionalLight(m_directionalLight);
  m_pEffect->SetEyeWorldPos(m_pGameCamera->GetPos());
  m_pEffect->SetMatSpecularIntensity(0.0f);
  m_pEffect->SetMatSpecularPower(0);

  m_pMesh->Render();

  glutSwapBuffers();
}



void Tutorial22::KeyboardCB(OGLDEV_KEY OgldevKey, OGLDEV_KEY_STATE OgldevKeyState)
{
  switch (OgldevKey) {
  case OGLDEV_KEY_ESCAPE:
  case OGLDEV_KEY_q:
    GLUTBackendLeaveMainLoop();
    break;
  case OGLDEV_KEY_a:
    m_directionalLight.AmbientIntensity += 0.05f;
    break;
  case OGLDEV_KEY_s:
    m_directionalLight.AmbientIntensity -= 0.05f;
    break;
  case OGLDEV_KEY_z:
    m_directionalLight.DiffuseIntensity += 0.05f;
    break;
  case OGLDEV_KEY_x:
    m_directionalLight.DiffuseIntensity -= 0.05f;
    break;
  default:
    m_pGameCamera->OnKeyboard(OgldevKey);
  }
}


void Tutorial22::PassiveMouseCB(int x, int y)
{
  m_pGameCamera->OnMouse(x, y);
}
#endif
#endif
