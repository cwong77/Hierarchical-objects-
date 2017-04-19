
# include <iostream>
# include <gsim/gs.h>
# include "app_window.h"

AppWindow::AppWindow ( const char* label, int x, int y, int w, int h )
          :GlutWindow ( label, x, y, w, h )
 {
   initPrograms ();
   addMenuEntry ( "Option 0", evOption0 );
   addMenuEntry ( "Option 1", evOption1 );
   _viewaxis = true;
   _fovy = GS_TORAD(60.0f);
   _rotx = _roty = 0;
   _w = w;
   _h = h;
 }

void AppWindow::initPrograms ()
 {
   // Init my scene objects:
	//_model.init();

   _axis.init ();
   body.init ();
   prop.init();
   prop2.init();
   rudder.init();
   elevator.init();
   farleftflaps.init();
   centerleftflaps.init();
   centerrightflaps.init();
   farrightflaps.init();
   rflaps.init();
   rocket.init();

   plane.init();


   // set light:
   _light.set ( GsVec(0,0,10), GsColor(90,90,90,255), GsColor::white, GsColor::white );

   // Load demo model:
   loadModel ( 1 );
 }

static void printInfo ( GsModel& m )
 {
   std::cout<<"V:  "<<m.V.size()<<"\n";
   std::cout<<"F:  "<<m.F.size()<<"\n";
   std::cout<<"N:  "<<m.N.size()<<"\n";
   std::cout<<"M:  "<<m.M.size()<<"\n";
   std::cout<<"Fn: "<<m.Fn.size()<<"\n";
   std::cout<<"Fm: "<<m.Fm.size()<<"\n";
 }

void AppWindow::loadModel ( int model )
 {
	/*
   float f;
   GsString file;
   switch ( model )
    { case 1: f=0.05f; file="../models/cessna/cessna.obj"; break;
      case 2: f=0.05f; file="../models/cessna/rudder.obj"; break;
      case 3: f=0.05f; file="../models/cessna/body.obj"; break;
	  case 4: f = 0.05f; file = "../models/cessna/flaps.obj"; break;
	  case 5: f = 0.05f; file = "../models/cessna/flaps2.obj"; break;
	  case 6: f = 0.05f; file = "../models/cessna/rflaps.obj"; break;
	  case 7: f = 0.05f; file = "../models/cessna/prop2.obj"; break;
	  case 8: f = 0.05f; file = "../models/cessna/prop.obj"; break;
	  case 9: f = 0.05f; file = "../models/cessna/elevator.obj"; break;

      default: return;
    }
	
   std::cout<<"Loading "<<file<<"...\n";
   if ( !_gsm.load ( file ) ) std::cout<<"Error!\n";
   printInfo ( _gsm );
   _gsm.scale ( f ); // to fit our camera space
   _model.build(_gsm);
   redraw();
   */
	
	_gsm.smooth(GS_TORAD(35));
	_gsm2.smooth(GS_TORAD(35));
	_gsm3.smooth(GS_TORAD(35));
	_gsm4.smooth(GS_TORAD(35));
	_gsm5.smooth(GS_TORAD(35));
	_gsm6.smooth(GS_TORAD(35));
	_gsm7.smooth(GS_TORAD(35));
	_gsm8.smooth(GS_TORAD(35));
	
	//body
	float f = 0.05f;
	GsString file = "../models/cessna/body.obj";
	std::cout << "Loading " << file << "...\n";
	if (!_gsm.load(file)) std::cout << "Error!\n";
	//printInfo(_gsm);
	_gsm.scale(f);
	body.build(_gsm);

	//props
	file = "../models/cessna/prop.obj";
	std::cout << "Loading " << file << "...\n";
	if (!_gsm2.load(file)) std::cout << "Error!\n";
	//printInfo(_gsm2);
	_gsm2.scale(f);
	prop.build(_gsm2);

	file = "../models/cessna/prop2b.obj";
	std::cout << "Loading " << file << "...\n";
	if (!_gsm3.load(file)) std::cout << "Error!\n";
	//printInfo(_gsm3);
	_gsm3.scale(f);
	prop2.build(_gsm3);

	//rudder
	file = "../models/cessna/rudder.obj";
	std::cout << "Loading " << file << "...\n";
	if (!_gsm4.load(file)) std::cout << "Error!\n";
	//printInfo(_gsm4);
	_gsm4.scale(f);
	rudder.build(_gsm4);

	//flaps
	file = "../models/cessna/farleftflaps.obj";
	std::cout << "Loading " << file << "...\n";
	if (!_gsm5.load(file)) std::cout << "Error!\n";
	//printInfo(_gsm5);
	_gsm5.scale(f);
	farleftflaps.build(_gsm5);

	file = "../models/cessna/centerleftflaps.obj";
	std::cout << "Loading " << file << "...\n";
	if (!_gsm9.load(file)) std::cout << "Error!\n";
	//printInfo(_gsm9);
	_gsm9.scale(f);
	centerleftflaps.build(_gsm9);

	file = "../models/cessna/centerrightflaps.obj";
	std::cout << "Loading " << file << "...\n";
	if (!_gsm6.load(file)) std::cout << "Error!\n";
	//printInfo(_gsm6);
	_gsm6.scale(f);
	centerrightflaps.build(_gsm6);

	file = "../models/cessna/farrightflaps.obj";
	std::cout << "Loading " << file << "...\n";
	if (!_gsm10.load(file)) std::cout << "Error!\n";
	//printInfo(_gsm10);
	_gsm10.scale(f);
	farrightflaps.build(_gsm10);

	file = "../models/cessna/rflaps.obj";
	std::cout << "Loading " << file << "...\n";
	if (!_gsm7.load(file)) std::cout << "Error!\n";
	//printInfo(_gsm7);
	_gsm7.scale(f);
	rflaps.build(_gsm7);

	//elevator
	file = "../models/cessna/elevator.obj";
	std::cout << "Loading " << file << "...\n";
	if (!_gsm8.load(file)) std::cout << "Error!\n";
	//printInfo(_gsm8);
	_gsm8.scale(f);
	elevator.build(_gsm8);

	file = "../models/Proton.obj";
	std::cout << "Loading " << file << "...\n";
	//if (!_gsm11.load(file)) std::cout << "Error!\n";
	//printInfo(_gsm8);
	_gsm11.scale(.0005f);
	rocket.build(_gsm11);

	//the ground plane, not the airplane
	plane.build();

	redraw();
	
 }

