
// Ensure the header file is included only once in multi-file projects
#ifndef APP_WINDOW_H
#define APP_WINDOW_H

# include <gsim/gs_color.h>
# include <gsim/gs_array.h>
# include <gsim/gs_light.h>
# include <gsim/gs_vec.h>
# include "ogl_tools.h"
# include "glut_window.h"
# include "so_axis.h"
# include "so_model.h"
# include "SoPlane.h"

// The functionality of your application should be implemented inside AppWindow
class AppWindow : public GlutWindow
 { private :
    // OpenGL shaders and programs:
    GlShader _vshflat, _fshflat, _vshgou, _fshgou, _vshphong, _fshphong;
    GlProgram _progflat, _proggou, _progphong;

    // My scene objects:
    SoAxis _axis;
    SoModel _model;
	
	SoModel body;
	SoModel prop;
	SoModel prop2;
	SoModel rudder;
	SoModel elevator;
	//SoModel flaps;
	SoModel farleftflaps;
	SoModel centerleftflaps;
	SoModel centerrightflaps;
	SoModel farrightflaps;
	SoModel rflaps;
	
	SoModel rocket;

	SoPlane plane;

    // Scene data:
	//prop rotation
	int propRot = 0;
	GsMat propTrans;
	GsMat propTrans2;

	//body trans
	int bodyRotPitch = 0;
	int bodyRotRoll = 0;
	int bodyRotYaw = 0;
	int body_direction;
	GsMat bodyTransPitch, bodyTransRoll, bodyTransYaw, bodySet, bodyRotate;

	//elevator trans
	int elevatorRot = 0;
	GsMat elevatorTrans;

	//rudder trans
	int rudderRot = 0;
	GsMat rudderTrans;

	//flap trans
	int flapsRot = 0;
	int farLeftFlapsRot = 0;
	int centerLeftFlapsRot = 0;
	int centerRightFlapsRot = 0;
	int farRightFlapsRot = 0;
	GsMat farLeftFlapsTrans;
	GsMat centerLeftFlapsTrans;
	GsMat centerRightFlapsTrans;
	GsMat farRightFlapsTrans;

	//shadow
	GsMat ShadowTrans;
	float lx = 1.0, ly = 1.0, lz = 1.0;

	GsMat movement;
	int move = 0;

	GsMat rocketTrans;

	float offset = 0;

    bool  _viewaxis;
    GsModel _gsm, _gsm2, _gsm3, _gsm4, _gsm5, _gsm6, _gsm7, _gsm8, _gsm9, _gsm10, _gsm11;
    GsLight _light;
    
    // App data:
    enum MenuEv { evOption0, evOption1 };
    float _rotx, _roty, _fovy;
    int _w, _h;

	bool cam = true;

   public :
    AppWindow ( const char* label, int x, int y, int w, int h );
    void initPrograms ();
    void loadModel ( int model );
    GsVec2 windowToScene ( const GsVec2& v );

   private : // functions derived from the base class

    virtual void glutMenu ( int m );
    virtual void glutKeyboard ( unsigned char key, int x, int y );
    virtual void glutSpecial ( int key, int x, int y );
    virtual void glutMouse ( int b, int s, int x, int y );
    virtual void glutMotion ( int x, int y );
    virtual void glutDisplay ();
    virtual void glutReshape ( int w, int h );
	virtual void glutIdle();

	virtual void ComputeShadowTrans(GsMat &TransMatrix, float l_x, float l_y, float l_z);
	virtual void ComputeBodyTrans(GsMat &TransMatrix, int i, int direction);
	virtual void ComputePropTrans(GsMat &TransMatrix, int i);
	virtual void ComputePropTrans2(GsMat &TransMatrix, int i);
	virtual void ComputeElevatorTrans(GsMat &TransMatrix);
	virtual void ComputeRudderTrans(GsMat &TransMatrix);
	virtual void ComputeFarLeftFlapTrans(GsMat &TransMatrix);
	virtual void ComputeCenterLeftFlapTrans(GsMat &TransMatrix);
	virtual void ComputeCenterRightFlapTrans(GsMat &TransMatrix);
	virtual void ComputeFarRightFlapTrans(GsMat &TransMatrix);

	virtual void ComputeRocket(GsMat &TransMatrix);

	virtual void moveForward(GsMat &TransMatrix);
 };

#endif // APP_WINDOW_H
