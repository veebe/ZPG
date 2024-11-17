#version 330
in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
out vec4 frag_colour;

#define MAX_LIGHTS 4
uniform int numLights;

struct light {
    vec3 position;
    vec3 direction;
    vec3 color;
    float strength;
    int type;
};

uniform light lights[MAX_LIGHTS]; 
uniform vec3 ambient;
uniform vec3 objectColor;
uniform float shininess;

uniform vec3 cameraDirection;
uniform vec3 cameraPosition;

void main() {

    vec3 worldPosition = ex_worldPosition.xyz / max(ex_worldPosition.w, 0.00001);
    vec3 viewDir = normalize(cameraPosition - worldPosition);
    vec3 normal = normalize(ex_worldNormal);

    vec3 totalDiffuse = vec3(0.0);
    vec3 totalSpecular = vec3(0.0);

    for (int i = 0; i < numLights; ++i) {
        
        vec3 lv_not_norm = lights[i].position - worldPosition; 
        
        float fdistance = length(lv_not_norm);
        vec3 lightVector = normalize(lv_not_norm);

        float dimming = 1.0 / (1.0 + (fdistance / lights[i].strength));

        // Diffuse component
        float diff = max(dot(normal, lightVector), 0.0);
        vec3 diffuse = diff * lights[i].color;

        // Specular component using reflector light calculations
        vec3 reflectDir = normalize(reflect(-lightVector, normal));
        float spec = pow(max(dot(reflectDir, viewDir), 0.0), shininess);
        vec3 specular = spec * lights[i].color;

        if (lights[i].type == 2) {
            float spotEffect = dot(normalize(cameraDirection), -lightVector);
            if (spotEffect < 0.99) continue;
            spotEffect = (spotEffect - 0.99) / (1.0 - 0.99);

            totalDiffuse += diffuse * dimming * spotEffect;
            totalSpecular += specular * dimming * spotEffect;
        }
        else {
            totalDiffuse += diffuse * dimming;
            totalSpecular += specular * dimming;
        }
        
    }
    
    frag_colour = vec4((ambient + totalDiffuse + totalSpecular) * objectColor, 1.0);
}
