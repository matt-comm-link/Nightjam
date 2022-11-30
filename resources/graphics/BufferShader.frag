#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec4 vColor;

uniform sampler2D buffer;

void main()
{
    vec4 sampled = texture(buffer, TexCoords);
    FragColor = vColor * texture(buffer, TexCoords);
}