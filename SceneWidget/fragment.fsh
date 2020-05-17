varying vec4 vColor;
varying vec3 vLook;
varying vec3 vNormal;
varying vec3 vPosition;

uniform mat4 u_modelViewProjectionMatrix;
uniform mat4 u_modelViewMatrix;
uniform mat4 u_transformation;
uniform vec3 u_color;

uniform vec3 light_position;
uniform vec3 camera_position;
uniform sampler2D sampler0;
uniform sampler2D sampler1;

out float gl_FragDepth;

void main(void) {
    vec3 a = camera_position - vec3(u_transformation * vec4(vPosition, 1.0));
    vec3 b = vNormal;

    float p = abs((a.x * b.x + a.y * b.y + a.z * b.z) / (length(a) * length(b)));

    float k_diffuse = 0.8;
    float k_specular = 0.7;
    float ambient = 0.4;

    vec3 v_normal = normalize(vNormal);
    vec3 lightvector = normalize(light_position - vec3(u_transformation * vec4(vPosition, 1.0)));
    vec3 lookvector = normalize(vLook);

    float diffuse = k_diffuse * max(dot(v_normal, lightvector), 0.0);
    vec3 reflectvector = reflect(-lightvector, v_normal);
    float specular = k_specular * pow( max(dot(lookvector,reflectvector),0.0), 40.0);

    float p1 = (ambient+diffuse+specular);

    v_normal = normalize(vNormal);
    lightvector = normalize(vec3(-2.5, -1.25, -1.0) - vPosition);
    lookvector = normalize(vLook);

    diffuse = k_diffuse * max(dot(v_normal, lightvector), 0.0);
    reflectvector = reflect(-lightvector, v_normal);
    specular = k_specular * pow( max(dot(lookvector,reflectvector),0.0), 40.0);

    float p2 = (ambient+diffuse+specular);
    float p3 = (p2 + p1) / 2.0;
    float px = 10.0 * abs(vec3(u_transformation * vec4(vPosition, 1.0)).z);

    vec4 frag_color = vColor;
    vec4 light_color = vec4(1.0, 1.0, 1.0, 1.0);
    vec4 color = ((frag_color + light_color) / 2.0) * vec4(p * p1, p * p1, p * p1, 1.0);

    vec4 one = vec4(2.0 * p1 * p, 2.0 * p1 * p * px, p1 * p * px, 1.0);
    vec4 water_color = vec4(0.6, 0.6, 1.0, 1.0);
    p = min(vPosition.x / 5.0, 1.0);

//    gl_FragColor = (p * texture2D(sampler0, vPosition.xz) +
//                    (1 - p) * texture2D(sampler1, vPosition.xz)) *
//            (ambient+diffuse+specular);//vec4(p, p, p, 1.0);
    gl_FragColor = color;
    gl_FragColor.a = 1.0;
    //gl_FragDepth = (far-near) * 0.5 * f_ndc_depth + (far + near) * 0.5;


    gl_FragDepth = abs(vec3(u_modelViewProjectionMatrix * vec4(vPosition, 1.0)).z) / 5.0;
}
