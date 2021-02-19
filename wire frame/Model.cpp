#include "Model.h"

Model::Model()
{
}

Model::~Model()
{
}

const vector<Polygon3D>& Model::GetPolygons()
{
	return _polygons;
}

const vector<Vertex>& Model::GetVertices()
{
	return _vertices;
}

size_t Model::GetPolygonCount() const
{
	return _polygons.size();
}

size_t Model::GetVertexCount() const
{
	return _vertices.size();
}

void Model::AddVertex(float x, float y, float z)
{
	Vertex Vertexes(x, y, z, 1);
	_vertices.push_back(Vertexes);
}

void Model::AddPolygon(int i0, int i1, int i2)
{
	Polygon3D Polygons(i0, i1, i2);
	_polygons.push_back(Polygons);
}

void Model::TransformToVertices(const Matrix& transform)
{
	_TransformVert.clear();
	for (int I = 0; I < _vertices.size(); I++)
	{
		_TransformVert.push_back(transform * _vertices[I]);
	}
}

void Model::TransformToTransformed(const Matrix& transform)
{
	for (int I = 0; I < _TransformVert.size(); I++)
	{
		_TransformVert[I] = transform * _TransformVert[I];
	}
}

void Model::Dehomogenize()
{
	for (int I = 0; I < _TransformVert.size(); I++)
	{
		_TransformVert[I].SetX(_TransformVert[I].GetX() / _TransformVert[I].GetW());
		_TransformVert[I].SetY(_TransformVert[I].GetY() / _TransformVert[I].GetW());
		_TransformVert[I].SetZ(_TransformVert[I].GetZ() / _TransformVert[I].GetW());
		_TransformVert[I].SetW(_TransformVert[I].GetW() / _TransformVert[I].GetW());
	}
}

const vector<Vertex>& Model::GetTransformed()
{
	return _TransformVert;
}