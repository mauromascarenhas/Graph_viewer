#version 330

in vec4 vColours;
in vec4 vPosition;

out vec4 v2fColour;

void main(){
    gl_Position = vPosition;
    v2fColour = vColours;
}
