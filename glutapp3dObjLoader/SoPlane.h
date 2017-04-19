
// Ensure the header file is included only once in multi-file projects
#ifndef SO_PLANE_H
#define SO_PLANE_H

#define _USE_MATH_DEFINES

// Include needed header files
# include <gsim/gs_mat.h>
# include <gsim/gs_light.h>
# include <gsim/gs_color.h>
# include <gsim/gs_material.h>
# include <gsim/gs_array.h>
# include "ogl_tools.h"
# include <cmath>
# include <vector>
# include <gsim/gs_shared.h>
# include <gsim/gs_image.h>
# include <gsim/stb_image.h>
# include <gsim/stb_image_write.h>

// Scene objects should be implemented in their own classes; and
// here is an example of how to organize a scene object in a class.
// Scene object axis:
class SoPlane : public GlObjects
{
private:
	GlShader _vshtex, _fshtex;

	GsArray<GsVec>   P; // coordinates
	GsArray<GsVec>   N; // normals
	GsArray<GsVec2>	T;

	GsMaterial _mtl;
	int _numpoints;     // just saves the number of points

	GLuint _texid;
	GlProgram _progtex;
	float influence = .75;

public:
	GsArray<GsVec> NL; // normal lines computed in last build
public:
	SoPlane();
	void init();
	void build();
	void draw(const GsMat& tr, const GsMat& pr, const GsLight& l);
	void increase_influence() { influence += .1; }	//increase shader influence
	void decrease_influence() { influence -= .1; }	//decrease shader influence
};

#endif // SO_MODEL_H