// mouse events are in window coordinates, but your 2D scene is in [0,1]x[0,1],
// so make here the conversion when needed
GsVec2 AppWindow::windowToScene ( const GsVec2& v )
 {
   // GsVec2 is a lighteweight class suitable to return by value:
   return GsVec2 ( (2.0f*(v.x/float(_w))) - 1.0f,
                    1.0f - (2.0f*(v.y/float(_h))) );
 }

// Called every time there is a window event
void AppWindow::glutKeyboard ( unsigned char key, int x, int y )
 {
   switch ( key )
    { //case ' ': _viewaxis = !_viewaxis; redraw(); break;
	  case 27 : exit(1); // Esc was pressed
		//pitch
	  case 'q':
		  //ascend
		  //body
		  body_direction = 1;
		  bodyRotPitch++;
		  ComputeBodyTrans(bodyTransPitch, bodyRotPitch, body_direction);
		  //elevator
		  if(elevatorRot < 10)
			elevatorRot++;
		  ComputeElevatorTrans(elevatorTrans);
		  redraw();
		  break;
	  case 'a':
		  //descend
		  body_direction = 1;
		  bodyRotPitch--;
		  ComputeBodyTrans(bodyTransPitch, bodyRotPitch, body_direction);
		  //elevator
		  if(elevatorRot > -10)
			elevatorRot--;
		  ComputeElevatorTrans(elevatorTrans);
		  redraw();
		  break;

		//roll
	  case 'w':
		  //right roll
		  //body
		  body_direction = 2;
		  bodyRotRoll++;
		  ComputeBodyTrans(bodyTransRoll, bodyRotRoll, body_direction);
		  //flap
		  if(flapsRot > -10)
			flapsRot--;	//flap goes down
		  ComputeFarLeftFlapTrans(farLeftFlapsTrans);
		  ComputeCenterLeftFlapTrans(centerLeftFlapsTrans);
		  ComputeFarRightFlapTrans(farRightFlapsTrans);
		  ComputeCenterRightFlapTrans(centerRightFlapsTrans);
		  redraw();
		  break;
	  case 'r':
		  farLeftFlapsRot++;
		  ComputeFarLeftFlapTrans(farLeftFlapsTrans);
		  break;
	  case 'f':
		  farLeftFlapsRot--;
		  ComputeFarLeftFlapTrans(farLeftFlapsTrans);
		  break;
	  case 't':
		  centerLeftFlapsRot++;
		  ComputeCenterLeftFlapTrans(centerLeftFlapsTrans);
		  break;
	  case 'g':
		  centerLeftFlapsRot--;
		  ComputeCenterLeftFlapTrans(centerLeftFlapsTrans);
		  break;
	  case 'y':
		  centerRightFlapsRot++;
		  ComputeCenterRightFlapTrans(centerRightFlapsTrans);
		  break;
	  case 'h':
		  centerRightFlapsRot--;
		  ComputeCenterRightFlapTrans(centerRightFlapsTrans);
		  break;
	  case 'u':
		  farRightFlapsRot++;
		ComputeFarRightFlapTrans(farRightFlapsTrans);
		break;
	  case'j':
		  farRightFlapsRot--;
		  ComputeFarRightFlapTrans(farRightFlapsTrans);
		  break;
	  case 'i':
		  propRot++;
		  ComputePropTrans(propTrans, propRot);
		  break;
	  case 'k':
		  propRot--;
		ComputePropTrans2(propTrans2, propRot);
		break;
	  case 's':
		  //left roll
		  body_direction = 2;
		  bodyRotRoll--;
		  ComputeBodyTrans(bodyTransRoll, bodyRotRoll, body_direction);
		  //flap
		  if(flapsRot < 10)
			flapsRot++;	//flap goes up
		  ComputeFarLeftFlapTrans(farLeftFlapsTrans);
		  ComputeCenterLeftFlapTrans(centerLeftFlapsTrans);
		  ComputeFarRightFlapTrans(farRightFlapsTrans);
		  ComputeCenterRightFlapTrans(centerRightFlapsTrans);
		  redraw();
		  break;
		  
		  //yaw
	  case 'e':
		  //right yaw
		  //body
		  body_direction = 3;
		  bodyRotYaw++;
		  ComputeBodyTrans(bodyTransYaw, bodyRotYaw, body_direction);
		  //rudder
		  if(rudderRot < 10)
			rudderRot++;
		  ComputeRudderTrans(rudderTrans);
		  redraw();
		  break;
	  case 'd':
		  //left yaw
		  //body
		  body_direction = 3;
		  bodyRotYaw--;
		  ComputeBodyTrans(bodyTransYaw, bodyRotYaw, body_direction);
		  //rudder
		  if(rudderRot > -10)
			rudderRot--;
		  ComputeRudderTrans(rudderTrans);
		  redraw();
		  break;

	  case ' ': cam = !cam; break;

      default : 
                break;
	}
 }

