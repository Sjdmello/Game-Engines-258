#version 450 core

layout(location =0) in vec3 position;
layout(location =1) in vec3 normal;
layout(location =2) in vec2 textCoords;
layout(location =3) in vec3 colour;

out vec3 Normal;
out vec2 TextCoords;
out vec3 Colour;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
gl_Position = projection* view *model * vec4(position,1.0f);
Colour = colour;
TextCoords = textCoords;
Normal = mat3(transpose(inverse(model)))*normal;
FragPos = vec3(model * vec4(position,1.0f));
}