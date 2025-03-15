#include"gllib.h"

int glad_load(){
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize GLAD");
		fprintf(stderr,"Failed to initialize GLAD");
		return -1;
	}
	return 0;
}

GLFWwindow *window_init(int width,int height,const char* title,GLFWmonitor *monitor,GLFWwindow *share){
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(width,height,title,monitor,share);
	if (window == NULL)
	{
		fprintf(stderr,"Failed to create GLFW window" );
		glfwTerminate();
	}
	return window;
}

int shader_build(shader_file shader[],GLuint shader_list[],size_t list_size){
	FILE *file_p = NULL;
	size_t file_size;
	char * shader_string;

	for (size_t i = 0;i < list_size;i++){
		fprintf(stderr,"loading shader:%s\n",shader[i].path);
		file_p = fopen(shader[i].path,"rb");
		if(file_p == NULL){
			fprintf(stderr,"ERROR:SHADER:%s:shader file open faild\n",shader[i].path);
			continue;
		}
		fseek(file_p,0,SEEK_END);
		file_size = ftell(file_p);
		rewind(file_p);
		shader_string = (char *)malloc((file_size + 1) * sizeof(char));
		fread(shader_string,sizeof(char),file_size,file_p);
		shader_string[file_size] = '\0';
		fclose(file_p);

		GLuint shader_id;
		shader_id = glCreateShader(shader[i].type);
		if(shader_id == 0){
			fprintf(stderr,"ERROR:SHADER:%s:glCreateShader() faild\n",shader[i].path);
			continue;
		}

		glShaderSource(shader_id,1,(char const * const *)(&shader_string),NULL);
		glCompileShader(shader_id);

		int  success;
		char infoLog[512];
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

		if(!success)
		{
			glGetShaderInfoLog(shader_id, 512, NULL, infoLog);
			fprintf(stderr,"ERROR:SHADER:%s:COMPILATION_FAILED\n%s\n",shader[i].path,infoLog);
			continue;
		}
		shader_list[i] = shader_id;
	}
	return 0;
}

GLuint shader_program_build(GLuint shader_list[],size_t list_size){
	GLuint shader_program = glCreateProgram();
	/* fprintf(stderr,"%zu\n",list_size); */

	for (size_t i = 0;i < list_size;i++)
		glAttachShader(shader_program,shader_list[i]);

	glLinkProgram(shader_program);

	for (size_t i = 0;i < list_size;i++)
		glDeleteShader(shader_list[i]);

	return shader_program;
}

GLuint texture2D_build(texture2D_file texture_file_list[],size_t list_size){
	int width,height,nrChannels;
	GLuint texture;
	glGenTextures(list_size,&texture);

	stbi_set_flip_vertically_on_load(true);
	unsigned char *texture_data;

	for(size_t i = 0;i < list_size;i++){
		glActiveTexture(GL_TEXTURE0 + i);
		texture_data = stbi_load(texture_file_list[i].path,&width,&height,&nrChannels,0);
		glBindTexture(GL_TEXTURE_2D,texture);
		glTexImage2D(
				GL_TEXTURE_2D,
				texture_file_list[i].level,
				texture_file_list[i].internalformat,
				width,height,
				0,
				texture_file_list[i].format,
				texture_file_list[i].type,
				texture_data
				);
		stbi_image_free(texture_data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	return texture;
}


/* mat4 CalculateObliqueMatrix(Camera cam,vec4 clipPlane){ */
/* 	Matrix4x4 projectionMatrix = cam.projectionMatrix; */
/* 	Vector4 q = projectionMatrix.inverse * new Vector4( */
/* 			Sign(clipPlane.x), */
/* 			Sign(clipPlane.y), */
/* 			1.0f, */
/* 			1.0f */
/* 			); */

/* 	Vector4 c = clipPlane * (2.0F / (Vector4.Dot(clipPlane, q))); */

/* 	// Replace the third row of the projection matrix */
/* 	projectionMatrix[2] = c.x - projectionMatrix[3]; */
/* 	projectionMatrix[6] = c.y - projectionMatrix[7]; */
/* 	projectionMatrix[10] = c.z - projectionMatrix[11]; */
/* 	projectionMatrix[14] = c.w - projectionMatrix[15]; */

/* 	return projectionMatrix; */
/* } */
