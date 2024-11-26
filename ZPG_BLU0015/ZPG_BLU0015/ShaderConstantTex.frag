#version 330
in vec2 vt_out;
out vec4 frag_colour;

uniform sampler2D textureUnitID;

void main() {
    frag_colour = texture(textureUnitID, vt_out);
}
