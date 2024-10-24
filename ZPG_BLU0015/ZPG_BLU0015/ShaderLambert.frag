#version 330
in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
in vec3 ex_cameraDirection;

out vec4 frag_colour;
uniform vec3 lightPosition;  
uniform vec3 lightColor;   

void main () {
    vec3 lightVector = normalize(lightPosition - vec3(ex_worldPosition)); 

    float diff = max(dot(lightVector, normalize(ex_worldNormal)), 0.0);
    vec3 diffuse = diff * lightColor;  

    vec3 ambient = vec3(0.1, 0.1, 0.1); 
    vec3 objectColor = vec3(0.385, 0.647, 0.812); 
    
    vec3 viewDir = normalize(ex_cameraDirection);
	vec3 reflectDir = normalize(reflect(-lightVector, normalize(ex_worldNormal)));     
    
    float spec = 0.0;
    if (diff > 0.0) {
        spec = pow(max(dot(reflectDir, viewDir), 0.0), 32.0); 
    }

    vec4 specular = vec4(lightColor * spec, 1.0); 
    
    frag_colour = vec4((ambient + diffuse) * objectColor, 1.0) + specular;  
};
