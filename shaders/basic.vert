#version 460 core


layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

//out vec4 vertexColor; // and then sent to fragment shader
out vec3 otherColor;
out vec2 TexCoord;

uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
   gl_Position = projection * view * model * vec4(aPos, 1.0);
   otherColor = aColor;

   // otherColor = aColor;
   // vertexColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
   TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
}