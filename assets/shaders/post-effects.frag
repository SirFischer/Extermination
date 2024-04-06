uniform sampler2D texture;

void main()
{
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	vec4 color = gl_Color * pixel;
	//darken the sceen to make it look like night
	color.a = 1.0;
    gl_FragColor = color;
}