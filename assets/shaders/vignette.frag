#ifdef GL_ES
precision highp float;
#endif

uniform float u_alpha;
uniform float u_inner_radius;
uniform float u_outer_radius;
uniform vec2 u_resolution;

void main() {
    vec2 UV = gl_FragCoord.xy / u_resolution;
    float x = abs(UV.x - 0.5) * 2.0;
    float y = abs(UV.y - 0.5) * 2.0;
    float distance = sqrt(x * x + y * y);
    float alpha = smoothstep(u_inner_radius, u_outer_radius, distance);
    gl_FragColor = vec4(0.0, 0.0, 0.0, u_alpha * alpha);
}
