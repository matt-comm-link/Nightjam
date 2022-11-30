#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec4 aColor;

out vec2 TexCoords;
out vec4 vColor;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    TexCoords = aTexCoords;
    vColor = aColor;
    
    gl_Position = model * vec4(aPos.x, aPos.y, aPos.z, 1.0f);
}