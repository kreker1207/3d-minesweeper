#ifndef Zero_h
#define Zero_h

#include "Shape.h"

namespace Sapper {
	class Zero : public Shape {
	private:
		float innerRadius;
	public:
		Zero(float xCenter, float yCenter, float zCenter,
			float xSize, float ySize, float zSize,
			float* diffColor, float* ambiColor, float* specColor,
			float innerRadius)
			: Shape(xCenter, yCenter, zCenter, xSize, ySize, zSize, specColor, diffColor, ambiColor)
		{
			this->innerRadius = innerRadius;
		}
		float getInnerRadius() const { return innerRadius; }
		void setInnerRadius(float innerRadius) { this->innerRadius = innerRadius; }
		virtual void draw();
	};
}
#endif
#pragma once
