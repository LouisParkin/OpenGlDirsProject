#include "Tutorial18.h"

#ifdef __TUT_VERSION
#if __TUT_VERSION == 18

bool Tutorial18::Init(char* pVSFileName, char* pFSFileName)
{
  Vector3f Pos(0.0f, 0.0f, -3.0f);
  Vector3f Target(0.0f, 0.0f, 1.0f);
  Vector3f Up(0.0, 1.0f, 0.0f);

  m_pGameCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT, Pos, Target, Up);

  unsigned int Indices[] = { 0, 3, 1,
                             1, 3, 2,
                             2, 3, 0,
                             1, 2, 0
                           };

  CreateIndexBuffer(Indices, sizeof(Indices));
  CreateVertexBuffer(Indices, ARRAY_SIZE_IN_ELEMENTS(Indices));

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

void Tutorial18::Run()
{
  GLUTBackendRun(this);
}

void Tutorial18::RenderSceneCB()
{
  m_pGameCamera->OnRender();

  glClear(GL_COLOR_BUFFER_BIT);

  m_scale += 0.1f;

  Pipeline p;
  p.Rotate(0.0f, m_scale, 0.0f);
  p.WorldPos(0.0f, 0.0f, 1.0f);
  p.SetCamera(m_pGameCamera->GetPos(), m_pGameCamera->GetTarget(), m_pGameCamera->GetUp());
  p.SetPerspectiveProj(m_persProjInfo);
  m_pEffect->SetWVP(p.GetWVPTrans());
  const Matrix4f& WorldTransformation = p.GetWorldTrans();
  m_pEffect->SetWorldMatrix(WorldTransformation);
  m_pEffect->SetDirectionalLight(m_directionalLight);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
  m_pTexture->Bind(GL_TEXTURE0);
  glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);

  glutSwapBuffers();
}

void Tutorial18::KeyboardCB(OGLDEV_KEY OgldevKey, OGLDEV_KEY_STATE OgldevKeyState)
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
  }
}

void Tutorial18::PassiveMouseCB(int x, int y)
{
  m_pGameCamera->OnMouse(x, y);
}

void Tutorial18::CreateVertexBuffer(const unsigned int* pIndices, unsigned int IndexCount)
{
  Vertex Vertices[4] = { Vertex(Vector3f(-1.0f, -1.0f, 0.5773f), Vector2f(0.0f, 0.0f)),
                         Vertex(Vector3f(0.0f, -1.0f, -1.15475f), Vector2f(0.5f, 0.0f)),
                         Vertex(Vector3f(1.0f, -1.0f, 0.5773f),  Vector2f(1.0f, 0.0f)),
                         Vertex(Vector3f(0.0f, 1.0f, 0.0f),      Vector2f(0.5f, 1.0f))
                       };

  unsigned int VertexCount = ARRAY_SIZE_IN_ELEMENTS(Vertices);

  CalcNormals(pIndices, IndexCount, Vertices, VertexCount);

  glGenBuffers(1, &m_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

void Tutorial18::CreateIndexBuffer(const unsigned int* pIndices, unsigned int SizeInBytes)
{
  glGenBuffers(1, &m_IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, SizeInBytes, pIndices, GL_STATIC_DRAW);
}

void Tutorial18::CalcNormals(const unsigned int* pIndices, unsigned int IndexCount, Vertex* pVertices, unsigned int VertexCount)
{
  // Accumulate each triangle normal into each of the triangle vertices
  for (unsigned int i = 0 ; i < IndexCount ; i += 3) {
    unsigned int Index0 = pIndices[i];
    unsigned int Index1 = pIndices[i + 1];
    unsigned int Index2 = pIndices[i + 2];
    Vector3f v1 = pVertices[Index1].m_pos - pVertices[Index0].m_pos;
    Vector3f v2 = pVertices[Index2].m_pos - pVertices[Index0].m_pos;
    Vector3f Normal = v1.Cross(v2);
    Normal.Normalize();

    pVertices[Index0].m_normal += Normal;
    pVertices[Index1].m_normal += Normal;
    pVertices[Index2].m_normal += Normal;
  }

  // Normalize all the vertex normals
  for (unsigned int i = 0 ; i < VertexCount ; i++) {
    pVertices[i].m_normal.Normalize();
  }
}

#endif
#endif
