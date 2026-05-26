uniform sampler2D texture;
uniform float blur_radius;

void main()
{
    vec2 offset = 1.0 / textureSize(texture, 0);
    vec4 color = vec4(0.0);
    
    int radius = int(blur_radius);
    int count = 0;
    
    // Simple box blur
    for (int x = -radius; x <= radius; x++)
    {
        for (int y = -radius; y <= radius; y++)
        {
            vec2 uv = vec2(gl_TexCoord[0].x + float(x) * offset.x,
                          gl_TexCoord[0].y + float(y) * offset.y);
            color += texture2D(texture, uv);
            count++;
        }
    }
    
    gl_FragColor = color / float(count);
}