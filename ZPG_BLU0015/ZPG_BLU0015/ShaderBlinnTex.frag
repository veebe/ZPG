#version 330
/* Vratislav Blunar - BLU0015 */
in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
in vec2 vt_out;
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
uniform float shininess;

uniform vec3 cameraDirection;
uniform vec3 cameraPosition;

uniform sampler2D textureUnitID;

void main() {
    vec4 texColor = texture(textureUnitID, vt_out);

    vec3 worldPosition = ex_worldPosition.xyz / max(ex_worldPosition.w, 0.00001);

    vec3 viewDir = normalize(cameraPosition - worldPosition);
    vec3 normal = normalize(ex_worldNormal);


    vec3 totalDiffuse = vec3(0.0);
    vec3 totalSpecular = vec3(0.0);

    for (int i = 0; i < numLights; ++i) {
        
        vec3 lv_not_norm;
        if (lights[i].type == 1)
            lv_not_norm = normalize(lights[i].position); 
        else 
            lv_not_norm = lights[i].position - worldPosition;

        float fdistance = length(lv_not_norm);
        vec3 lightVector = normalize(lv_not_norm);

        float dimming = 1.0 / (1.0 + (fdistance / lights[i].strength));

        float diff = max(dot(normal, lightVector), 0.0);
        vec3 diffuse = diff * lights[i].color;

        vec3 halfwayDir = normalize(lightVector + viewDir);
        float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess);
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
    vec3 result = (ambient + totalDiffuse + totalSpecular) * texColor.rgb;
    frag_colour = vec4(result, texColor.a); 

}
