#include "Camera.h"

Camera::Camera(float xRotation, float yRotation, float zRotation, const Vertex& position)
{
	_RotateX = xRotation;
	_RotateY = yRotation;
	_RotateZ = zRotation;
	_position = position;

	_MatrixX = { 1, 0, 0, 0,
					 0, cosf(xRotation), sinf(xRotation), 0,
					 0, -sinf(xRotation), cosf(xRotation), 0,
					 0, 0, 0, 1 };
	_MatrixY = { cosf(yRotation), 0, -sinf(yRotation), 0,
				 0, 1, 0, 0,
				 sinf(yRotation), 0, cosf(yRotation), 0,
				 0, 0, 0, 1 };
	_MatrixZ = { cosf(zRotation), sinf(zRotation), 0, 0,
				 -sinf(zRotation), cosf(zRotation), 0, 0,
				 0, 0, 1, 0,
				 0, 0, 0, 1 };
	_NegMatrix = { 1, 0, 0, -position.GetX(),
				   0, 1, 0, -position.GetY(),
				   0, 0, 1, -position.GetZ(),
				   0, 0, 0, 1 };

	_CamMatrix = _MatrixX * _MatrixY * _MatrixZ * _NegMatrix;
}

void Camera::SetxR(const float xRotation)
{
	_RotateX = xRotation;
	_MatrixX = { 1, 0, 0, 0,
				 0, cosf(xRotation), sinf(xRotation), 0,
				 0, -sinf(xRotation), cosf(xRotation), 0,
				 0, 0, 0, 1 };
	_CamMatrix = _MatrixX * _MatrixY * _MatrixZ * _NegMatrix;
}

void Camera::SetyR(const float yRotation)
{
	_RotateY = yRotation;
	_MatrixY = { cosf(yRotation), 0, -sinf(yRotation), 0,
				 0, 1, 0, 0,
				 sinf(yRotation), 0, cosf(yRotation), 0,
				 0, 0, 0, 1 };
	_CamMatrix = _MatrixX * _MatrixY * _MatrixZ * _NegMatrix;
}

void Camera::SetzR(const float zRotation)
{
	_RotateZ = zRotation;
	_MatrixZ = { cosf(zRotation), sinf(zRotation), 0, 0,
				-sinf(zRotation), cosf(zRotation), 0, 0,
				 0, 0, 1, 0,
				 0, 0, 0, 1 };
	_CamMatrix = _MatrixX * _MatrixY * _MatrixZ * _NegMatrix;
}

void Camera::SetPosition(const Vertex& position)
{
	_position = position;
	_NegMatrix = { 1, 0, 0, -position.GetX(),
						 0, 1, 0, -position.GetY(),
						 0, 0, 1, -position.GetZ(),
						 0, 0, 0, 1 };
	_CamMatrix = _MatrixX * _MatrixY * _MatrixZ * _NegMatrix;
}

Matrix Camera::GetCMatrix() const
{
	return _CamMatrix;
}