#include "Polygon3D.h"

Polygon3D::Polygon3D()
{
	_indices[0] = 0;
	_indices[1] = 0;
	_indices[2] = 0;
}

Polygon3D::~Polygon3D()
{
}

Polygon3D::Polygon3D(int i0, int i1, int i2)
{
	_indices[0] = i0;
	_indices[1] = i1;
	_indices[2] = i2;
}

Polygon3D::Polygon3D(const Polygon3D& p)
{
	_indices[0] = p.GetIndex(0);
	_indices[1] = p.GetIndex(1);
	_indices[2] = p.GetIndex(2);
}

int Polygon3D::GetIndex(int Index) const
{
	return _indices[Index];
}

Polygon3D& Polygon3D::operator=(const Polygon3D& rhs)
{
	if (this != &rhs)
	{
		for (int I = 0; I < 3; I++)
		{
			_indices[I] = rhs.GetIndex(I);
		}
	}

	return *this;
}