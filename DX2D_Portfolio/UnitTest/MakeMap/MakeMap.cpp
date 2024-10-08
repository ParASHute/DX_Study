#include "stdafx.h"
#include "MakeMap.h"

void MakeMap::Init()
{
	uint spacing = 40;
	uint width = (WinMaxWidth * 2) / spacing;
	uint height = (WinMaxHeight * 2) / spacing;

	LandBase = new TMap(width, height, spacing,L"TilesetField.png");
	LandBorderDown = new TMap(width, height, spacing,L"TilesetNatureDown.png");
	LandBorderLeft = new TMap(width, height, spacing, L"TilesetNatureLeft.png");
	LandBorderRight = new TMap(width, height, spacing, L"TilesetNatureRight.png");
	LandBorderUp = new TMap(width, height, spacing, L"TilesetNatureUP.png");
	Obstacle = new TMap(width, height, spacing, L"TilesetNatureUP.png");


	LandBase->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetField.png", 5,15);
	LandBorderDown->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetNatureDown.png", 24, 21);
	LandBorderLeft->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetNatureLeft.png", 21, 24);
	LandBorderRight->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetNatureRight.png", 21, 24);
	LandBorderUp->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetNatureUP.png", 24, 21);
	Obstacle->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetNatureDown.png", 24, 21);


	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"Bush-3.png", 1, 1);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"Bush-4.png", 1, 1);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"Grass-1.png", 1, 1);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"Stump.png", 1, 1);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"Tree-1-4.png", 1, 1);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"Tree-2-4.png", 1, 1);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"Tree-3-4.png", 1, 1);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetDesert.png", 20, 12);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetDungeon.png", 12, 4);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetField.png", 5,15);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetFloor.png", 11, 5);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetHole.png", 11, 5);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetHouse.png", 33, 23);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetInterior.png", 16, 20);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetInteriorFloor.png", 22, 17);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetNatureDown.png", 24, 21);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetNatureLeft.png", 21, 24);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetNatureRight.png", 21, 24);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetNatureUP.png", 24, 21);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetRelief.png", 20, 12);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetReliefUpSideDown.png", 20, 12);
	//Map->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetVillageAbandoned.png", 20, 12);

	LandBase->Load(TilePath + "Field1-1/GrassLandBase.data");
	LandBorderDown->Load(TilePath + "Field1-1/GrassLandBorderDown.data");
	LandBorderLeft->Load(TilePath + "Field1-1/GrassLandBorderLeft.data");
	LandBorderRight->Load(TilePath + "Field1-1/GrassLandBorderRight.data");
	LandBorderUp->Load(TilePath + "GrassLandBorder.data");
	//Obstacle->Load(TilePath + "TilesetNatureDown.data");
}

void MakeMap::Destroy()
{
	SAFE_DELETE(Obstacle);
	SAFE_DELETE(LandBorderUp);
	SAFE_DELETE(LandBorderRight);
	SAFE_DELETE(LandBorderLeft);
	SAFE_DELETE(LandBorderDown);
	SAFE_DELETE(LandBase);
}
 
void MakeMap::Update()
{	
	LandBase->Update();
	LandBorderDown->Update();
	LandBorderLeft->Update();
	LandBorderRight->Update();
	LandBorderUp->Update();
	Obstacle->Update();
}

void MakeMap::Render()
{
	LandBase->Render();
	LandBorderDown->Render();
	LandBorderLeft->Render();
	LandBorderRight->Render();
	LandBorderUp->Render();
	Obstacle->Render();
}

void MakeMap::PostRender()
{

}

void MakeMap::GUI()
{
	//LandBase->GUI();
	//LandBorderDown->GUI();
	//LandBorderLeft->GUI();
	//LandBorderRight->GUI();
	//LandBorderUp->GUI();
	Obstacle->GUI();
}