void AppWindow::glutSpecial ( int key, int x, int y )
 {
   bool rd=true;
   const float incr=GS_TORAD(2.5f);
   const float incf=0.05f;
   switch ( key )
    { case GLUT_KEY_LEFT:      _roty-=incr; break;
      case GLUT_KEY_RIGHT:     _roty+=incr; break;
	  case GLUT_KEY_UP:		    moveForward(movement); move++; redraw(); break;
      case GLUT_KEY_DOWN:      _rotx-=incr; break;
      case GLUT_KEY_PAGE_UP:   _fovy-=incf; break;
      case GLUT_KEY_PAGE_DOWN: _fovy+=incf; break;
      default: return; // return without rendering
	}
   if (rd) redraw(); // ask the window to be rendered when possible
 }

void AppWindow::glutMouse ( int b, int s, int x, int y )
 {
   // The mouse is not used in this example.
   // Recall that a mouse click in the screen corresponds
   // to a whole line traversing the 3D scene.
 }

void AppWindow::glutMotion ( int x, int y )
 {
 }

void AppWindow::glutMenu ( int m )
 {
   std::cout<<"Menu Event: "<<m<<std::endl;
 }

void AppWindow::glutReshape ( int w, int h )
 {
   // Define that OpenGL should use the whole window for rendering
   glViewport( 0, 0, w, h );
   _w=w; _h=h;
 }

void AppWindow::moveForward(GsMat &TransMatrix) {
	offset = -.01f * move;
	TransMatrix[0] = 1.0f;
	TransMatrix[1] = 0.0f;
	TransMatrix[2] = 0.0f;
	TransMatrix[3] = 0.0f + offset;

	TransMatrix[4] = 0.0f;
	TransMatrix[5] = 1.0f;
	TransMatrix[6] = 0.0f;
	TransMatrix[7] = 0.0f;

	TransMatrix[8] = 0.0f;
	TransMatrix[9] = 0.0f;
	TransMatrix[10] = 1.0f;
	TransMatrix[11] = 0.0f;

	TransMatrix[12] = 0.0f;
	TransMatrix[13] = 0.0f;
	TransMatrix[14] = 0.0f;
	TransMatrix[15] = 1.0f;
}

void AppWindow::ComputeCenterRightFlapTrans(GsMat &TransMatrix) {
	float shift = .20f;
	float theta = (-3.14159265358979323846 / 45) * centerRightFlapsRot;

	TransMatrix[0] = 1.0f;
	TransMatrix[1] = 0.0f;
	TransMatrix[2] = 0.0f;
	TransMatrix[3] = 0.0f + shift * .3f;//    -offset;// +.01f * move;

	TransMatrix[4] = 0.0f;
	TransMatrix[5] = 1.0f;
	TransMatrix[6] = 0.0f;
	TransMatrix[7] = 0.0f + shift * 1.1f;

	TransMatrix[8] = 0.0f;
	TransMatrix[9] = 0.0f;
	TransMatrix[10] = 1.0f;
	TransMatrix[11] = 0.0f + shift;

	TransMatrix[12] = 0.0f;
	TransMatrix[13] = 0.0f;
	TransMatrix[14] = 0.0f;
	TransMatrix[15] = 1.0f;

	GsMat rotate;
	rotate[0] = cos(theta);
	rotate[1] = -sin(theta);
	rotate[2] = 0.0f;
	rotate[3] = 0.0f;

	rotate[4] = sin(theta);
	rotate[5] = cos(theta);
	rotate[6] = 0.0f;
	rotate[7] = 0.0f;

	rotate[8] = 0.0f;
	rotate[9] = 0.0f;
	rotate[10] = 1.0f;
	rotate[11] = 0.0f;

	rotate[12] = 0.0f;
	rotate[13] = 0.0f;
	rotate[14] = 0.0f;
	rotate[15] = 1.0f;

	GsMat translate;
	translate[0] = 1.0f;
	translate[1] = 0.0f;
	translate[2] = 0.0f;
	translate[3] = 0.0f - shift * .3f;//     +offset;

	translate[4] = 0.0f;
	translate[5] = 1.0f;
	translate[6] = 0.0f;
	translate[7] = 0.0f - shift *1.1f;

	translate[8] = 0.0f;
	translate[9] = 0.0f;
	translate[10] = 1.0f;
	translate[11] = 0.0f - shift;

	translate[12] = 0.0f;
	translate[13] = 0.0f;
	translate[14] = 0.0f;
	translate[15] = 1.0f;
	TransMatrix = translate * rotate*TransMatrix;
}

