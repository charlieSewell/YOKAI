#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in ivec4 boneIDs;
layout (location = 4) in vec4 weights;


const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 boneTrans[MAX_BONES];
out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;
out float visibility;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform bool isAnimated;

const float density = 0.003;
const float gradient = 1.5;
void main()
{

    vec4 worldPosition = model * vec4(aPos,1.0);
    vec4 positionRelToCamera = view * worldPosition;
    float distance = length(positionRelToCamera.xyz);

    Normal = mat3(transpose(inverse(model))) * aNormal;

    visibility = exp(-pow((distance*density),gradient));

    mat4 BoneTransform = boneTrans[boneIDs[0]] * weights[0];
    BoneTransform += boneTrans[boneIDs[1]] * weights[1];
    BoneTransform += boneTrans[boneIDs[2]] * weights[2];
    BoneTransform += boneTrans[boneIDs[3]] * weights[3];
    vec4 PosL;
    if(isAnimated)
    {
        PosL = BoneTransform * vec4(aPos, 1.0);
    }
    else{
        PosL = vec4(aPos, 1.0);
    }

    FragPos = vec3(model * vec4(aPos, 1.0));
    TexCoords = aTexCoords;
    gl_Position = projection * view * model* PosL;
}