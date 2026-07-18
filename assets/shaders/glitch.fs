#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

float sampleCount = 20.0;
uniform float blur;
float falloff = 4.0;

void main() {
    vec4 col = texture(texture0, fragTexCoord);

    if(fragTexCoord.x < .9999) {
        vec2 offset = vec2(.0025, .0);
        col.r = texture(texture0, fragTexCoord + offset.xy).r;
        col.g = texture(texture0, fragTexCoord).g;
        col.b = texture(texture0, fragTexCoord + offset.yx).b;
    }

    finalColor = col;

    vec2 destCoord = fragTexCoord;

    vec2 direction = normalize(destCoord - 0.5);
    vec2 velocity = direction * blur * pow(length(destCoord - 0.5), falloff);
    float inverseSampleCount = 1.0 / float(sampleCount);

    mat3x2 increments = mat3x2(velocity * 1.0 * inverseSampleCount, velocity * 2.0 * inverseSampleCount, velocity * 4.0 * inverseSampleCount);

    vec4 accumulator = vec4(0);
    mat3x2 offsets = mat3x2(0);

    for(float i = 0.0; i < sampleCount; i+= 1.0) {
        accumulator.r += texture(texture0, destCoord + offsets[0]).r;
        accumulator.g += texture(texture0, destCoord + offsets[1]).g;
        accumulator.b += texture(texture0, destCoord + offsets[2]).b;
        accumulator.a += (texture(texture0, destCoord + offsets[0]).a + texture(texture0, destCoord + offsets[1]).a + texture(texture0, destCoord + offsets[2]).a) / 3.0;

        offsets -= increments;
    }

    finalColor = vec4(accumulator / sampleCount);
}