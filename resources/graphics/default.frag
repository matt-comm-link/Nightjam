#version 330 core



out vec4 FragColor;

in vec2 TexCoords;
in vec4 vColor;
uniform sampler2D texture_diffuse1;


void main()
{
    //FragColor = vec4(1,1,1,1);
    FragColor = vColor * texture(texture_diffuse1, TexCoords);
    //FragColor = vColor;
}