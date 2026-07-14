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
uniform vec4 fillColor = vec4(1.0, 0.0, 0.0, 1.0);

void main()
{
    vec4 tc = texture(texture0, fragTexCoord);

    if(fragTexCoord.x <= progress / 100.0){
        tc = fillColor;
    }

    finalColor = tc;
}