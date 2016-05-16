#include "Tutorial21.h"

#ifdef __TUT_VERSION
#if __TUT_VERSION == 21

bool Tutorial21::Init(char* pVSFileName, char* pFSFileName)
{
  Vector3f Pos(5.0f, 1.0f, -3.0f);
  Vector3f Target(0.0f, 0.0f, 1.0f);
  Vector3f Up(0.0, 1.0f, 0.0f);

  m_pGameCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT, Pos, Target, Up);

  CreateVertexBuffer();

  m_pEffect = new LightingTechnique();

  if (!m_pEffect->Init(pVSFileName, pFSFileName)) {
    printf("Error initializing the lighting technique\n");
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

void Tutorial21::Run()
{
  GLUTBackendRun(this);
}

void Tutorial21::RenderSceneCB()
{
  m_scale += 0.0057f;

  m_pGameCamera->OnRender();

  glClear(GL_COLOR_BUFFER_BIT);

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

  SpotLight sl[2];
  sl[0].DiffuseIntensity = 0.9f;
  sl[0].Color = Vector3f(0.0f, 1.0f, 1.0f);
  sl[0].Position = m_pGameCamera->GetPos();
  sl[0].Direction = m_pGameCamera->GetTarget();
  sl[0].Attenuation.Linear = 0.1f;
  sl[0].Cutoff = 10.0f;

  sl[1].DiffuseIntensity = 0.9f;
  sl[1].Color = Vector3f(1.0f, 1.0f, 1.0f);
  sl[1].Position = Vector3f(5.0f, 3.0f, 10.0f);
  sl[1].Direction = Vector3f(0.0f, -1.0f, 0.0f);
  sl[1].Attenuation.Linear = 0.1f;
  sl[1].Cutoff = 20.0f;
  m_pEffect->SetSpotLights(2, sl);

  Pipeline p;
  p.WorldPos(0.0f, 0.0f, 1.0f);
  p.SetCamera(m_pGameCamera->GetPos(), m_pGameCamera->GetTarget(), m_pGameCamera->GetUp());
  p.SetPerspectiveProj(m_persProjInfo);
  m_pEffect->SetWVP(p.GetWVPTrans());
  const Matrix4f& WorldTransformation = p.GetWorldTrans();
  m_pEffect->SetWorldMatrix(WorldTransformation);
  m_pEffect->SetDirectionalLight(m_directionalLight);
  m_pEffect->SetEyeWorldPos(m_pGameCamera->GetPos());
  m_pEffect->SetMatSpecularIntensity(0.0f);
  m_pEffect->SetMatSpecularPower(0);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);
  m_pTexture->Bind(GL_TEXTURE0);
  glDrawArrays(GL_TRIANGLES, 0, 6);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);

  glutSwapBuffers();
}

void Tutorial21::KeyboardCB(OGLDEV_KEY OgldevKey, OGLDEV_KEY_STATE OgldevKeyState)
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

void Tutorial21::PassiveMouseCB(int x, int y)
{
  m_pGameCamera->OnMouse(x, y);
}

void Tutorial21::CreateVertexBuffer()
{
  const Vector3f Normal = Vector3f(0.0, 1.0f, 0.0f);

  Vertex Vertices[6] = {
    Vertex(Vector3f(0.0f, 0.0f, 0.0f),             Vector2f(0.0f, 0.0f), Normal),
    Vertex(Vector3f(0.0f, 0.0f, FieldDepth),       Vector2f(0.0f, 1.0f), Normal),
    Vertex(Vector3f(FieldWidth, 0.0f, 0.0f),       Vector2f(1.0f, 0.0f), Normal),

    Vertex(Vector3f(FieldWidth, 0.0f, 0.0f),       Vector2f(1.0f, 0.0f), Normal),
    Vertex(Vector3f(0.0f, 0.0f, FieldDepth),       Vector2f(0.0f, 1.0f), Normal),
    Vertex(Vector3f(FieldWidth, 0.0f, FieldDepth), Vector2f(1.0f, 1.0f), Normal)
  };

  glGenBuffers(1, &m_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

#endif
#endif
