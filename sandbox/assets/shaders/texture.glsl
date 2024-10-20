#type vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

out vec2 vTexCoord;

uniform mat4 uViewProjection;
uniform mat4 uTransform;

void main() {
    vTexCoord = texCoord;
    gl_Position = uViewProjection * uTransform * vec4(position, 1.0);
}

#type pixel
#version 330 core

out vec4 FragColor;

in vec2 vTexCoord;

uniform sampler2D u_texture;

void main() {
    FragColor = texture(u_texture, vTexCoord);
}