void AppWindow::ComputeCenterLeftFlapTrans(GsMat &TransMatrix){
	float shift = .20f;
	float theta = (3.14159265358979323846 / 45) * centerLeftFlapsRot;

	TransMatrix[0] = 1.0f;
	TransMatrix[1] = 0.0f;
	TransMatrix[2] = 0.0f;
	TransMatrix[3] = 0.0f + shift * .3f;//    -offset;

	TransMatrix[4] = 0.0f;
	TransMatrix[5] = 1.0f;
	TransMatrix[6] = 0.0f;
	TransMatrix[7] = 0.0f + shift * 1.1f;

	TransMatrix[8] = 0.0f;
	TransMatrix[9] = 0.0f;
	TransMatrix[10] = 1.0f;
	TransMatrix[11] = 0.0f - shift;

	TransMatrix[12] = 0.0f;
	TransMatrix[13] = 0.0f;
	TransMatrix[14] = 0.0f;
	TransMatrix[15] = 1.0f;

	GsMat rotate;
	rotate[0] = cos(theta);
	rotate[1] = -sin(theta);
	rotate[2] = 0.0f;
	rotate[3] = 0.0f;

	rotate[4] = sin(theta);
	rotate[5] = cos(theta);
	rotate[6] = 0.0f;
	rotate[7] = 0.0f;

	rotate[8] = 0.0f;
	rotate[9] = 0.0f;
	rotate[10] = 1.0f;
	rotate[11] = 0.0f;

	rotate[12] = 0.0f;
	rotate[13] = 0.0f;
	rotate[14] = 0.0f;
	rotate[15] = 1.0f;

	GsMat translate;
	translate[0] = 1.0f;
	translate[1] = 0.0f;
	translate[2] = 0.0f;
	translate[3] = 0.0f - shift * .3f;//    +offset;

	translate[4] = 0.0f;
	translate[5] = 1.0f;
	translate[6] = 0.0f;
	translate[7] = 0.0f - shift *1.1f;

	translate[8] = 0.0f;
	translate[9] = 0.0f;
	translate[10] = 1.0f;
	translate[11] = 0.0f + shift;

	translate[12] = 0.0f;
	translate[13] = 0.0f;
	translate[14] = 0.0f;
	translate[15] = 1.0f;
	TransMatrix = translate *rotate*TransMatrix;
}

void AppWindow::ComputeFarLeftFlapTrans(GsMat &TransMatrix) {
	//when rolling, opposite flap goes does down
	//right roll, left flap goes down and right flap goes up
	float shift = .8f;
	float theta = (3.14159265358979323846 / 45) * farLeftFlapsRot;

	TransMatrix[0] = 1.0f;
	TransMatrix[1] = 0.0f;
	TransMatrix[2] = 0.0f;
	TransMatrix[3] = 0.0f + shift * .2f;//    -offset;

	TransMatrix[4] = 0.0f;
	TransMatrix[5] = 1.0f;
	TransMatrix[6] = 0.0f;
	TransMatrix[7] = 0.0f + shift * .25f;

	TransMatrix[8] = 0.0f;
	TransMatrix[9] = 0.0f;
	TransMatrix[10] = 1.0f;
	TransMatrix[11] = 0.0f - shift;

	TransMatrix[12] = 0.0f;
	TransMatrix[13] = 0.0f;
	TransMatrix[14] = 0.0f;
	TransMatrix[15] = 1.0f;

	GsMat rotate;
	rotate[0] = cos(theta);
	rotate[1] = -sin(theta);
	rotate[2] = 0.0f;
	rotate[3] = 0.0f;

	rotate[4] = sin(theta);
	rotate[5] = cos(theta);
	rotate[6] = 0.0f;
	rotate[7] = 0.0f;

	rotate[8] = 0.0f;
	rotate[9] = 0.0f;
	rotate[10] = 1.0f;
	rotate[11] = 0.0f;

	rotate[12] = 0.0f;
	rotate[13] = 0.0f;
	rotate[14] = 0.0f;
	rotate[15] = 1.0f;

	GsMat translate;
	translate[0] = 1.0f;
	translate[1] = 0.0f;
	translate[2] = 0.0f;
	translate[3] = 0.0f - shift * .2f;//   +offset;

	translate[4] = 0.0f;
	translate[5] = 1.0f;
	translate[6] = 0.0f;
	translate[7] = 0.0f - shift * .25f;

	translate[8] = 0.0f;
	translate[9] = 0.0f;
	translate[10] = 1.0f;
	translate[11] = 0.0f + shift;

	translate[12] = 0.0f;
	translate[13] = 0.0f;
	translate[14] = 0.0f;
	translate[15] = 1.0f;
	TransMatrix = translate * rotate *  TransMatrix;
}

void AppWindow::ComputeFarRightFlapTrans(GsMat &TransMatrix) {
	//when rolling, opposite flap goes does down
	//right roll, left flap goes down and right flap goes up
	float shift = .8f;
	float theta = (-3.14159265358979323846 / 45) * farRightFlapsRot;

	TransMatrix[0] = 1.0f;
	TransMatrix[1] = 0.0f;
	TransMatrix[2] = 0.0f;
	TransMatrix[3] = 0.0f + shift * .2f;//    -offset;

	TransMatrix[4] = 0.0f;
	TransMatrix[5] = 1.0f;
	TransMatrix[6] = 0.0f;
	TransMatrix[7] = 0.0f + shift * .25f;

	TransMatrix[8] = 0.0f;
	TransMatrix[9] = 0.0f;
	TransMatrix[10] = 1.0f;
	TransMatrix[11] = 0.0f + shift;

	TransMatrix[12] = 0.0f;
	TransMatrix[13] = 0.0f;
	TransMatrix[14] = 0.0f;
	TransMatrix[15] = 1.0f;

	GsMat rotate;
	rotate[0] = cos(theta);
	rotate[1] = -sin(theta);
	rotate[2] = 0.0f;
	rotate[3] = 0.0f;

	rotate[4] = sin(theta);
	rotate[5] = cos(theta);
	rotate[6] = 0.0f;
	rotate[7] = 0.0f;

	rotate[8] = 0.0f;
	rotate[9] = 0.0f;
	rotate[10] = 1.0f;
	rotate[11] = 0.0f;

	rotate[12] = 0.0f;
	rotate[13] = 0.0f;
	rotate[14] = 0.0f;
	rotate[15] = 1.0f;

	GsMat translate;
	translate[0] = 1.0f;
	translate[1] = 0.0f;
	translate[2] = 0.0f;
	translate[3] = 0.0f - shift * .2f;//  +offset;

	translate[4] = 0.0f;
	translate[5] = 1.0f;
	translate[6] = 0.0f;
	translate[7] = 0.0f - shift * .25f;

	translate[8] = 0.0f;
	translate[9] = 0.0f;
	translate[10] = 1.0f;
	translate[11] = 0.0f - shift;

	translate[12] = 0.0f;
	translate[13] = 0.0f;
	translate[14] = 0.0f;
	translate[15] = 1.0f;
	TransMatrix = translate * rotate *  TransMatrix;
}

