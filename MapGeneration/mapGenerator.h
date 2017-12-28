#pragma once
//////////////////////
// Include

//////////////////////
// Const
const int kSize = 100;

//////////////////////
// Forward declaration
class Camera;

//////////////////////
// Class MapGenerator
class MapGenerator
{
public:
	MapGenerator();
	~MapGenerator();

	void RandomPlusInterpolateGenerate(float tf, int lvl);
	void DiamodAndSquareGenerate();
	bool DrawCave();
	bool DrawLandscape();

private:
	Camera* m_camera;

	float** m_fmap;
	int m_map[kSize][kSize];
};

