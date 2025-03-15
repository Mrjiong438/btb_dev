#ifndef MST_HOT_LOAD
#define MST_HOT_LOAD
#include<stdio.h>
#include<dlfcn.h>

typedef struct{
	char *name;
	void *fuc;
}dyfuc;

typedef struct{
	char *path;
	void *lib;
	dyfuc *fucs;
}dylib;

int mst_load_lib(dylib *dlib);

#ifdef MST_HOT_LOAD_IMPLEMENTATION
int mst_load_lib(dylib *dlib){
	if (dlib->lib != NULL) {
		dlclose(dlib->lib);
		/* *lib_dest = NULL; */
	}
	void *templib = dlopen(dlib->path,RTLD_NOW);//will be NULL if error

	if(templib == NULL){
		fprintf(stderr,"ERROR: can not load %s:\n%s\n",dlib->path,dlerror());
		return -1;
	}
	dlib->lib = templib;

	for(int i = 0;dlib->fucs[i].name != NULL;i++){
		void *tempfuc = dlsym(templib,dlib->fucs[i].name);
		if(tempfuc == NULL){
			fprintf(stderr,"ERROR: can not load fuc %s in %s:\n%s\n" ,dlib->fucs[i].name,dlib->path,dlerror());
			return -2;
		}
		dlib->fucs[i].fuc = tempfuc;
	}
	return 0;
}

#ifdef MST_RELEASE
#define mst_load_lib(n) 
#endif//MST_RELEASE

#endif//MST_HOT_LOAD_IMPLEMENTATION
#endif//MST_HOT_LOAD
