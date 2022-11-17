#version 330

in vec4 vPosition;
in vec2 texCoord;
in vec3 vNormal;

out vec2 tex;

out vec3 normal;
out vec4 eye;

uniform mat4 uModelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 viewMatrix;

void main (void) 
{
  gl_Position = uModelViewMatrix * vPosition;
  normal = (normalMatrix * normalize(vNormal)); 
  eye = -gl_Position; 
  tex = texCoord;
}