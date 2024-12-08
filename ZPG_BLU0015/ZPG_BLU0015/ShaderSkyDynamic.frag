#version 450
/* Vratislav Blunar - BLU0015 */
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
    }
    
    frag_colour = vec4(skyColor, 1.0) * texColor;
}

