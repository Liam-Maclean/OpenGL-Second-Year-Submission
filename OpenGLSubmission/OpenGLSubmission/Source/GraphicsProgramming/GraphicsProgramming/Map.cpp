#include "Map.h"
//constructor (default)
Map::Map()
{
}

//constructor (initialising position)
Map::Map(int x, int y, int z)
{
	mapX = x; 
	mapY = y;
}

//deconstructor
Map::~Map()
{
}

//load the map from a file
bool Map::ParseMap(const char * path)
{
	//open file name at path handed
	FILE *file = fopen(path, "r");

	//if the file can't be loaded 
	while (file == NULL){
		//throw an error exception and return false
		MessageBox(NULL, "File failed to load", "Failure", MB_OK);
		printf("Impossible to open the file !\n");
		return false;
	}


	while (1){

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.
		else
		{
		}
	}
}

//sets the position of the tiles and map
void Map::SetPosition()
{
	for (int x = 0; x < 20; x++)
	{
		for (int z = 0; z < 20; z++)
		{
			m_tiles[x][z].SetPosition(x, z, -2);
			m_cubes[x][z].SetPosition(x, z, -1);
		}
	}
}

//sets the colors of tiles and cubes
void Map::SetColors(Vector3 tColor, Vector3 cColor)
{
	//loop for x
	for (int x = 0; x < 20; x++)
	{
		//loop for y
		for (int y = 0; y < 20; y++)
		{
			//set the colors of the objects
			m_tiles[x][y].SetColor(tColor, 1.0f);
			m_cubes[x][y].SetColor(cColor,1.0f);
		}
	}
}


//draws the map with tiles stored
void Map::MapDraw()
{
	//loop height
	for (int y = 0; y < 20; y++)
	{
		//loop width
		for (int x = 0; x < 20; x++)
		{
			//draw tiles
			glBegin(GL_QUADS);
				m_tiles[x][y].DrawPlane();
			glEnd();
		}
	}

	//draw walls
	MapWallDraw();
}

//loads table created in scene
void Map::CreateTable(int table[10][10])
{
	//loop for x
	for (int x = 0; x < 2; x++)
	{
		//loop for y
		for (int y = 0; y < 10; y++)
		{
			//store table
			m_table[x][y] = table[x][y];
		}
	}
}

//Draws walls
void Map::MapWallDraw()
{
	//loop for x
	for (int x = 0; x < 20; x++)
	{
		//loop for y
		for (int z = 0; z < 20; z++)
		{
			//if wall exists in the map (1)
			if (m_table[x][z] == 1)
			{
				//draw wall
				m_cubes[x][z].DrawCube();
			}
		}
	}
}

