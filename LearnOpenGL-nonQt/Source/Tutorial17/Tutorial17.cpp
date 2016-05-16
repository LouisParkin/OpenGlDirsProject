#include "Tutorial17.h"

#ifdef __TUT_VERSION
#if __TUT_VERSION == 17
bool Tutorial17::Init(char* pVSFileName, char* pFSFileName)
{
  m_pGameCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT);

  CreateVertexBuffer();
  CreateIndexBuffer();

  m_pEffect = new LightingTechnique();

  if (!m_pEffect->Init(pVSFileName, pFSFileName)) {
    return false;
  }

  m_pEffect->Enable();

  m_pEffect->SetTextureUnit(0);

  m_pTexture = new Texture(GL_TEXTURE_2D, "/home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Project/Content/test.png");

  if (!m_pTexture->Load()) {
    return false;
  }

  return true;
}

void Tutorial17::Run()
{
  GLUTBackendRun(this);
}

void Tutorial17::RenderSceneCB()
{
  m_pGameCamera->OnRender();

  glClear(GL_COLOR_BUFFER_BIT);

  m_scale += 0.1f;

  Pipeline p;
  p.Rotate(0.0f, m_scale, 0.0f);
  p.WorldPos(0.0f, 0.0f, 3.0f);
  p.SetCamera(m_pGameCamera->GetPos(), m_pGameCamera->GetTarget(), m_pGameCamera->GetUp());
  p.SetPerspectiveProj(m_persProjInfo);
  m_pEffect->SetWVP(p.GetWVPTrans());
  m_pEffect->SetDirectionalLight(m_directionalLight);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
  m_pTexture->Bind(GL_TEXTURE0);
  glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);

  glutSwapBuffers();
}

void Tutorial17::KeyboardCB(OGLDEV_KEY OgldevKey, OGLDEV_KEY_STATE OgldevKeyState)
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
  }
}

void Tutorial17::PassiveMouseCB(int x, int y)
{
  m_pGameCamera->OnMouse(x, y);
}

void Tutorial17::CreateVertexBuffer()
{

  Vertex Vertices[4] = { Vertex(Vector3f(-1.0f, -1.0f, 0.5773f), Vector2f(0.0f, 0.0f)),
                         Vertex(Vector3f(0.0f, -1.0f, -1.15475f), Vector2f(0.5f, 0.0f)),
                         Vertex(Vector3f(1.0f, -1.0f, 0.5773f),  Vector2f(1.0f, 0.0f)),
                         Vertex(Vector3f(0.0f, 1.0f, 0.0f),      Vector2f(0.5f, 1.0f))
                       };

  glGenBuffers(1, &m_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

}

void Tutorial17::CreateIndexBuffer()
{
  unsigned int Indices[] = { 0, 3, 1,
                             1, 3, 2,
                             2, 3, 0,
                             1, 2, 0
                           };

  glGenBuffers(1, &m_IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}
#endif
#endif
