#version 410 core
out vec4 FragColor;

in vec2 TexCoord;
in float HeightPoint;
in vec3 Normal;
in vec3 FragPos;
in float visibility;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform float lightLinear;
uniform float lightQuadratic;

uniform sampler2D sandTexture;
uniform sampler2D grassTexture;
uniform sampler2D snowTexture;
uniform sampler2D detailMap;

uniform float sandHeight;
uniform float grassHeight;
uniform float snowHeight;
uniform vec3 skyColor;
void main(){
    vec4 sand = texture(sandTexture, TexCoord);
    vec4 grass = texture(grassTexture, TexCoord);
    vec4 snow = texture(snowTexture, TexCoord);
    vec4 detail = texture(detailMap, TexCoord);
    //FragColor = vec4(0.8,0,0,0);
    if(HeightPoint > snowHeight){

        FragColor = snow;
    }
    else if(HeightPoint > grassHeight){
        float blend = (HeightPoint - grassHeight) / (snowHeight - grassHeight);
        FragColor = mix(grass,snow,blend);
    }
    else if(HeightPoint > sandHeight){
        float blend = (HeightPoint - sandHeight) / (grassHeight - sandHeight);
        FragColor = mix(sand,grass,blend);
    }
    else{
        FragColor = sand;
    }
    //Light Drop off
    float dist = length(lightPos - FragPos);
    float attenuation = 1.0 / (1.0 + lightLinear * dist + lightQuadratic * (dist * dist));    
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

    //final results
    //ambient  *= attenuation;
    //diffuse  *= attenuation;
    //specular *= attenuation;
    
    vec4 texResult = FragColor*detail;
    vec3 result = (ambient + diffuse + specular);

    FragColor = texResult * vec4(result,1.0);

    FragColor = mix(vec4(skyColor,1.0),FragColor,visibility);
}