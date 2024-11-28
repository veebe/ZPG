#version 330
in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
out vec4 frag_colour;


#define MAX_LIGHTS 10
uniform int numLights;

struct light
{
  vec3 position;
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

uniform sampler2D textureUnitID;

void main() {
    vec3 worldPosition = ex_worldPosition.xyz / max(ex_worldPosition.w, 0.00001);

    vec3 viewDir = normalize(cameraPosition - worldPosition);
    vec3 normal = normalize(ex_worldNormal);

    vec3 totalDiffuse = vec3(0.0);
    vec3 totalSpecular = vec3(0.0);

    float totalSpec = 0;
    float totalDiff = 0;

    for (int i = 0; i < numLights; ++i) {
        
        vec3 lv_not_norm;
        if (lights[i].type == 1)
            lv_not_norm = normalize(lights[i].position); 
        else 
            lv_not_norm = lights[i].position - worldPosition;
        
        float fdistance = length(lv_not_norm);
        vec3 lightVector = normalize(lv_not_norm);

        float dimming = 1.0 / (1.0 + (fdistance / lights[i].strength));

        // Diffuse component
        float diff = max(dot(normal, lightVector), 0.0);
        vec3 diffuse = diff * lights[i].color;
        totalDiff += diff;

        // Specular component
        vec3 reflectDir = reflect(-lightVector, normal);
        float spec = 0.0;
        if (diff > 0.0) {
            spec = pow(max(dot(normalize(reflectDir), viewDir), 0.0), shininess);
        }
        totalSpec += spec;
        vec3 specular = spec * lights[i].color;
        if (lights[i].type == 2) {
            float spotEffect = dot(normalize(cameraDirection), -lightVector);
            if (spotEffect < 0.99) continue;
            spotEffect = (spotEffect - 0.99) / (1.0 - 0.99);

            totalDiffuse += diffuse * dimming * spotEffect;
            totalSpecular += specular * dimming * spotEffect;
        }
        else if (lights[i].type == 1){
            if (lights[i].position.y > 0){
                float log_var = log(10 * lightVector.y + 1.0) / log(10 + 1.0);
                totalDiffuse += diffuse * dimming * log_var;
                totalSpecular += specular * dimming * log_var;
            }
            else{
                continue;
            }            
        }
        else{
            totalDiffuse += diffuse * dimming;
            totalSpecular += specular * dimming;
        }
    }

    vec3 final = vec3(0);
    float outline = max(dot(normal, viewDir), 0.0);
    if (outline < 0.03)
        final = vec3(0,0,1);
    if (outline < 0.02)
        final = vec3(1,0,0);

    vec2 screenResolution = vec2(800,600); 

    vec3 ndc = ex_worldPosition.xyz / ex_worldPosition.w;

    vec2 screenPos = ((ndc.xy + vec2(1.0)) * 0.5) * 0.2;

    vec4 overlayColor = texture(textureUnitID, screenPos);

    vec3 totalTextured = vec3(0);

    vec3 highlightColor = vec3(0,0,0);
    if (totalSpec > 0.01){
        highlightColor = totalSpec * vec3(1,0.2,0.5) * (1 - overlayColor.x);
    }
    vec3 highlightColorSmooth = vec3(0,0,0);
    if (totalDiff > 0.1){
        highlightColorSmooth = totalDiff * vec3(0.9,0,0.3) * (1 - overlayColor.x);
    }

    frag_colour = vec4((ambient + (totalDiffuse * 0.2) + (highlightColorSmooth * 0.5) + highlightColor) * objectColor + final, 1.0);
}
