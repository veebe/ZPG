#version 330
/* Vratislav Blunar - BLU0015 */
out vec4 frag_colour;

uniform vec3 objectColor;

void main() {
    frag_colour = vec4(objectColor, 1.0);  
}
