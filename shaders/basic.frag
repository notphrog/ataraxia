#version 460 core


out vec4 FragColor;

in vec3 otherColor;
in vec2 TexCoord;

//uniform vec4 customColor;
uniform sampler2D ourTexture;

void main() {
    // FragColor = customColor; // this makes it controlled by the main.cpp
    //FragColor = vec4(otherColor, 1.0);
    FragColor = texture(ourTexture, TexCoord); // * vec4(otherColor, 1.0);
}