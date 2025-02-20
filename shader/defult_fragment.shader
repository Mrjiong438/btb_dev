#version 330 core
out vec4 FragColor;

in vec4 vertex_color;
in vec2 TexCoord;

uniform sampler2D Texture0;
uniform sampler2D Texture1;

void main()
{
	/* FragColor = vertex_color; */
	/* FragColor = texture(Texture0,TexCoord) * vertex_color; */
	vec4 temp = 
		/* mix(texture(Texture0,TexCoord),texture(Texture1,TexCoord),0.6); */
		texture(Texture0,TexCoord);
	/* if(temp.a < 0.1) */
	/* 	discard; */
	FragColor = temp;
	/* FragColor = texture(Texture1,TexCoord); */
};

