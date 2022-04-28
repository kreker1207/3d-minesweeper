#include "Zero.h"
#include "utils.h"
#include "glut.h"
#include "Shape.h"

namespace Sapper
{
	void Zero::draw()
	{
		{
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, getAmbiColor());
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, getDiffColor());
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, getSpecColor());
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, GraphUtils::shininess);
			glPushMatrix();
			glTranslatef(getXCenter(), getYCenter() + getYSize() / 2, getZCenter());
			glRotatef(90, 1, 0, 0);
			GLUquadricObj* quadricObj = gluNewQuadric();
			gluCylinder(quadricObj, getXSize() / 2, getXSize() / 2, getYSize(), 20, 2);
			glRotatef(180, 1, 0, 0);
			gluDisk(quadricObj, innerRadius, getXSize() / 4, 20, 20);
			glTranslatef(0, 0, -getYSize());
			gluDisk(quadricObj, innerRadius, getXSize() / 4, 20, 20);
			gluDeleteQuadric(quadricObj);
			glPopMatrix();
		}
	}
}