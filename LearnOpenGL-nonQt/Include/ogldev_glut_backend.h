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

#ifndef GLUT_BACKEND_H
#define	GLUT_BACKEND_H

#include "ogldev_types.h"
#include "ogldev_callbacks.h"

void GLUTBackendInit(int argc, char** argv, bool WithDepth, bool WithStencil);


bool GLUTBackendCreateWindow(uint Width, uint Height, bool isFullScreen, const char* pTitle);

void GLUTBackendRun(ICallbacks* pCallbacks);

void GLUTBackendSwapBuffers();

void GLUTBackendLeaveMainLoop();

//static void IdleCB();
//static void RenderSceneCB();
//static void PassiveMouseCB(int x, int y);
//static void KeyboardCB(unsigned char Key, int x, int y);
//static void SpecialKeyboardCB(int Key, int x, int y);
//static OGLDEV_MOUSE GLUTMouseToOGLDEVMouse(uint Button);
//static void MouseCB(int Button, int State, int x, int y);
struct Attempt
{
  static void InitCallbacks();
};

OGLDEV_KEY GLUTKeyToOGLDEVKey(uint Key);

#endif	/* GLUT_BACKEND_H */

