#include "Framework.h"
#include "Item.h"

Arrow::Arrow(Vector3 position, Vector3 size, float rotation)
{
	Image = new TextureRect(position, size);
}

Arrow::~Arrow()
{
	SAFE_DELETE(Image);
}

void Arrow::SetIamge()
{
	Image->SetImage(TexturePath + L"파일 명");
}

Bomb::Bomb(Vector3 position, Vector3 size, float rotation)
{
	Image = new TextureRect(position, size);
}

Bomb::~Bomb()
{
	SAFE_DELETE(Image);
}

void Bomb::SetIamge()
{
	Image->SetImage(TexturePath + L"파일 명");
}

Heart::Heart(Vector3 position, Vector3 size, float rotation)
{
	Image = new TextureRect(position, size);
}

Heart::~Heart()
{
	SAFE_DELETE(Image);
}

void Heart::SetIamge()
{
	Image->SetImage(TexturePath + L"파일 명");
}

Rooby::Rooby(Vector3 position, Vector3 size, float rotation)
{
	Image = new TextureRect(position, size);
}

Rooby::~Rooby()
{
	SAFE_DELETE(Image);
}

void Rooby::SetIamge()
{
	Image->SetImage(TexturePath + L"파일 명");
}
