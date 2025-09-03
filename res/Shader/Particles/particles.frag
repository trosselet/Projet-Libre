#version 130

in float alpha;
out vec4 fragColor;

void main()
{
    fragColor = vec4(0.0, 0.0, 0.0, alpha);
}