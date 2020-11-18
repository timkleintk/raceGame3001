#include <SFML/Graphics.hpp>
#include "game.h"
#include "camera.h"
#include "map.h"


#include <fstream>
#include <iostream>

#define numTiles 165
#define bufferSize 2048


using namespace std;
using namespace sf;

/*Tile getTile(int i)
{
	if (i < 0) { return defaultTile; }
	else { return Tile(i); }
}*/

Map::Map() {};

/*void Map::setAttributes()
{
	m_tf = new TileFactory(numTiles);

	int* values = new int[numTiles];
	Sprite solidMap(new Surface("assets/solidmap3.png"), numTiles); // nts delete??
	Sprite objectMap(new Surface("assets/objectsmap3.png"), numTiles);
	Sprite visibleMap(new Surface("assets/visiblemap3.png"), numTiles);
	Sprite budgeMap(new Surface("assets/budgemap3.png"), numTiles);


	for (int i = 0; i < numTiles; i++)
	{
		values[i] = 0;
		values[i] += ((solidMap.GetBuffer()[i] & 0xffffff) ? 0 : 1) << SOLID;
		values[i] += ((objectMap.GetBuffer()[i] & 0xffffff) ? 0 : 1) << NEEDSOBJECT;
		values[i] += ((visibleMap.GetBuffer()[i] & 0xffffff) ? 0 : 1) << DRAWABLE;
		values[i] += ((budgeMap.GetBuffer()[i] & 0xffffff) ? 0 : 1) << BUDGABLE;

	}

	m_tf->setAttributes(values);

	delete[] values;
}*/

Tile Map::getTile(int tx, int ty) const
{
	if (tx < 0 || tx >= m_width || ty < 0 || ty >= m_height) { /*printf("bruh\n");*/ return defaultTile; }
	return m_tiles[ty][tx];
}

Tile Map::getTile(fvec& wPos) const
{
	int tx = (int)floor(wPos.x / TILESZ);
	int ty = (int)floor(wPos.y / TILESZ);
	return getTile(tx, ty);
}

void Map::setTile(int tx, int ty, Tile t)
{
	if (tx < 0 || tx >= m_width || ty < 0 || ty >= m_height) { /*printf("bruh\n");*/ return; }
	m_tiles[ty][tx] = t;
}

void Map::setTile(fvec& wPos, int t)
{
	setTile((int)(wPos.x / TILESZ), (int)(wPos.y / TILESZ), t);
}

/*int Map::getObject(int tx, int ty)
{
	return m_objects[ty][tx];
}

int Map::getObject(vec2 wPos)
{
	return getObject((int)(wPos.x / TILESZ), (int)(wPos.y/TILESZ));
}

void Map::setObject(int tx, int ty, int o)
{
	m_objects[ty][tx] = o;
}

void Map::setObject(vec2 wPos, int o)
{
	setObject((int)(wPos.x / TILESZ), (int)(wPos.y / TILESZ), o);
}

void Map::budgeTile(vec2 wPos)
{
	wPos -= wPos % TILESZ;
	Tile* t = getTile(wPos);
	if (t && t->getAttribute(BUDGABLE))
	{
		// spawn block for budging
		int nt = m_spawnChain->handleObject(t->getId(), wPos, m_pManager);
		setTile(wPos, nt);

		int o = getObject(wPos);
		// spawn what was in that block
		if ( o != -1)
		{
			m_spawnChain->handleObject( o , wPos, m_pManager);
			setObject(wPos, -1);
			//if (o == sCoinID) 
			
		}
	}
}*/


void Map::initMap()
{
#ifdef _DEBUG
	printf("initMap\n");
#endif // _DEBUG
	
	
}; 


int parseInt(char* b)
{
	int result = 0;
	int sign = 1;
	if (b[0] == '-')
	{
		sign = -1;
		b++;
	}

	for (int i = 0; b[i] != 0; i++)
	{
		result *= 10;
		result += ((int)b[i] - '0');
	}

	return result * sign;
}

int strLen(const char* b)
{
	int len = 0;
	while (b[len] != 0)
	{
		len++;
	}
	return len;
}