void AppWindow::ComputePropTrans(GsMat &TransMatrix, int i) {
	float shift = -.39f;
	float theta = (-3.14159265358979323846 / 120)*i;

	TransMatrix[0] = 1.0f;
	TransMatrix[1] = 0.0f;
	TransMatrix[2] = 0.0f;
	TransMatrix[3] = 0.0f - shift*1.45;//    -offset;

	TransMatrix[4] = 0.0f;
	TransMatrix[5] = 1.0f;
	TransMatrix[6] = 0.0f;
	TransMatrix[7] = 0.0f - shift*.46f;

	TransMatrix[8] = 0.0f;
	TransMatrix[9] = 0.0f;
	TransMatrix[10] = 1.0f;
	TransMatrix[11] = 0.0f + shift;

	TransMatrix[12] = 0.0f;
	TransMatrix[13] = 0.0f;
	TransMatrix[14] = 0.0f;
	TransMatrix[15] = 1.0f;

	GsMat rotate;
	rotate[0] = 1.0f;
	rotate[1] = 0.0f;
	rotate[2] = 0.0f;
	rotate[3] = 0.0f;

	rotate[4] = 0.0f;
	rotate[5] = cos(theta);
	rotate[6] = -sin(theta);
	rotate[7] = 0.0f;

	rotate[8] = 0.0f;
	rotate[9] = sin(theta);
	rotate[10] = cos(theta);
	rotate[11] = 0.0f;

	rotate[12] = 0.0f;
	rotate[13] = 0.0f;
	rotate[14] = 0.0f;
	rotate[15] = 1.0f;

	GsMat translate;
	translate[0] = 1.0f;
	translate[1] = 0.0f;
	translate[2] = 0.0f;
	translate[3] = 0.0f + shift*1.45f;//    +offset;

	translate[4] = 0.0f;
	translate[5] = 1.0f;
	translate[6] = 0.0f;
	translate[7] = 0.0f + shift*.46f;

	translate[8] = 0.0f;
	translate[9] = 0.0f;
	translate[10] = 1.0f;
	translate[11] = 0.0f - shift;

	translate[12] = 0.0f;
	translate[13] = 0.0f;
	translate[14] = 0.0f;
	translate[15] = 1.0f;

	TransMatrix = translate* rotate * TransMatrix;
}

void AppWindow::ComputePropTrans2(GsMat &TransMatrix, int i) {
	float shift = -.39f;
	float theta = (-3.14159265358979323846 / 120)*i;

	TransMatrix[0] = 1.0f;
	TransMatrix[1] = 0.0f;
	TransMatrix[2] = 0.0f;
	TransMatrix[3] = 0.0f - shift*1.45       - offset;

	TransMatrix[4] = 0.0f;
	TransMatrix[5] = 1.0f;
	TransMatrix[6] = 0.0f;
	TransMatrix[7] = 0.0f - shift*.46f;

	TransMatrix[8] = 0.0f;
	TransMatrix[9] = 0.0f;
	TransMatrix[10] = 1.0f;
	TransMatrix[11] = 0.0f - shift;

	TransMatrix[12] = 0.0f;
	TransMatrix[13] = 0.0f;
	TransMatrix[14] = 0.0f;
	TransMatrix[15] = 1.0f;

	GsMat rotate;
	rotate[0] = 1.0f;
	rotate[1] = 0.0f;
	rotate[2] = 0.0f;
	rotate[3] = 0.0f;

	rotate[4] = 0.0f;
	rotate[5] = cos(theta);
	rotate[6] = -sin(theta);
	rotate[7] = 0.0f;

	rotate[8] = 0.0f;
	rotate[9] = sin(theta);
	rotate[10] = cos(theta);
	rotate[11] = 0.0f;

	rotate[12] = 0.0f;
	rotate[13] = 0.0f;
	rotate[14] = 0.0f;
	rotate[15] = 1.0f;

	GsMat translate;
	translate[0] = 1.0f;
	translate[1] = 0.0f;
	translate[2] = 0.0f;
	translate[3] = 0.0f + shift*1.45f     + offset;

	translate[4] = 0.0f;
	translate[5] = 1.0f;
	translate[6] = 0.0f;
	translate[7] = 0.0f + shift*.46f;

	translate[8] = 0.0f;
	translate[9] = 0.0f;
	translate[10] = 1.0f;
	translate[11] = 0.0f + shift;

	translate[12] = 0.0f;
	translate[13] = 0.0f;
	translate[14] = 0.0f;
	translate[15] = 1.0f;

	TransMatrix = translate * rotate * TransMatrix;
}

