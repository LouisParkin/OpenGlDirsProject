#include "Tutorial23.h"

#ifdef __TUT_VERSION
#if __TUT_VERSION == 23

bool Tutorial23::Init(char* pVSFileName, char* pFSFileName)
{
  if (!m_shadowMapFBO.Init(WINDOW_WIDTH, WINDOW_HEIGHT)) {
    return false;
  }

  m_pGameCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT/*, Pos, Target, Up*/);

  m_pShadowMapTech = new ShadowMapTechnique();

  if (!m_pShadowMapTech->Init(pVSFileName, pFSFileName)) {
    printf("Error initializing the shadow map technique\n");
    return false;
  }

  m_pShadowMapTech->Enable();

  m_pQuad = new Mesh();

  if (!m_pQuad->LoadMesh("/home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Project/Content/quad.obj")) {
    return false;
  }

  m_pMesh = new Mesh();

  return m_pMesh->LoadMesh("/home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Project/Content/phoenix_ugv.md2");
}

void Tutorial23::Run()
{
  GLUTBackendRun(this);
}

void Tutorial23::RenderSceneCB()
{
  m_pGameCamera->OnRender();
  m_scale += 0.05f;

  ShadowMapPass();
  RenderPass();

  glutSwapBuffers();
}

void Tutorial23::ShadowMapPass()
{
  m_shadowMapFBO.BindForWriting();

  glClear(GL_DEPTH_BUFFER_BIT);

  Pipeline p;
  p.Scale(0.1f, 0.1f, 0.1f);
  p.Rotate(0.0f, m_scale, 0.0f);
  p.WorldPos(0.0f, 0.0f, 5.0f);
  p.SetCamera(m_spotLight.Position, m_spotLight.Direction, Vector3f(0.0f, 1.0f, 0.0f));
  p.SetPerspectiveProj(m_persProjInfo);
  m_pShadowMapTech->SetWVP(p.GetWVPTrans());
  m_pMesh->Render();

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Tutorial23::RenderPass()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  m_pShadowMapTech->SetTextureUnit(0);
  m_shadowMapFBO.BindForReading(GL_TEXTURE0);

  Pipeline p;
  p.Scale(5.0f, 5.0f, 5.0f);
  p.WorldPos(0.0f, 0.0f, 10.0f);
  p.SetCamera(m_pGameCamera->GetPos(), m_pGameCamera->GetTarget(), m_pGameCamera->GetUp());
  p.SetPerspectiveProj(m_persProjInfo);
  m_pShadowMapTech->SetWVP(p.GetWVPTrans());
  m_pQuad->Render();
}


void Tutorial23::KeyboardCB(OGLDEV_KEY OgldevKey, OGLDEV_KEY_STATE )
{
  switch (OgldevKey) {
  case OGLDEV_KEY_ESCAPE:
  case OGLDEV_KEY_q:
    GLUTBackendLeaveMainLoop();
    break;
  default:
    m_pGameCamera->OnKeyboard(OgldevKey);
  }
}


void Tutorial23::PassiveMouseCB(int x, int y)
{
  m_pGameCamera->OnMouse(x, y);
}
#endif
#endif