void Map::loadMap(const char* path)
{
	//int len = strLen(path) + 1;
	//char* objPath = new char[len];
	//memcpy(objPath, path, len);
	//emcpy(&objPath[len - 8], "obj", 3);

	int rows = 0;
	int cols = 1;
	char buffer[bufferSize ];

	fstream mapFile;
	//fstream objFile;
	mapFile.open(path, ios::in);
	//objFile.open(objPath, ios::in);
	
	// determine rows
	while (mapFile.get(buffer, bufferSize))
	{
		// determine cols
		if (rows == 0) { for (int i = 0; buffer[i] != NULL; i++) { if (buffer[i] == ',') { cols++; } } }
		mapFile.get();
		rows++;
	}

	//reset the cursor
	mapFile.clear();
	mapFile.seekg(0, mapFile.beg);
	//mapFile.open(path, ios::in);

	
	// make the m_tiles member
	m_width = cols;
	m_height = rows;
	m_tiles = new Tile *[rows];
	//m_objects = new int* [rows];
	for (int i = 0; i < m_height; i++)
	{
		//m_objects[i] = new int[cols];
		m_tiles[i] = new Tile[cols];

	}

	// load the map data into m_tiles
	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width-1; x++)
		{
			mapFile.get(buffer, bufferSize, ',');
			setTile(x, y, parseInt(buffer));
			mapFile.get();
			
		}
		mapFile.get(buffer, bufferSize);
		setTile(m_width - 1, y, parseInt(buffer));
		mapFile.get();
	}

}

/*void Map::spawnObjects()
{
	
	vec2 wPos;
	Tile* t;
	int o;
	for (wPos.x = 0; wPos.x < m_width * TILESZ; wPos.x += TILESZ) 
	for (wPos.y = 0; wPos.y < m_height * TILESZ; wPos.y += TILESZ)
	{
		o = getObject(wPos);
		if (o == -1) { continue; }
		t = getTile(wPos);
		if (t && (!t->getAttribute(SOLID) && !t->getAttribute(BUDGABLE)))
		{
			m_spawnChain->handleObject(o, wPos, m_pManager);
		} 
	}
}*/

void Map::draw(Camera* cam)
{
	fvec tPos;
	fvec cPos = cam->getPos();

	for (tPos.x = cPos.x; tPos.x <= cPos.x + cam->getSize().x + TILESZ; tPos.x += TILESZ)
	{
		for (tPos.y = cPos.y; tPos.y <= cPos.y + cam->getSize().y + TILESZ; tPos.y += TILESZ)
		{
			Tile t = getTile(tPos);
			
			//cam->drawFrame(pT->getFrame(0), tPos - offset);
			
		}

	}

	/*vec2 tPos;
	vec2 cPos = cam->getPos();
	vec2 offset = cPos % TILESZ;
	for (tPos.x = cPos.x; tPos.x <= cPos.x + cam->getWidth() + TILESZ; tPos.x += TILESZ)
	{
		for (tPos.y = cPos.y; tPos.y <= cPos.y + cam->getHeight() + TILESZ; tPos.y += TILESZ)
		{
			Tile* pT = getTile(tPos);
			if (pT && pT->getAttribute(DRAWABLE))
			{
				cam->drawFrame(pT->getFrame(0), tPos - offset);
			}
		}

	}*/
}

/*void Map::drawBackground(Camera* cam)
{
	vec2 tPos;
	vec2 cPos = cam->getPos();
	vec2 offset = cPos % TILESZ;
	for (tPos.x = cPos.x; tPos.x <= cPos.x + cam->getWidth() + TILESZ; tPos.x += TILESZ)
	{
		for (tPos.y = cPos.y; tPos.y <= cPos.y + cam->getHeight() + TILESZ; tPos.y += TILESZ)
		{
			Tile* pT = getTile(tPos);
			if (pT && pT->getAttribute(DRAWABLE) && !pT->getAttribute(SOLID))
			{
				cam->drawFrame(pT->getFrame(0), tPos - offset);
			}
		}

	}
}

void Map::drawForeground(Camera* cam)
{
	vec2 tPos;
	vec2 cPos = cam->getPos();
	vec2 offset = cPos % TILESZ;
	for (tPos.x = cPos.x; tPos.x <= cPos.x + cam->getWidth() + TILESZ; tPos.x += TILESZ)
	{
		for (tPos.y = cPos.y; tPos.y <= cPos.y + cam->getHeight() + TILESZ; tPos.y += TILESZ)
		{
			Tile* pT = getTile(tPos);
			if (pT && pT->getAttribute(SOLID) && pT->getAttribute(DRAWABLE))
			{
				cam->drawFrame(pT->getFrame(0), tPos - offset);
			}
		}

	}*/
