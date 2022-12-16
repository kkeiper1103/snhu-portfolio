#version 440 core

in vec4 oColor;
in vec2 oTextureCoord;
in vec3 oNormal;
in vec3 oFragPosition;



//
struct Light {
    float constant;
    float linear;
    float quadratic;

    vec4 ambient;
    vec4 diffuse;
    vec4 specular;

    vec3 position;

    // normalized direction
    vec3 direction;
};

// number of active lights
uniform int numLights;

// number of allowed lights
#define MAX_LIGHTS 16
uniform Light lights[MAX_LIGHTS];

uniform vec3 viewPosition;




uniform bool useTexture0 = false;
uniform sampler2D texture0;

uniform bool useTexture1 = false;
uniform sampler2D texture1;


out vec4 FragColor;


// functions to apply lights and then average the results
vec3 applyLight(int i) {
    // get attenuation factor
    float distance = length(lights[i].position - oFragPosition);
    float attenuation = 1.0 / ( lights[i].constant + lights[i].linear * distance + lights[i].quadratic * (distance * distance) );

    // ambient
    vec3 ambient = lights[i].ambient.rgb * lights[i].ambient.a;

    // diffuse
    vec3 normal = normalize(oNormal);
    vec3 lightDir = normalize(lights[i].position - oFragPosition);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lights[i].diffuse.rgb * lights[i].diffuse.a;

    // specular
    vec3 viewDir = normalize(viewPosition - oFragPosition);
    vec3 reflectDir = reflect(-lights[i].direction, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = spec * lights[i].specular.rgb * lights[i].specular.a;

    return ambient * attenuation + diffuse * attenuation + specular * attenuation;
}


void main() {

    // average the total of all lights
    vec3 final = vec3(0, 0, 0);

    // the min() call is to make sure that no errors happen if a user binds more than MAX_LIGHTS
    for(int i=0; i < min(numLights, MAX_LIGHTS); i++)
        final += applyLight(i);

    final /= max(1, numLights); // prevent a divide by 0 error
    

    // get the raw texture color

    if(useTexture0)
        FragColor = texture(texture0, oTextureCoord);
    else
        FragColor = oColor;

    // apply final calculated lighting to texture
    FragColor *= vec4(final, 1);
}
