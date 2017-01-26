#version 410 core
#define PI 3.1415926

uniform float multiplier;
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
out vec3 ourColor;

void main() {
    gl_Position = vec4(
        position.x * sin(2 * PI * multiplier),
        position.y * cos(PI * multiplier/3),
        position.z + position.z * multiplier,
        1.0
    );
    ourColor = color;
}
