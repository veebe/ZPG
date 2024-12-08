#version 450
/* Vratislav Blunar - BLU0015 */
in vec3 fragmentLocalPosition;
uniform samplerCube UISky;

out vec4 frag_colour;

void main () {
    frag_colour = texture(UISky, fragmentLocalPosition);
}

