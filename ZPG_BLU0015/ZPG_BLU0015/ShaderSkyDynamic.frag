#version 450
in vec3 fragmentLocalPosition;
uniform samplerCube UISky;

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

void main () {
    vec4 texColor = texture(UISky, fragmentLocalPosition);
    
    float dimming = 1;
    vec3 light_color = vec3(1.f);

    for (int i = 0; i < numLights; ++i) {
        
        if (lights[i].type == 1) {
            vec3 lightVector = normalize(lights[i].position);

            if (lights[i].position.y > 0){
                float log_var = log(10 * lightVector.y + 1.0) / log(10 + 1.0);
                dimming = dimming * log_var;
                light_color = lights[i].color;
            }    
        }
    }
    

    frag_colour = (vec4(light_color, 1.f) *  texColor) * dimming;
}

