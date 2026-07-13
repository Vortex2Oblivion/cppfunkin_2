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
uniform float progress = 0;
uniform vec3 fillColor = vec3(1.0, 0.0, 0.0);

void main()
{
    vec3 tc = texture(texture0, fragTexCoord).rgb;

    if(fragTexCoord.x <= progress){
        tc = fillColor;
    }

    finalColor = vec4(tc, fragColor.a);
}