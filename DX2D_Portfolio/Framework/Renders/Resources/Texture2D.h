#pragma once

struct TextureDesc
{
	wstring filePath = L"";
	UINT width = 0;
	UINT height = 0;
	ID3D11ShaderResourceView* srv = nullptr;

	bool operator == (const TextureDesc& other)
	{
		bool b = true;

		b &= filePath == other.filePath;
		b &= width == other.width;
		b &= height == other.height;

		return b;
	}
};

class Texture2D
{
public:
	Texture2D(wstring filePath);

	void ReadPixel(vector<Color>* pixels);
	static void ReadPixel(ID3D11Texture2D* texture,
		vector<Color>* pixels);

	ID3D11ShaderResourceView* GetSRV() { return srv; }
	float GetWidth() { return (float)metaData.width; }
	float GetHeight() { return (float)metaData.height; }
	wstring GetFilePath() { return filePath; }

private:
	friend class Textures;

	wstring filePath = L"";
	ID3D11ShaderResourceView* srv = nullptr;
	DirectX::TexMetadata metaData;
};

class Textures
{
public:
	static void Delete();

private:
	friend class Texture2D;

	static void Load(Texture2D* texture);
	static vector<TextureDesc> descs;
};
