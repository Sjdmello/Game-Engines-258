#version 450 core

in vec3 Normal;
in vec3 TextCoords;
in vec3 Colour;

out vec4 fcolour;


void main(){
fcolour = vec4 (Colour,1.0);
}