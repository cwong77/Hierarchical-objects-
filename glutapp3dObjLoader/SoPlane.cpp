
# include "SoPlane.h"

SoPlane::SoPlane()
{
	_numpoints = 0;
}

void SoPlane::init()
{
	// Load programs:
	_vshtex.load_and_compile(GL_VERTEX_SHADER, "../texgouraud.vert");
	_fshtex.load_and_compile(GL_FRAGMENT_SHADER, "../texgouraud.frag");
	_progtex.init_and_link(_vshtex, _fshtex);

	// Define buffers needed:
	gen_vertex_arrays(1); // will use 1 vertex array
	gen_buffers(3);       // will use 3 buffers

	_progtex.uniform_locations(11); // will send 11 variables
	_progtex.uniform_location(0, "vTransf");
	_progtex.uniform_location(1, "vProj");
	_progtex.uniform_location(2, "lPos");
	_progtex.uniform_location(3, "la");
	_progtex.uniform_location(4, "ld");
	_progtex.uniform_location(5, "ls");
	_progtex.uniform_location(6, "ka");
	_progtex.uniform_location(7, "kd");
	_progtex.uniform_location(8, "ks");
	_progtex.uniform_location(9, "sh");
	_progtex.uniform_location(10, "Tex1");
	_progtex.uniform_location(11, "influence");

	//first image
	GsImage I;
	if (!I.load("../sky.png")) {
		std::cout << "COULD NOT LOAD IMAGE!\n"; exit(1);
	}
	else
		std::cout << "LOADED IMAGE\n";

	glGenTextures(1, &_texid);
	glBindTexture(GL_TEXTURE_2D, _texid);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, I.w(), I.h(), 0, GL_RGBA, GL_UNSIGNED_BYTE, I.data());

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);

	I.init(0, 0);
}

void SoPlane::build()
{
	NL.abandon();	//clear the normal lines array
	P.reserve(6); //C.reserve(nfaces * 6);	// reserve space to avoid re-allocations from the calls below

	GsPnt a = GsPnt(-50.0, -1.0, -50.0);
	GsPnt b = GsPnt(50.0, -1.0, -50.0);
	GsPnt c = GsPnt(50.0, -1.0, 50.0);
	GsPnt d = GsPnt(-50.0, -1.0, 50.0);
	
	P.push(a); P.push(b); P.push(c);
	P.push(a); P.push(c); P.push(d);

	for (int i = 0; i < 6; i++) {
		N.push(GsVec(0.0, 1.0, 0.0));
	}

	T.push(GsVec2(0.0, 1.0));	//bottom left
	T.push(GsVec2(1.0, 1.0));	//bottom right
	T.push(GsVec2(1.0, 0.0));	//top right
	
	T.push(GsVec2(0.0, 1.0));	//bottom left
	T.push(GsVec2(1.0, 0.0));	//top right
	T.push(GsVec2(0.0, 0.0));	//top left
	
	/* There are multiple ways to organize data to send to OpenGL.
	Here we send material information in uniforms and we only send the diffuse color
	information per vertex. The other components are uniforms sent to affect the whole object.
	This is a solution that keeps this code simple and is ok for most objects.
	*/

	//C.size(P.size()); C.setall(GsColor::green);
	_mtl.specular.set(255, 255, 255);
	_mtl.shininess = 8; // increase specular effect
	// send data to OpenGL buffers:
	glBindVertexArray(va[0]);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, buf[0]);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float)*P.size(), P.pt(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, buf[1]);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float)*N.size(), N.pt(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, buf[2]);
	glBufferData(GL_ARRAY_BUFFER, T.size() * 2 * sizeof(float), &T[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0); // break the existing vertex array object binding.

	// save size so that we can free our buffers and later draw the OpenGL arrays:
	_numpoints = P.size();

	// free non-needed memory:
	P.capacity(0); N.capacity(0); //C.capacity(0);
								  // (leave NL untouched because it will be used by another class for display)
}

void SoPlane::draw(const GsMat& tr, const GsMat& pr, const GsLight& l)
{
	float f[4];
	float sh = (float)_mtl.shininess;
	if (sh<0.001f) sh = 64;

		glUseProgram(_progtex.id);
		glBindVertexArray(va[0]);
		glBindTexture(GL_TEXTURE_2D, _texid);
		glUniformMatrix4fv(_progtex.uniloc[0], 1, GL_FALSE, tr.e);
		glUniformMatrix4fv(_progtex.uniloc[1], 1, GL_FALSE, pr.e);
		glUniform3fv(_progtex.uniloc[2], 1, l.pos.e);
		glUniform4fv(_progtex.uniloc[3], 1, l.amb.get(f));
		glUniform4fv(_progtex.uniloc[4], 1, l.dif.get(f));
		glUniform4fv(_progtex.uniloc[5], 1, l.spe.get(f));
		glUniform4fv(_progtex.uniloc[6], 1, _mtl.ambient.get(f));
		glUniform4fv(_progtex.uniloc[7], 1, _mtl.diffuse.get(f));
		glUniform4fv(_progtex.uniloc[8], 1, _mtl.specular.get(f));
		glUniform1fv(_progtex.uniloc[9], 1, &sh);
		glUniform1fv(_progtex.uniloc[11], 1, &influence);

	glDrawArrays(GL_TRIANGLES, 0, _numpoints);
	glBindVertexArray(0); // break the existing vertex array object binding.
}

