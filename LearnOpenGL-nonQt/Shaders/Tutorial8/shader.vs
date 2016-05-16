#version 330

layout (location = 0) in vec3 Position;

uniform mat4 gWorld;
uniform float gScale;

void main()
{
    gl_Position = gWorld * vec4(gScale * Position.x, gScale * Position.y, Position.z, 1.0);
}
