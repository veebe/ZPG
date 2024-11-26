#version 450
layout(location = 0) in vec3 vp;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform bool showSkyCube;

out vec3 fragmentLocalPosition;

void main () {
    mat4 viewMod = viewMatrix;
    if (!showSkyCube)
	    viewMod = mat4(mat3(viewMatrix)); 
    gl_Position = projectionMatrix * viewMod * vec4(vp, 1.0);
    fragmentLocalPosition = vp;
}
