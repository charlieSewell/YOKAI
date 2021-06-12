#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoord;
out float HeightPoint;
out vec3 Normal;
out vec3 FragPos;
out float visibility;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

const float density = 0.002;
const float gradient = 1.1;

void main()
{
    vec4 worldPosition = model * vec4(aPos,1.0);
    vec4 positionRelToCamera = view * worldPosition;
    float distance = length(positionRelToCamera.xyz);
    visibility = exp(-pow((distance*density),gradient));

    TexCoord = vec2(aTexCoords.x, aTexCoords.y);
    HeightPoint = aPos[1];
    Normal = mat3(transpose(inverse(model))) * aNormal;
    FragPos = vec3(model * vec4(aPos, 1.0));
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}