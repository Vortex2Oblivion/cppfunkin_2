#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

// NOTE: Add your custom variables here

uniform float hue;
uniform float saturation;
uniform float brightness;
uniform float contrast;

const vec3 grayscaleValues = vec3(0.3098039215686275, 0.607843137254902, 0.0823529411764706);
const float e = 2.718281828459045;

vec3 applyHueRotate(vec3 aColor, float aHue){
    float angle = radians(aHue);

    mat3 m1 = mat3(0.213, 0.213, 0.213, 0.715, 0.715, 0.715, 0.072, 0.072, 0.072);
    mat3 m2 = mat3(0.787, -0.213, -0.213, -0.715, 0.285, -0.715, -0.072, -0.072, 0.928);
    mat3 m3 = mat3(-0.213, 0.143, -0.787, -0.715, 0.140, 0.715, 0.928, -0.283, 0.072);
    mat3 m = m1 + cos(angle) * m2 + sin(angle) * m3;

    return m * aColor;
}

vec3 applySaturation(vec3 aColor, float value){
    if(value > 0.0){ value = value * 3.0; }
    value = (1.0 + (value / 100.0));
    vec3 grayscale = vec3(dot(aColor, grayscaleValues));
    return clamp(mix(grayscale, aColor, value), 0.0, 1.0);
}

vec3 applyContrast(vec3 aColor, float value){
    value = (1.0 + (value / 100.0));
    if(value > 1.0){
        value = (((0.00852259 * pow(e, 4.76454 * (value - 1.0))) * 1.01) - 0.0086078159) * 10.0; //Just roll with it...
        value += 1.0;
    }
    return clamp((aColor - 0.25) * value + 0.25, 0.0, 1.0);
}

vec3 applyHSBCEffect(vec3 color){

    //Brightness
    color = color + ((brightness) / 255.0);

    //Hue
    color = applyHueRotate(color, hue);

    //Contrast
    color = applyContrast(color, contrast);

    //Saturation
    color = applySaturation(color, saturation);

    return color;
}

void main()
{
    vec4 textureColor = texture(texture0, fragTexCoord);

    // Un-multiply alpha if the texture is premultiplied
    // Lime premultiplies alphas before sending it to render, so we want to accomodate header. This fixes some antialiased edges appearing darker
    vec3 unpremultipliedColor = textureColor.a > 0.0 ? textureColor.rgb / textureColor.a : textureColor.rgb;

    // Apply effects to the unpremultiplied color
    vec3 outColor = applyHSBCEffect(unpremultipliedColor);

    finalColor = vec4(outColor * textureColor.a, textureColor.a);
}