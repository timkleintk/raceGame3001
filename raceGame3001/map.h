#pragma once

#include <SFML/Graphics.hpp>
#include "game.h"

#define TILESZ 32
#define defaultTile 17

struct Tile
{
	int id;
	Tile(int i = defaultTile)
	{
		id = (i == -1) ? defaultTile : i;
	}
};


//class TileFactory;
//class Tile;
//class GenericObjectSpawner;
//class Manager;
//class vec2;
class Camera;

class Map
{
public:
	Map();
	void initMap();
	//void setAttributes();
	void loadMap(const char* path);

	//void spawnObjects();


	void draw(Camera* cam);

	//void drawBackground(Camera* cam);

	//void drawForeground(Camera* cam);

	Tile getTile(fvec& wPos) const;
	void setTile(fvec& wPos, int t);

	//int getObject(vec2 wPos);
	//void setObject(vec2 wPos, int o);



	//void setManager(Manager* m) { m_pManager = m; }
	
	//void budgeTile(vec2 wPos);

	int getVTiles() { return m_height; }
	int getHTiles() { return m_width; }
	//void draw(Tmpl8::Surface* screen);

private:
	Tile getTile(int tx, int ty) const;
	void setTile(int x, int y, Tile t); // nts delete if already in use
	//int getObject(int tx, int ty);
	//void setObject(int tx, int ty, int o);

	//Manager* m_pManager =0;
	//TileFactory* m_tf = 0;
	//GenericObjectSpawner* m_spawnChain = 0;
	Tile** m_tiles = 0; //pointerpointer
	//int** m_objects = 0;
	int m_width = 48;
	int m_height = 16;
};
