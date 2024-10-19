#type vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord;

out vec4 vertexColor;
out vec2 texCoord;

uniform mat4 u_viewProjection;
uniform mat4 u_transform;

void main() {
    gl_Position = u_viewProjection * u_transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexColor = aColor;
    texCoord = aTexCoord;
}

#type pixel
#version 330 core

out vec4 FragColor;

in vec4 vertexColor;
in vec2 texCoord;

uniform sampler2D u_texture;
uniform vec3 u_color;

void main() {
    FragColor = texture(u_texture, texCoord) * vec4(u_color, 1.0);
}