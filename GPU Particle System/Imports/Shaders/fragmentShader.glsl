#version 440 core
uniform sampler2D tex0;

in Vertex	{
	vec2 texCoord;
	vec4 colour;
} IN;

out vec4 gl_FragColor;
uniform float colourVar;

void main(void)	{
	vec4 texC = texture(tex0,IN.texCoord);
	if (texC.rgb == vec3(0.0,0.0,0.0)) discard;
	else gl_FragColor = (IN.colour - vec4(0.0,colourVar,0,0));
	//else gl_FragColor = texC * IN.colour;
}