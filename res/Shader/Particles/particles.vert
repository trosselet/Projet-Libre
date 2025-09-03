#version 130

uniform float u_time;
uniform vec2 u_emitter;

in vec2 position;
in vec4 color;

out float alpha;

void main()
{
    float lifeRatio = color.a;

    if (lifeRatio <= 0.0)
    {
        gl_Position = vec4(-100000.0);
        gl_PointSize = 0.0;
        alpha = 0.0;
        return;
    }

    float angle = radians(float(gl_VertexID) * 137.5);
    float speed = 100.0 + mod(float(gl_VertexID) * 73.3, 50.0);

    float life = 0.6;
    float t = mod(u_time, life);
    float ratio = 1.0 - (t / life);

    vec2 velocity = vec2(cos(angle), sin(angle)) * speed;
    vec2 offset = velocity * t;

    gl_Position = gl_ModelViewProjectionMatrix * vec4(u_emitter + offset, 0.0, 1.0);
    gl_PointSize = 3.0;

    alpha = ratio * lifeRatio;
}
