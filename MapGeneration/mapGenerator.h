#pragma once
//////////////////////
// Include

//////////////////////
// Const
const int kSize = 257;

//////////////////////
// Forward declaration
class Camera;

//////////////////////
// Enum
enum DrawType
{
	Noise,
	Cave,
	Landscape
};

enum GenerateType
{
	Interpolating,
	DiamodAndSquare,
	PerlinNoise
};

//////////////////////
// Class MapGenerator
class MapGenerator
{
public:
	MapGenerator();
	~MapGenerator();

	void Generate(GenerateType type);
	bool Draw(DrawType type, int size);

private:
	void Random_InterpolateGenerate(float tf, int lvl);
	void DiamodAndSquareGenerate(float tf);

private:
	Camera* m_camera;

	bool m_mapUpdated;

	float** m_fmap;
	int m_map[kSize][kSize];
};

