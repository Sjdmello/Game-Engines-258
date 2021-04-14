#version 450 core

in vec3 Normal;
in vec2 TextCoords;
in vec3 Colour;
in vec3 FragPos;

uniform sampler2D inputTexture;
uniform vec3 CameraPos;


out vec4 fcolour;

struct Light {
vec3 lightPos;
float amb;
float diff;
float spec;
vec3 lightColour;
};

uniform Light light;

void main(){


vec3 amb = light.amb * texture(inputTexture,TextCoords).rgb * light.lightColour;

vec3 norm = normalize(Normal);
vec3 lightDir = normalize(light.lightPos - FragPos);
float diff = max(dot(norm,lightDir),0.0);
vec3 diffuse = (diff*light.diff)*texture(inputTexture,TextCoords).rgb*light.lightColour;

vec3 viewDir = normalize(CameraPos - FragPos);
vec3 reflectDir = reflect(-lightDir,norm);
float spec = pow(max(dot(viewDir,reflectDir),0.0),32);
vec3 specular = (spec*light.spec)*light.lightColour;

vec3 result = amb + diffuse + specular;

fcolour = vec4(result,1.0f);

}