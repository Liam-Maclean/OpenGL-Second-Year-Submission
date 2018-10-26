#pragma once
#include "CubeGen.h"
#include "Cube.h"
#include "plane.h"
#include <vector>
#include "Vector3.h"
using namespace std;
class Map
{

private:
	Vector3 MapPos;
	int mapX;
	int mapY;

public:
	Map();
	Map(int x, int y, int z);
	~Map();

	Plane m_tiles[20][20];
	Cube m_cubes[20][20];
	int m_table[20][20];


	void SetColors(Vector3 tColor, Vector3 cColor);

	bool ParseMap(const char * path);
	bool SaveMap();
	void CreateTable(int table[10][10]);
	void MapWallDraw();
	void SetPosition();
	void MapDraw();
};

