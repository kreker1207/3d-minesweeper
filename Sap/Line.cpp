#include "glut.h"
#include "Line.h"
#include "utils.h"
namespace Sapper {
	void Line::draw() {
		glMaterialfv(GL_FRONT, GL_AMBIENT, getAmbiColor());
		glMaterialfv(GL_FRONT, GL_DIFFUSE, getDiffColor());
		glMaterialfv(GL_FRONT, GL_SPECULAR, getSpecColor());
		glMaterialf(GL_FRONT, GL_SHININESS, GraphUtils::shininess);

		glPushMatrix();
		glTranslatef(getXCenter(), getYCenter() - 0.000001, getZCenter());
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		GraphUtils::parallelepiped(getXSize(), getYSize(), getZSize());
		glPopMatrix();

		
	}
	void Line2::draw() {
		glMaterialfv(GL_FRONT, GL_AMBIENT, getAmbiColor());
		glMaterialfv(GL_FRONT, GL_DIFFUSE, getDiffColor());
		glMaterialfv(GL_FRONT, GL_SPECULAR, getSpecColor());
		glMaterialf(GL_FRONT, GL_SHININESS, GraphUtils::shininess);

		glPushMatrix();
		glTranslatef(getXCenter()-0.02, getYCenter() - 0.000001, getZCenter());
		glRotatef(-70.0f, 0.0f, 1.0f, 0.0f);
		GraphUtils::parallelepiped(getXSize(), getYSize(), getZSize());
		glPopMatrix();

		glMaterialfv(GL_FRONT, GL_AMBIENT, getAmbiColor());
		glMaterialfv(GL_FRONT, GL_DIFFUSE, getDiffColor());
		glMaterialfv(GL_FRONT, GL_SPECULAR, getSpecColor());
		glMaterialf(GL_FRONT, GL_SHININESS, GraphUtils::shininess);

		glPushMatrix();
		glTranslatef(getXCenter()+0.08, getYCenter() - 0.000001, getZCenter());
		glRotatef(70.0f, 0.0f, 1.0f, 0.0f);
		GraphUtils::parallelepiped(getXSize(), getYSize(), getZSize());
		glPopMatrix();


	}

}