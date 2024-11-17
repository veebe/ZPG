#version 330
layout(location=0) in vec3 vp;               
layout(location=1) in vec3 vn;               

uniform mat4 modelMatrix;                    
uniform mat4 viewMatrix;                     
uniform mat4 projectionMatrix;  
uniform vec3 cameraPosition;

out vec4 ex_worldPosition;                   
out vec3 ex_worldNormal;
out vec3 ex_cameraDirection;
		
void main () {
		gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);
		ex_worldPosition = modelMatrix * vec4(vp, 1.0);
		ex_worldNormal = mat3(transpose(inverse(modelMatrix))) * vn;
};