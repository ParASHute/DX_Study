#include "stdafx.h"
#include "Border.h"

void Border::Init()
{
	uint spacing = 40;
	uint width = (WinMaxWidth * 2) / spacing;
	uint height = (WinMaxHeight * 2) / spacing;

	GrassLandBorderDown = new TMap(width, height, spacing, L"TilesetNatureDown.png");
	GrassLandBorderLeft = new TMap(width, height, spacing, L"TilesetNatureLeft.png");
	GrassLandBorderRight = new TMap(width, height, spacing, L"TilesetNatureRight.png");
	GrassLandBorder = new TMap(width, height, spacing, L"TilesetNatureUP.png");

	GrassLandBorderDown->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetNatureDown.png", 24, 21);
	GrassLandBorderLeft->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetNatureLeft.png", 21, 24);
	GrassLandBorderRight->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetNatureRight.png", 21, 24);
	GrassLandBorder->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetNatureUP.png", 24, 21);

	GrassLandBorderDown->Load(TilePath + "Field1-1/GrassLandBorderDown.data");
	GrassLandBorderLeft->Load(TilePath + "Field1-1/GrassLandBorderLeft.data");
	GrassLandBorderRight->Load(TilePath + "Field1-1/GrassLandBorderRight.data");
	GrassLandBorder->Load(TilePath + "GrassLandBorder.data");
}

void Border::Destroy()
{
	SAFE_DELETE(GrassLandBorder);
	SAFE_DELETE(GrassLandBorderRight);
	SAFE_DELETE(GrassLandBorderLeft);
	SAFE_DELETE(GrassLandBorderDown);
}

void Border::Update()
{
	GrassLandBorderDown->Update();
	GrassLandBorderLeft->Update();
	GrassLandBorderRight->Update();
	GrassLandBorder->Update();
}

void Border::Render()
{
	GrassLandBorderDown->Render();
	GrassLandBorderLeft->Render();
	GrassLandBorderRight->Render();
	GrassLandBorder->Render();
}

void Border::PostRender()
{
}

void Border::GUI()
{
}
