#version 330

layout(location = 0 )in vec4 vPosition;
layout(location = 1 )in vec4 vColor;
out vec4 vColorOut;
uniform mat4 uModelViewProjectMatrix;


void main (void)
{
  gl_Position = uModelViewProjectMatrix * vPosition;
  vColorOut= vColor;
}
