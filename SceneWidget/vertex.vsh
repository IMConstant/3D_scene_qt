uniform mat4 u_modelViewProjectionMatrix;

attribute vec3 coord3d;
attribute vec3 normal;
attribute vec4 color;

uniform vec3 camera_position;
uniform mat4 u_transformation;
uniform float angle;

varying vec4 vColor;
varying vec3 vLook;
varying vec3 vNormal;
varying vec3 vPosition;

void main(void) {
    gl_Position = u_modelViewProjectionMatrix * vec4(coord3d.x, coord3d.y, coord3d.z, 1.0);

    vColor = color;
    vNormal = vec3(u_transformation * vec4(normal, 0.0));
    vLook = camera_position - vec3(u_transformation * vec4(coord3d, 1.0));
    vPosition = coord3d;
}
