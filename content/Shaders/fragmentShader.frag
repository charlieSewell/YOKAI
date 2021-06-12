#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in float visibility;
in vec3 Normal;
in vec3 FragPos;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

uniform sampler2D texture_diffuse1;
uniform vec3 skyColor;
void main()
{
    vec4 texColor = texture(texture_diffuse1, TexCoords);

    //if(texColor.a < 0.1)
        //discard;
    //FragColor = vec4(0.8,0,0,0);

    //Ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    //Difuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    //Specular
    float specularStrength = 0.05;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;


    vec3 result = (ambient + diffuse + specular);

    FragColor = texColor * vec4(result,1.0);

    FragColor = mix(vec4(skyColor,1.0),FragColor,visibility);
}