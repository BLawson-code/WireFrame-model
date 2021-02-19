#include "Rasteriser.h"

Rasteriser app;

bool Rasteriser::Initialise()
{
	if (!MD2Loader::LoadModel("car.md2", _Model,
		&Model::AddPolygon,
		&Model::AddVertex))
	{
		return false;
	}

	_ModelTrans = Matrix{ 1, 0, 0, 0,
									0, 1, 0, 0,
									0, 0, 1, 0,
									0, 0, 0, 1 };

	return true;
}

void Rasteriser::Render(const Bitmap& bitmap)
{
	Camera camera(0, 0, 0, { 0.0f, 50.0f, -250.0f, 10.0f });

	HDC hdc = bitmap.GetDC();
	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, RGB(245, 245, 220));
	bitmap.Clear(RGB(0, 0, 255));
	_Model.TransformToVertices(_ModelTrans);
	_Model.TransformToTransformed(camera.GetCMatrix());
	_Model.TransformToTransformed(_Perspective);
	_Model.Dehomogenize();
	_Model.TransformToTransformed(_View);
	DrawFrames(bitmap);
}

void Rasteriser::Update(const Bitmap& bitmap)
{
	_ModelTrans = _ModelTrans * Matrix{ cosf(0.01f), 0, sinf(0.01f), 0,
										 0, 1, 0, 0,
								 -sinf(0.01f), 0, cosf(0.01f), 0,
										 0, 0, 0, 1 };

	PerspectiveMatrix(1.0f, float(bitmap.GetWidth()) / float(bitmap.GetHeight()));
	ViewMatrix(1.0f, float(bitmap.GetWidth()), float(bitmap.GetHeight()));
}

void Rasteriser::PerspectiveMatrix(float D, float AspectRatio)
{
	_Perspective = { D / AspectRatio, 0, 0, 0,
									  0,D,0,0,
									  0,0,D,0,
									  0,0,1,0 };
}

void Rasteriser::ViewMatrix(float D, float Width, float Height)
{
	_View = { Width / 2, 0, 0, Width / 2,
					0, -Height / 2, 0, Height / 2,
					0, 0, D / 2, D / 2,
					0, 0, 0, 1 };
}

void Rasteriser::DrawFrames(const Bitmap& bitmap)
{
	HDC hdc = bitmap.GetDC();

	std::vector<Polygon3D> Polygons = _Model.GetPolygons();
	std::vector<Vertex> Vertices = _Model.GetTransformed();

	for (int i = 0; i < _Model.GetPolygonCount(); i++) {
		MoveToEx(hdc, int(Vertices[Polygons[i].GetIndex(0)].GetX()), int(Vertices[Polygons[i].GetIndex(0)].GetY()), NULL);
		LineTo(hdc, int(Vertices[Polygons[i].GetIndex(1)].GetX()), int(Vertices[Polygons[i].GetIndex(1)].GetY()));
		LineTo(hdc, int(Vertices[Polygons[i].GetIndex(2)].GetX()), int(Vertices[Polygons[i].GetIndex(2)].GetY()));
		LineTo(hdc, int(Vertices[Polygons[i].GetIndex(0)].GetX()), int(Vertices[Polygons[i].GetIndex(0)].GetY()));
	}
}