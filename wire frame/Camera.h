#pragma once
#include "Matrix.h"
#include <math.h>

class Camera
{
public:
	Camera(float xR, float yR, float zR, const Vertex& position);
	void SetxR(const float xR);
	void SetyR(const float yR);
	void SetzR(const float zR);
	void SetPosition(const Vertex& position);
	Matrix GetCMatrix() const;

private:
	float _RotateX;
	float _RotateY;
	float _RotateZ;
	Vertex _position;
	Matrix _MatrixX;
	Matrix _MatrixY;
	Matrix _MatrixZ;
	Matrix _NegMatrix;
	Matrix _CamMatrix;
};