void AppWindow::ComputeRudderTrans(GsMat &TransMatrix) {
	float shift = -.39f;
	float theta = (3.14159265358979323846 / 60) * rudderRot;

	TransMatrix[0] = 1.0f;
	TransMatrix[1] = 0.0f;
	TransMatrix[2] = 0.0f;
	TransMatrix[3] = 0.0f + 2 * shift;// -offset;

	TransMatrix[4] = 0.0f;
	TransMatrix[5] = 1.0f;
	TransMatrix[6] = 0.0f;
	TransMatrix[7] = 0.0f - shift*.345;

	TransMatrix[8] = 0.0f;
	TransMatrix[9] = 0.0f;
	TransMatrix[10] = 1.0f;
	TransMatrix[11] = 0.0f;

	TransMatrix[12] = 0.0f;
	TransMatrix[13] = 0.0f;
	TransMatrix[14] = 0.0f;
	TransMatrix[15] = 1.0f;

	GsMat rotate;
	rotate[0] = cos(theta);
	rotate[1] = 0.0f;
	rotate[2] = sin(theta);
	rotate[3] = 0.0f;

	rotate[4] = 0.0f;
	rotate[5] = 1.0f;
	rotate[6] = 0.0f;
	rotate[7] = 0.0f;

	rotate[8] = -sin(theta);
	rotate[9] = 0.0f;
	rotate[10] = cos(theta);
	rotate[11] = 0.0f;

	rotate[12] = 0.0f;
	rotate[13] = 0.0f;
	rotate[14] = 0.0f;
	rotate[15] = 1.0f;

	GsMat translate;
	translate[0] = 1.0f;
	translate[1] = 0.0f;
	translate[2] = 0.0f;
	translate[3] = 0.0f - shift*2.0f;// +offset;

	translate[4] = 0.0f;
	translate[5] = 1.0f;
	translate[6] = 0.0f;
	translate[7] = 0.0f + shift*.345f;

	translate[8] = 0.0f;
	translate[9] = 0.0f;
	translate[10] = 1.0f;
	translate[11] = 0.0f;

	translate[12] = 0.0f;
	translate[13] = 0.0f;
	translate[14] = 0.0f;
	translate[15] = 1.0f;

	TransMatrix = translate* rotate * TransMatrix;
}

void AppWindow::ComputeElevatorTrans(GsMat &TransMatrix) {
	float shift = -.39f;
	float theta = (3.14159265358979323846 / 60)*elevatorRot;

	TransMatrix[0] = 1.0f;
	TransMatrix[1] = 0.0f;
	TransMatrix[2] = 0.0f;
	TransMatrix[3] = 0.0f + 2 * shift;//     -offset;

	TransMatrix[4] = 0.0f;
	TransMatrix[5] = 1.0f;
	TransMatrix[6] = 0.0f;
	TransMatrix[7] = 0.0f - shift*.345;

	TransMatrix[8] = 0.0f;
	TransMatrix[9] = 0.0f;
	TransMatrix[10] = 1.0f;
	TransMatrix[11] = 0.0f;

	TransMatrix[12] = 0.0f;
	TransMatrix[13] = 0.0f;
	TransMatrix[14] = 0.0f;
	TransMatrix[15] = 1.0f;
	
	GsMat rotate;
	rotate[0] = cos(theta);
	rotate[1] = -sin(theta);
	rotate[2] = 0.0f;
	rotate[3] = 0.0f;

	rotate[4] = sin(theta);
	rotate[5] = cos(theta);
	rotate[6] = 0.0f;
	rotate[7] = 0.0f;

	rotate[8] = 0.0f;
	rotate[9] = 0.0f;
	rotate[10] = 1.0f;
	rotate[11] = 0.0f;

	rotate[12] = 0.0f;
	rotate[13] = 0.0f;
	rotate[14] = 0.0f;
	rotate[15] = 1.0f;
	
	GsMat translate;
	translate[0] = 1.0f;
	translate[1] = 0.0f;
	translate[2] = 0.0f;
	translate[3] = 0.0f - shift*2.0f;//   +offset;

	translate[4] = 0.0f;
	translate[5] = 1.0f;
	translate[6] = 0.0f;
	translate[7] = 0.0f + shift*.345f;

	translate[8] = 0.0f;
	translate[9] = 0.0f;
	translate[10] = 1.0f;
	translate[11] = 0.0f;

	translate[12] = 0.0f;
	translate[13] = 0.0f;
	translate[14] = 0.0f;
	translate[15] = 1.0f;

	TransMatrix = translate* rotate * TransMatrix;
}

void AppWindow::ComputeRocket(GsMat &TransMatrix) {
	float theta = 3.14159265358979323846/2;

	TransMatrix[0] = 1.0f;
	TransMatrix[1] = 0.0f;
	TransMatrix[2] = 0.0f;
	TransMatrix[3] = 0.0f;

	TransMatrix[4] = 0.0f;
	TransMatrix[5] = 1.0f;
	TransMatrix[6] = 0.0f;
	TransMatrix[7] = 0.0f - 2.5f;

	TransMatrix[8] = 0.0f;
	TransMatrix[9] = 0.0f;
	TransMatrix[10] = 1.0f;
	TransMatrix[11] = 0.0f;

	TransMatrix[12] = 0.0f;
	TransMatrix[13] = 0.0f;
	TransMatrix[14] = 0.0f;
	TransMatrix[15] = 1.0f;

	GsMat rotate;
	rotate[0] = cos(theta);
	rotate[1] = -sin(theta);
	rotate[2] = 0.0f;
	rotate[3] = 0.0f;

	rotate[4] = sin(theta);
	rotate[5] = cos(theta);
	rotate[6] = 0.0f;
	rotate[7] = 0.0f;

	rotate[8] = 0.0f;
	rotate[9] = 0.0f;
	rotate[10] = 1.0f;
	rotate[11] = 0.0f;

	rotate[12] = 0.0f;
	rotate[13] = 0.0f;
	rotate[14] = 0.0f;
	rotate[15] = 1.0f;

	TransMatrix = rotate * TransMatrix;
}

