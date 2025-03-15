#ifndef GLLIB
#define GLLIB 1

#include"glad/glad.h"
#include"GLFW/glfw3.h"
#include"cglm/call.h"
#include"stb_image.h"
#include<stdio.h>
#include<stdlib.h>

typedef struct{
	vec3 positon;
	vec3 targit;
	vec3 up;
}camera;

typedef struct{
	char *path;
	GLenum type;
}shader_file;

typedef struct{
	char *path;
	GLint level;
	GLint internalformat;
	GLenum format;
	GLenum type;
}texture2D_file;

GLFWwindow *window_init(int width,int height,const char* title,GLFWmonitor *monitor,GLFWwindow *share);

int glad_load();

GLuint shader_program_build(GLuint shader_list[],size_t listlen);

/* GLuint shader_build(const char *shader_path,GLenum shader_type); */
int shader_build(shader_file shader[],GLuint shader_list[],size_t list_size);

#endif//GLLIB
