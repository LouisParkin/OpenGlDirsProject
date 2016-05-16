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

#ifndef LIGHTING_TECHNIQUE_H // #1
#define LIGHTING_TECHNIQUE_H

#if __TUT_VERSION < 22

#include "technique.h"
#include "ogldev_math_3d.h"

#if __TUT_VERSION == 17 // #2
#include "ogldev_lights_common.h"
#elif __TUT_VERSION >= 18  && __TUT_VERSION <= 19 // #2
struct DirectionalLight {
  Vector3f Color;
  float AmbientIntensity;
  Vector3f Direction;
  float DiffuseIntensity;
};

#elif __TUT_VERSION >= 20 // #2

struct BaseLight {
  Vector3f Color;
  float AmbientIntensity;
  float DiffuseIntensity;

  BaseLight()
  {
    Color = Vector3f(0.0f, 0.0f, 0.0f);
    AmbientIntensity = 0.0f;
    DiffuseIntensity = 0.0f;
  }
};

struct DirectionalLight : public BaseLight {
  Vector3f Direction;

  DirectionalLight()
  {
    Direction = Vector3f(0.0f, 0.0f, 0.0f);
  }
};

struct PointLight : public BaseLight {
  Vector3f Position;

  struct {
    float Constant;
    float Linear;
    float Exp;
  } Attenuation;

  PointLight()
  {
    Position = Vector3f(0.0f, 0.0f, 0.0f);
    Attenuation.Constant = 1.0f;
    Attenuation.Linear = 0.0f;
    Attenuation.Exp = 0.0f;
  }
};

#endif // #2

#if __TUT_VERSION >= 21
struct SpotLight : public PointLight {
  Vector3f Direction;
  float Cutoff;

  SpotLight()
  {
    Direction = Vector3f(0.0f, 0.0f, 0.0f);
    Cutoff = 0.0f;
  }
};
#endif

class LightingTechnique : public Technique
{
public:

#if __TUT_VERSION >= 20 // #3
  static const unsigned int MAX_POINT_LIGHTS = 2;
#endif // #3
#if __TUT_VERSION >= 21 // #3
  static const unsigned int MAX_SPOT_LIGHTS = 2;
#endif

  LightingTechnique();

  virtual bool Init(char* pVSFileName, char* pFSFileName);

  void SetWVP(const Matrix4f& WVP);

#if __TUT_VERSION >= 18  // #4
  void SetWorldMatrix(const Matrix4f& WVP);
#endif // #4

  void SetTextureUnit(unsigned int TextureUnit);
  void SetDirectionalLight(const DirectionalLight& Light);

#if __TUT_VERSION >= 20 // #5
  void SetPointLights(unsigned int NumLights, const PointLight* pLights);
#endif // #5

#if __TUT_VERSION >= 21
  void SetSpotLights(unsigned int NumLights, const SpotLight* pLights);
#endif

#if __TUT_VERSION >= 19
  void SetMatSpecularIntensity(float Intensity);
  void SetMatSpecularPower(float Power);
  void SetEyeWorldPos(const Vector3f& EyeWorldPos);
#endif

private:

  GLuint m_WVPLocation;
#if __TUT_VERSION >= 18  // #6
  GLuint m_WorldMatrixLocation;
#endif // #6

  GLuint m_samplerLocation;

#if __TUT_VERSION >= 19 // #7
  GLuint m_eyeWorldPosLocation;
  GLuint m_matSpecularIntensityLocation;
  GLuint m_matSpecularPowerLocation;
#endif // #7

#if __TUT_VERSION >= 20 // #8
  GLuint m_numPointLightsLocation;
#endif // #8

#if __TUT_VERSION >= 21
  GLuint m_numSpotLightsLocation;
#endif

#if __TUT_VERSION == 17 // #9
  GLuint m_dirLightColorLocation;
  GLuint m_dirLightAmbientIntensityLocation;
#elif __TUT_VERSION >= 18   // #9
  struct {
    GLuint Color;
    GLuint AmbientIntensity;
    GLuint Direction;
    GLuint DiffuseIntensity;
  } m_dirLightLocation;
#endif // #9

#if __TUT_VERSION >= 20 // #10

  struct {
    GLuint Color;
    GLuint AmbientIntensity;
    GLuint DiffuseIntensity;
    GLuint Position;
    struct {
      GLuint Constant;
      GLuint Linear;
      GLuint Exp;
    } Atten;
  } m_pointLightsLocation[MAX_POINT_LIGHTS];

#endif // #10

#if __TUT_VERSION >= 21
  struct {
    GLuint Color;
    GLuint AmbientIntensity;
    GLuint DiffuseIntensity;
    GLuint Position;
    GLuint Direction;
    GLuint Cutoff;
    struct {
      GLuint Constant;
      GLuint Linear;
      GLuint Exp;
    } Atten;
  } m_spotLightsLocation[MAX_SPOT_LIGHTS];
#endif
};

#endif

#endif  /* LIGHTING_TECHNIQUE_H */ // #1