void AppWindow::ComputeBodyTrans(GsMat &TransMatrix, int i, int direction) {
	float shift = -.165;
	float theta = (-3.14159265358979323846 / 60)*i;

	TransMatrix[0] = 1.0f;
	TransMatrix[1] = 0.0f;
	TransMatrix[2] = 0.0f;
	TransMatrix[3] = 0.0f -offset;

	TransMatrix[4] = 0.0f;
	TransMatrix[5] = 1.0f;
	TransMatrix[6] = 0.0f;
	TransMatrix[7] = 0.0f;

	TransMatrix[8] = 0.0f;
	TransMatrix[9] = 0.0f;
	TransMatrix[10] = 1.0f;
	TransMatrix[11] = 0.0f;

	TransMatrix[12] = 0.0f;
	TransMatrix[13] = 0.0f;
	TransMatrix[14] = 0.0f;
	TransMatrix[15] = 1.0f;

	GsMat rotate;
	//pitch
	if (direction == 1) {
		rotate[0] = cos(theta);
		rotate[1] = -sin(theta);
		rotate[2] = 0.0f;
		rotate[3] = 0.0f;

		rotate[4] = sin(theta);
		rotate[5] = cos(theta);
		rotate[6] = 0.0f;
		rotate[7] = 0.0f;

		rotate[8] = 0.0f;
		rotate[9] = 0.0f;
		rotate[10] = 1.0f;
		rotate[11] = 0.0f;

		rotate[12] = 0.0f;
		rotate[13] = 0.0f;
		rotate[14] = 0.0f;
		rotate[15] = 1.0f;
	}
	//roll
	else if (direction == 2) {
		rotate[0] = 1.0f;
		rotate[1] = 0.0f;
		rotate[2] = 0.0f;
		rotate[3] = 0.0f;

		rotate[4] = 0.0f;
		rotate[5] = cos(theta);
		rotate[6] = -sin(theta);
		rotate[7] = 0.0f;

		rotate[8] = 0.0f;
		rotate[9] = sin(theta);
		rotate[10] = cos(theta);
		rotate[11] = 0.0f;

		rotate[12] = 0.0f;
		rotate[13] = 0.0f;
		rotate[14] = 0.0f;
		rotate[15] = 1.0f;
	}
	//yaw
	else if (direction == 3) {
		rotate[0] = cos(theta);
		rotate[1] = 0.0f;
		rotate[2] = sin(theta);
		rotate[3] = 0.0f;

		rotate[4] = 0.0f;
		rotate[5] = 1.0f;
		rotate[6] = 0.0f;
		rotate[7] = 0.0f;

		rotate[8] = -sin(theta);
		rotate[9] = 0.0f;
		rotate[10] = cos(theta);
		rotate[11] = 0.0f;

		rotate[12] = 0.0f;
		rotate[13] = 0.0f;
		rotate[14] = 0.0f;
		rotate[15] = 1.0f;
	}

	GsMat translate;
	translate[0] = 1.0f;
	translate[1] = 0.0f;
	translate[2] = 0.0f;
	translate[3] = 0.0f +offset;

	translate[4] = 0.0f;
	translate[5] = 1.0f;
	translate[6] = 0.0f;
	translate[7] = 0.0f;

	translate[8] = 0.0f;
	translate[9] = 0.0f;
	translate[10] = 1.0f;
	translate[11] = 0.0f;

	translate[12] = 0.0f;
	translate[13] = 0.0f;
	translate[14] = 0.0f;
	translate[15] = 1.0f;

	TransMatrix = translate* rotate * TransMatrix;
}

void AppWindow::ComputeShadowTrans(GsMat &TransMatrix, float l_x, float l_y, float l_z) {

	float light[4] = { l_x, l_y, l_z, 1.0 };
	float normal[4] = { 0.0, 1.0, 0.0, 1.0 };

	float dot = normal[0] * light[0] +
				normal[1] * light[1] +
				normal[2] * light[2] +
				normal[3] * light[3];

	TransMatrix[0] = dot - light[0] * normal[0];
	TransMatrix[1] = 0.0f - light[0] * normal[1];
	TransMatrix[2] = 0.0f - light[0] * normal[2];
	TransMatrix[3] = 0.0f - light[0] * normal[3];

	TransMatrix[4] = 0.0f - light[1] * normal[0];
	TransMatrix[5] = dot - light[1] * normal[1];
	TransMatrix[6] = 0.0f - light[1] * normal[2];
	TransMatrix[7] = 0.0f - light[1] * normal[3];

	TransMatrix[8] = 0.0f - light[2] * normal[0];
	TransMatrix[9] = 0.0f - light[2] * normal[1];
	TransMatrix[10] = dot - light[2] * normal[2];
	TransMatrix[11] = 0.0f - light[2] * normal[3];

	TransMatrix[12] = 0.0f - light[3] * normal[0];
	TransMatrix[13] = 0.0f - light[3] * normal[1];
	TransMatrix[14] = 0.0f - light[3] * normal[2];
	TransMatrix[15] = dot - light[3] * normal[3];
}

void AppWindow::glutIdle() {
	//propRot++;
	redraw();
}

