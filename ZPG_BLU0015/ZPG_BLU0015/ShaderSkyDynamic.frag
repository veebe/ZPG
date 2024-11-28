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
    vec3 blendedLightColor = vec3(0.0);

    vec3 skyColor = vec3(0);

    for (int i = 0; i < numLights; ++i) {
        if (lights[i].type == 1) {
            if (lights[i].color.x > 0.5){
                vec3 sunriseColor = vec3(0.8, 0.6, 0.1); 
                vec3 middayColor = vec3(1.0, 1.0, 1.0); 
                vec3 sunsetColor = vec3(0.9, 0.2, 0.9); 

                vec3 sunDir = normalize(lights[i].position);

                float heightFactor = clamp(sunDir.y, 0.0, 1.0);
                float horizontalFactor = clamp(sunDir.z, -1.0, 1.0);

                if (horizontalFactor > 0.4) {
                    float sunsetBlend = smoothstep(0.0, 1.0, horizontalFactor - 0.4);
                    skyColor = mix(middayColor, sunsetColor, sunsetBlend);
                } else {
                    float sunriseBlend = smoothstep(-1.0, 0.0, horizontalFactor);
                    skyColor = mix(sunriseColor, middayColor, sunriseBlend);
                }

                float heightFactor_night = clamp(sunDir.y, 0.07, 1.0);

                skyColor *= heightFactor_night;
            }
        }
        /*
        if (lights[i].type == 1) {
            vec3 lightVector = normalize(lights[i].position);

            if (lights[i].position.y > 0){
                //float log_var = log(200 * lightVector.y + 1.0) / log(200 + 1.0);
                float log_val = log(10 * lightVector.y + 1.0) / log(10 + 1.0);
                float log_var = 0.2f + log_val * 0.8f;
                //dimming = dimming * log_var;
                light_color = lights[i].color * log_var;
                //float revers_log = 1 - log_var;
                //vec3 orange = vec3(1,0.9,0);
                //light_color = light_color * revers_log * orange;
            }    
        }*/
    }
    

    //frag_colour = (vec4(light_color, 1.f) *  texColor);
    frag_colour = vec4(skyColor, 1.0) * texColor;
}

