#include "stdafx.h"
#include "Map_1-1Base.h"

void Base11::Init()
{
	uint spacing = 40;
	uint width = (WinMaxWidth * 2) / spacing;
	uint height = (WinMaxHeight * 2) / spacing;

	GrassLandBase = new TMap(width, height, spacing, L"TilesetField.png");

	GrassLandBase->GetTileSet()->ChangeTileMap(TileTexturePath + L"TilesetField.png", 5, 15);

	GrassLandBase->Load(TilePath + "Field1-1/GrassLandBase.data");
}

void Base11::Destroy()
{
	SAFE_DELETE(GrassLandBase);
}

void Base11::Update()
{
	GrassLandBase->Update();
}

void Base11::Render()
{
	GrassLandBase->Render();
}

void Base11::PostRender()
{
}

void Base11::GUI()
{
}
