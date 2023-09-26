#version 450

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in flat vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

vec3 gammaCorrect(float r, float g, float b, float factor) {
    return vec3(pow(r, factor), pow(g, factor), pow(b, factor));
}

vec3 toneMap(vec3 x) {
    const float a = 2.51;
    const float b = 0.03;
    const float c = 2.43;
    const float d = 0.59;
    const float e = 0.14;
    return clamp((x * (a * x + b)) / (x * (c * x + d) + e), 0.0, 1.0);
}

void main() {
    vec4 sampledColor = texture(texSampler, fragTexCoord);
    vec3 color = gammaCorrect(sampledColor.x*fragColor.x, sampledColor.y*fragColor.y, sampledColor.z*fragColor.z, 1.5f);
    outColor = vec4(toneMap(color), sampledColor.a);
}