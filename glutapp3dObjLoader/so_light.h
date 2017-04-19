#ifndef SO_Light_H
#define SO_Light_H

// Include needed header files
# include <vector>
# include <gsim/gs_color.h>
# include <gsim/gs_vec.h>
# include "ogl_tools.h"

// Scene objects should be implemented in their own classes; and
// here is an example of how to organize a scene object in a class.
// Scene object axis:
class SoLight : public GlObjects
{
private:
	std::vector<GsVec>   P; // coordinates
	std::vector<GsColor> C; // colors
	int _numpoints;         // saves the number of points

public:
	SoLight();
	void init(const GlProgram& prog);
	void build(float l_x, float l_y, float l_z);	//radius, iteration
	void draw(GsMat& tr, GsMat& pr);
};

#endif // SO_AXIS_H
