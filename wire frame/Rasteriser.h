#include "Framework.h"
#include "Vertex.h"
#include <math.h>
#include "MD2Loader.h"
#include "Camera.h"
#include "Model.h"

class Rasteriser : public Framework
{
public:
	bool Initialise();
	void Update(const Bitmap& bitmap);
	void Render(const Bitmap& bitmap);
	void PerspectiveMatrix(float D, float AspectRatio);
	void ViewMatrix(float D, float Width, float Heigh);
	void DrawFrames(const Bitmap& bitmap);

private:
	double _x{ 0 };
	double _y{ 0 };
	double _z{ 0 };
	double _w{ 0 };
	Model _Model;
	Matrix _Perspective;
	Matrix _View;
	Matrix _ModelTrans;
};
