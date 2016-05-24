/*

  Copyright 2011 Etay Meiri

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#if __TUT_VERSION < 22
#include "lighting_technique.h"

#if __TUT_VERSION >= 20
  #include <limits.h>
  #include <string.h>

  #if __TUT_VERSION >= 21
    #include "ogldev_math_3d.h"
  #endif

  #include "ogldev_util.h"
#endif


LightingTechnique::LightingTechnique()
{
}

bool LightingTechnique::Init(char* pVSFileName, char* pFSFileName)
{
  if (!Technique::Init(pVSFileName, pFSFileName)) {
    return false;
  }

  if (!AddShader(GL_VERTEX_SHADER, pVSFileName)) {
    return false;
  }

  if (!AddShader(GL_FRAGMENT_SHADER, pFSFileName)) {
    return false;
  }

  if (!Finalize()) {
    return false;
  }

  m_WorldViewProjectionLocation = GetUniformLocation("gWVP");


#if __TUT_VERSION >= 18
  m_WorldMatrixLocation = GetUniformLocation("gWorld");
#endif

  m_samplerLocation = GetUniformLocation("gSampler");

#if __TUT_VERSION >= 19
  m_eyeWorldPosLocation = GetUniformLocation("gEyeWorldPos");
#endif

#if __TUT_VERSION == 17
  m_dirLightColorLocation = GetUniformLocation("gDirectionalLight.Color");
  m_dirLightAmbientIntensityLocation = GetUniformLocation("gDirectionalLight.AmbientIntensity");

  if (m_dirLightAmbientIntensityLocation == 0xFFFFFFFF ||
      m_WorldViewProjectionLocation == 0xFFFFFFFF ||
      m_samplerLocation == 0xFFFFFFFF ||
      m_dirLightColorLocation == 0xFFFFFFFF) {
    return false;
  }

  return true;
#endif

#if __TUT_VERSION >= 18
  m_dirLightLocation.Direction = GetUniformLocation("gDirectionalLight.Direction");

#if __TUT_VERSION >= 18 && __TUT_VERSION <= 19

  m_dirLightLocation.Color = GetUniformLocation("gDirectionalLight.Color");
  m_dirLightLocation.AmbientIntensity = GetUniformLocation("gDirectionalLight.AmbientIntensity");
  m_dirLightLocation.DiffuseIntensity = GetUniformLocation("gDirectionalLight.DiffuseIntensity");
#endif
#if __TUT_VERSION >= 20
  m_dirLightLocation.Color = GetUniformLocation("gDirectionalLight.Base.Color");
  m_dirLightLocation.AmbientIntensity = GetUniformLocation("gDirectionalLight.Base.AmbientIntensity");
  m_dirLightLocation.DiffuseIntensity = GetUniformLocation("gDirectionalLight.Base.DiffuseIntensity");
  m_numPointLightsLocation = GetUniformLocation("gNumPointLights");
#endif

#if __TUT_VERSION >= 21
  m_numSpotLightsLocation = GetUniformLocation("gNumSpotLights");

  if (m_dirLightLocation.AmbientIntensity == INVALID_UNIFORM_LOCATION ||
      m_WorldViewProjectionLocation == INVALID_UNIFORM_LOCATION ||
      m_WorldMatrixLocation == INVALID_UNIFORM_LOCATION ||
      m_samplerLocation == INVALID_UNIFORM_LOCATION ||
      m_eyeWorldPosLocation == INVALID_UNIFORM_LOCATION ||
      m_dirLightLocation.Color == INVALID_UNIFORM_LOCATION ||
      m_dirLightLocation.DiffuseIntensity == INVALID_UNIFORM_LOCATION ||
      m_dirLightLocation.Direction == INVALID_UNIFORM_LOCATION ||
      m_matSpecularIntensityLocation == INVALID_UNIFORM_LOCATION ||
      m_matSpecularPowerLocation == INVALID_UNIFORM_LOCATION ||
      m_numPointLightsLocation == INVALID_UNIFORM_LOCATION ||
      m_numSpotLightsLocation == INVALID_UNIFORM_LOCATION) {
    return false;
  }
#endif

#if __TUT_VERSION >= 19
  m_matSpecularIntensityLocation = GetUniformLocation("gMatSpecularIntensity");
  m_matSpecularPowerLocation = GetUniformLocation("gSpecularPower");
#endif

#if __TUT_VERSION <= 19
  if (m_dirLightLocation.AmbientIntensity == 0xFFFFFFFF ||
      m_WorldViewProjectionLocation == 0xFFFFFFFF ||
      m_WorldMatrixLocation == 0xFFFFFFFF ||
      m_samplerLocation == 0xFFFFFFFF ||

#if __TUT_VERSION == 19
      m_eyeWorldPosLocation == 0xFFFFFFFF ||
      m_matSpecularIntensityLocation == 0xFFFFFFFF ||
      m_matSpecularPowerLocation == 0xFFFFFFFF ||
#endif

      m_dirLightLocation.Color == 0xFFFFFFFF ||
      m_dirLightLocation.DiffuseIntensity == 0xFFFFFFFF ||
      m_dirLightLocation.Direction == 0xFFFFFFFF) {
    return false;
  }

  return true;
#elif __TUT_VERSION >= 20
  for (unsigned int i = 0 ; i < ARRAY_SIZE_IN_ELEMENTS(m_pointLightsLocation) ; i++) {
    char Name[128];
    memset(Name, 0, sizeof(Name));
    SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Base.Color", i);
    m_pointLightsLocation[i].Color = GetUniformLocation(Name);

    SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Base.AmbientIntensity", i);
    m_pointLightsLocation[i].AmbientIntensity = GetUniformLocation(Name);

    SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Position", i);
    m_pointLightsLocation[i].Position = GetUniformLocation(Name);

    SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Base.DiffuseIntensity", i);
    m_pointLightsLocation[i].DiffuseIntensity = GetUniformLocation(Name);

    SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Atten.Constant", i);
    m_pointLightsLocation[i].Atten.Constant = GetUniformLocation(Name);

    SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Atten.Linear", i);
    m_pointLightsLocation[i].Atten.Linear = GetUniformLocation(Name);

    SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Atten.Exp", i);
    m_pointLightsLocation[i].Atten.Exp = GetUniformLocation(Name);

    if (m_pointLightsLocation[i].Color == INVALID_UNIFORM_LOCATION ||
        m_pointLightsLocation[i].AmbientIntensity == INVALID_UNIFORM_LOCATION ||
        m_pointLightsLocation[i].Position == INVALID_UNIFORM_LOCATION ||
        m_pointLightsLocation[i].DiffuseIntensity == INVALID_UNIFORM_LOCATION ||
        m_pointLightsLocation[i].Atten.Constant == INVALID_UNIFORM_LOCATION ||
        m_pointLightsLocation[i].Atten.Linear == INVALID_UNIFORM_LOCATION ||
        m_pointLightsLocation[i].Atten.Exp == INVALID_UNIFORM_LOCATION) {
      return false;
    }
  }

#if __TUT_VERSION == 20
  if (m_dirLightLocation.AmbientIntensity == INVALID_UNIFORM_LOCATION ||
      m_WorldViewProjectionLocation == INVALID_UNIFORM_LOCATION ||
      m_WorldMatrixLocation == INVALID_UNIFORM_LOCATION ||
      m_samplerLocation == INVALID_UNIFORM_LOCATION ||
      m_eyeWorldPosLocation == INVALID_UNIFORM_LOCATION ||
      m_dirLightLocation.Color == INVALID_UNIFORM_LOCATION ||
      m_dirLightLocation.DiffuseIntensity == INVALID_UNIFORM_LOCATION ||
      m_dirLightLocation.Direction == INVALID_UNIFORM_LOCATION ||
      m_matSpecularIntensityLocation == INVALID_UNIFORM_LOCATION ||
      m_matSpecularPowerLocation == INVALID_UNIFORM_LOCATION ||
      m_numPointLightsLocation == INVALID_UNIFORM_LOCATION) {
    return false;
  }
#endif

#if __TUT_VERSION >= 21
  for (unsigned int i = 0 ; i < ARRAY_SIZE_IN_ELEMENTS(m_spotLightsLocation) ; i++) {
    char Name[128];
    memset(Name, 0, sizeof(Name));
    SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Base.Color", i);
    m_spotLightsLocation[i].Color = GetUniformLocation(Name);

    SNPRINTF(Name, sizeof(Name), "g/home/lparkin/Projects/S3/OpenGlDirsProject/LearnOpenGL-nonQt/Project/ContentSpotLights[%d].Base.Base.AmbientIntensity", i);
    m_spotLightsLocation[i].AmbientIntensity = GetUniformLocation(Name);

    SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Position", i);
    m_spotLightsLocation[i].Position = GetUniformLocation(Name);

    SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Direction", i);
    m_spotLightsLocation[i].Direction = GetUniformLocation(Name);

    SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Cutoff", i);
    m_spotLightsLocation[i].Cutoff = GetUniformLocation(Name);

    SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Base.DiffuseIntensity", i);
    m_spotLightsLocation[i].DiffuseIntensity = GetUniformLocation(Name);

    SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Atten.Constant", i);
    m_spotLightsLocation[i].Atten.Constant = GetUniformLocation(Name);

    SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Atten.Linear", i);
    m_spotLightsLocation[i].Atten.Linear = GetUniformLocation(Name);

    SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Atten.Exp", i);
    m_spotLightsLocation[i].Atten.Exp = GetUniformLocation(Name);

    if (m_spotLightsLocation[i].Color == INVALID_UNIFORM_LOCATION ||
        m_spotLightsLocation[i].AmbientIntensity == INVALID_UNIFORM_LOCATION ||
        m_spotLightsLocation[i].Position == INVALID_UNIFORM_LOCATION ||
        m_spotLightsLocation[i].Direction == INVALID_UNIFORM_LOCATION ||
        m_spotLightsLocation[i].Cutoff == INVALID_UNIFORM_LOCATION ||
        m_spotLightsLocation[i].DiffuseIntensity == INVALID_UNIFORM_LOCATION ||
        m_spotLightsLocation[i].Atten.Constant == INVALID_UNIFORM_LOCATION ||
        m_spotLightsLocation[i].Atten.Linear == INVALID_UNIFORM_LOCATION ||
        m_spotLightsLocation[i].Atten.Exp == INVALID_UNIFORM_LOCATION) {
      return false;
    }
  }
#endif

  return true;

#endif

#endif
}

void LightingTechnique::SetWorldViewProjection(const Matrix4f& WorldViewProjection)
{
  glUniformMatrix4fv(m_WorldViewProjectionLocation, 1, GL_TRUE, (const GLfloat*)WorldViewProjection.m);
}

#if __TUT_VERSION >= 18

void LightingTechnique::SetWorldMatrix(const Matrix4f& WorldInverse)
{
  glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, (const GLfloat*)WorldInverse.m);
}

#endif


void LightingTechnique::SetTextureUnit(unsigned int TextureUnit)
{
  glUniform1i(m_samplerLocation, TextureUnit);
}


void LightingTechnique::SetDirectionalLight(const DirectionalLight& Light)
{
#if __TUT_VERSION == 17
  glUniform3f(m_dirLightColorLocation, Light.Color.x, Light.Color.y, Light.Color.z);
  glUniform1f(m_dirLightAmbientIntensityLocation, Light.AmbientIntensity);
#elif __TUT_VERSION >= 18 && __TUT_VERSION <= 19
  glUniform3f(m_dirLightLocation.Color, Light.Color.x, Light.Color.y, Light.Color.z);
  glUniform1f(m_dirLightLocation.AmbientIntensity, Light.AmbientIntensity);
  Vector3f Direction = Light.Direction;
  Direction.Normalize();
  glUniform3f(m_dirLightLocation.Direction, Direction.x, Direction.y, Direction.z);
  glUniform1f(m_dirLightLocation.DiffuseIntensity, Light.DiffuseIntensity);
#endif

}


#if __TUT_VERSION >= 19

void LightingTechnique::SetEyeWorldPos(const Vector3f& EyeWorldPos)
{
  glUniform3f(m_eyeWorldPosLocation, EyeWorldPos.x, EyeWorldPos.y, EyeWorldPos.z);
}

void LightingTechnique::SetMatSpecularIntensity(float Intensity)
{
  glUniform1f(m_matSpecularIntensityLocation, Intensity);
}

void LightingTechnique::SetMatSpecularPower(float Power)
{
  glUniform1f(m_matSpecularPowerLocation, Power);
}

#endif

#if __TUT_VERSION >= 20
void LightingTechnique::SetPointLights(unsigned int NumLights, const PointLight* pLights)
{
  glUniform1i(m_numPointLightsLocation, NumLights);

  for (unsigned int i = 0 ; i < NumLights ; i++) {
    glUniform3f(m_pointLightsLocation[i].Color, pLights[i].Color.x, pLights[i].Color.y, pLights[i].Color.z);
    glUniform1f(m_pointLightsLocation[i].AmbientIntensity, pLights[i].AmbientIntensity);
    glUniform1f(m_pointLightsLocation[i].DiffuseIntensity, pLights[i].DiffuseIntensity);
    glUniform3f(m_pointLightsLocation[i].Position, pLights[i].Position.x, pLights[i].Position.y, pLights[i].Position.z);
    glUniform1f(m_pointLightsLocation[i].Atten.Constant, pLights[i].Attenuation.Constant);
    glUniform1f(m_pointLightsLocation[i].Atten.Linear, pLights[i].Attenuation.Linear);
    glUniform1f(m_pointLightsLocation[i].Atten.Exp, pLights[i].Attenuation.Exp);
  }
}
#endif
#if __TUT_VERSION >= 21
void LightingTechnique::SetSpotLights(unsigned int NumLights, const SpotLight* pLights)
{
  glUniform1i(m_numSpotLightsLocation, NumLights);

  for (unsigned int i = 0 ; i < NumLights ; i++) {
    glUniform3f(m_spotLightsLocation[i].Color, pLights[i].Color.x, pLights[i].Color.y, pLights[i].Color.z);
    glUniform1f(m_spotLightsLocation[i].AmbientIntensity, pLights[i].AmbientIntensity);
    glUniform1f(m_spotLightsLocation[i].DiffuseIntensity, pLights[i].DiffuseIntensity);
    glUniform3f(m_spotLightsLocation[i].Position,  pLights[i].Position.x, pLights[i].Position.y, pLights[i].Position.z);
    Vector3f Direction = pLights[i].Direction;
    Direction.Normalize();
    glUniform3f(m_spotLightsLocation[i].Direction, Direction.x, Direction.y, Direction.z);
    glUniform1f(m_spotLightsLocation[i].Cutoff, cosf(ToRadian(pLights[i].Cutoff)));
    glUniform1f(m_spotLightsLocation[i].Atten.Constant, pLights[i].Attenuation.Constant);
    glUniform1f(m_spotLightsLocation[i].Atten.Linear,   pLights[i].Attenuation.Linear);
    glUniform1f(m_spotLightsLocation[i].Atten.Exp,      pLights[i].Attenuation.Exp);
  }
}
#endif
#endif
