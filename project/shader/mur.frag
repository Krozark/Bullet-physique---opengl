uniform sampler2D Texture_Col;
uniform sampler2D Texture_Normal;

void main()
{
    vec3 Normal = normalize(texture2D(Texture_Normal, gl_TexCoord[0].st).rgb * 2.0 - 1.0);
    vec4 Kd = texture2D(Texture_Col, gl_TexCoord[0].st);
    vec3 Light = (vec3(gl_LightSource[0].position));

    Kd *= clamp(dot(Normal, Light), 0.0,1.0);

    gl_FragColor = Kd;
}
