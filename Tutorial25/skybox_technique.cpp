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

#include <limits.h>
#include <string.h>

#include "skybox_technique.h"
#include "ogldev_util.h"


SkyboxTechnique::SkyboxTechnique()
{   
}

bool SkyboxTechnique::Init(char* pVSFileName, char* pFSFileName)
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
    m_textureLocation = GetUniformLocation("gCubemapTexture");
 
    if (m_WorldViewProjectionLocation == INVALID_UNIFORM_LOCATION ||
        m_textureLocation == INVALID_UNIFORM_LOCATION) {
        return false;
    }

    return true;
}


void SkyboxTechnique::SetWorldViewProjection(const Matrix4f& WorldViewProjection)
{
    glUniformMatrix4fv(m_WorldViewProjectionLocation, 1, GL_TRUE, (const GLfloat*)WorldViewProjection.m);    
}


void SkyboxTechnique::SetTextureUnit(unsigned int TextureUnit)
{
    glUniform1i(m_textureLocation, TextureUnit);
}


