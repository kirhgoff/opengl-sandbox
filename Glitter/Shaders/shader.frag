#version 410 core
uniform float multiplier;
in vec3 ourColor;
out vec4 color;
void main() {
//    color = vec4(ourColor.x * (1 -  multiplier), ourColor.y * multiplier, ourColor.z, 1.0f);
    color = vec4(ourColor.x, ourColor.y, ourColor.z, 1.0f);
}