// here we will redraw the scene according to the current state of the application.
void AppWindow::glutDisplay ()
 {
   // Clear the rendering window
   glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   // Build a cross with some lines (if not built yet):
   if ( _axis.changed ) // needs update
    { _axis.build(1.0f); // axis has radius 1.0
    }

   // Define our scene transformation:
   GsMat rx, ry, stransf;
   rx.rotx ( _rotx );
   ry.roty ( _roty );
   stransf = rx*ry; // set the scene transformation matrix

   //rocket
   ComputeRocket(rocketTrans);
	//propeller
   ComputePropTrans(propTrans, propRot);
   ComputePropTrans2(propTrans2, propRot);
   ComputeBodyTrans(bodySet, 0, 0);
   //shadow
   ComputeShadowTrans(ShadowTrans, lx, ly, lz);

   // Define our projection transformation:
   // (see demo program in gltutors-projection.7z, we are replicating the same behavior here)
   GsMat camview, persp, sproj;
   if (cam) {
	   GsVec eye(0, 0, 3), center(0, 0, 0), up(0, 1, 0);
	   camview.lookat(eye, center, up); // set our 4x4 "camera" matrix

   }
   else {	//camera following plane
	   GsVec eye(-offset, 2, 0), center(0, 0, 0), up(-1, 0, 0);
	   camview.lookat(eye, center, up); // set our 4x4 "camera" matrix
   }

   float aspect=1.0f, znear=0.1f, zfar=50.0f;
   persp.perspective ( _fovy, aspect, znear, zfar ); // set our 4x4 perspective matrix

   // Our matrices are in "line-major" format, so vertices should be multiplied on the 
   // right side of a matrix multiplication, therefore in the expression below camview will
   // affect the vertex before persp, because v' = (persp*camview)*v = (persp)*(camview*v).
   sproj = persp * camview; // set final scene projection

   //  Note however that when the shader receives a matrix it will store it in column-major 
   //  format, what will cause our values to be transposed, and we will then have in our 
   //  shaders vectors on the left side of a multiplication to a matrix.

   // Draw:
   if ( false ) _axis.draw ( stransf, sproj );
   
   //ground
   plane.draw(stransf, sproj, _light);

   rocket.draw(stransf * rocketTrans, sproj, _light);
   
   //airplane
   body.draw ( stransf* movement* bodyTransPitch * bodyTransRoll * bodyTransYaw, sproj, _light );
   prop.draw(stransf * movement*bodyTransPitch * bodyTransRoll * bodyTransYaw * propTrans, sproj, _light);
   prop2.draw(stransf * movement*bodyTransPitch * bodyTransRoll * bodyTransYaw * propTrans2, sproj, _light);
   elevator.draw(stransf * movement*bodyTransPitch * bodyTransRoll * bodyTransYaw, sproj, _light);
   rudder.draw(stransf *movement*bodyTransPitch * bodyTransRoll * bodyTransYaw * rudderTrans, sproj, _light);
   farleftflaps.draw(stransf * movement*bodyTransPitch *bodyTransRoll * bodyTransYaw * farLeftFlapsTrans, sproj, _light);
   centerleftflaps.draw(stransf * movement*bodyTransPitch * bodyTransRoll * bodyTransYaw * centerLeftFlapsTrans, sproj, _light);
   centerrightflaps.draw(stransf * movement*bodyTransPitch * bodyTransRoll* bodyTransYaw * centerRightFlapsTrans, sproj, _light);
   farrightflaps.draw(stransf *movement* bodyTransPitch * bodyTransRoll* bodyTransYaw * farRightFlapsTrans, sproj, _light);
   rflaps.draw(stransf * movement*bodyTransPitch * bodyTransRoll* bodyTransYaw * elevatorTrans, sproj, _light);


   //shadow
   body.draw(stransf *movement * ShadowTrans* bodyTransPitch * bodyTransRoll * bodyTransYaw, sproj, _light);
   prop.draw(stransf * movement *ShadowTrans* bodyTransPitch * bodyTransRoll * bodyTransYaw, sproj, _light);
   prop2.draw(stransf * movement * ShadowTrans*bodyTransPitch * bodyTransRoll * bodyTransYaw, sproj, _light);
   rudder.draw(stransf * movement * ShadowTrans* bodyTransPitch * bodyTransRoll* bodyTransYaw * rudderTrans, sproj, _light);
   elevator.draw(stransf *movement * ShadowTrans*bodyTransPitch * bodyTransRoll * bodyTransYaw, sproj, _light);
   //flaps
   farleftflaps.draw(stransf *movement * ShadowTrans* bodyTransPitch *bodyTransRoll * bodyTransYaw * farLeftFlapsTrans, sproj, _light);
   centerleftflaps.draw(stransf * movement * ShadowTrans*bodyTransPitch * bodyTransRoll * bodyTransYaw * centerLeftFlapsTrans, sproj, _light);
   centerrightflaps.draw(stransf *movement * ShadowTrans* bodyTransPitch * bodyTransRoll* bodyTransYaw * centerRightFlapsTrans, sproj, _light);
   farrightflaps.draw(stransf *movement * ShadowTrans* bodyTransPitch * bodyTransRoll* bodyTransYaw * farRightFlapsTrans, sproj, _light);
   rflaps.draw(stransf * movement *ShadowTrans*bodyTransPitch * bodyTransRoll* bodyTransYaw * elevatorTrans, sproj, _light);

   // Swap buffers and draw:
   glFlush();         // flush the pipeline (usually not necessary)
   glutSwapBuffers(); // we were drawing to the back buffer, now bring it to the front
}


