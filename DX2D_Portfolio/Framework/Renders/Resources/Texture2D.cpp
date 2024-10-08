#include "Framework.h"
#include "Texture2D.h"

using namespace DirectX;
vector<TextureDesc> Textures::descs;

Texture2D::Texture2D(wstring filePath)
	:filePath(filePath)
{
	Textures::Load(this);
}

void Textures::Delete()
{
	for (TextureDesc desc : descs)
		SAFE_RELEASE(desc.srv);
}

// 텍스처2D를 생성하거나 따로 만들때 해당 texture2D의 데이터를 이용해서
// 이미 해당 그림의 데이터가 있는지 확인하고 없다면 만드는 함수
void Textures::Load(Texture2D* texture)
{
	HRESULT hr;
	TexMetadata metaData;

	// 그림이 가지고있는 경로의 확장자 추출
	// 확장자에 따른 그림 데이터 추출 함수 호출
	wstring ext = Path::GetExtension(texture->filePath);
	if (ext == L"tga")
	{
		hr = GetMetadataFromTGAFile(texture->filePath.c_str(), metaData);
		CHECK(hr);
	}
	else if (ext == L"dds")
	{
		hr = GetMetadataFromDDSFile(texture->filePath.c_str(),
			DDS_FLAGS_NONE, metaData);
		CHECK(hr);
	}
	else {
		hr = GetMetadataFromWICFile(texture->filePath.c_str(), WIC_FLAGS_NONE, metaData);
		CHECK(hr);
	}

	// 해당 그림의 너비와 높이를 변수화
	UINT width = metaData.width;
	UINT height = metaData.height;

	// Texture2D가 가지고있던 파일 경로 이미지의
	// 주소, 너비, 높이를 desc에 담음
	TextureDesc desc;
	desc.filePath = texture->filePath;
	desc.width = width;
	desc.height = height;

	TextureDesc exist;
	bool bExist = false;

	// 만약 이미 가지고있는 descs에 이번에 만들려 하는 Texture2D의
	// 주소, 너비, 높이가 같은 이미지 데이터가 이미 있는지 검사
	for (TextureDesc temp : descs)
	{
		if (desc == temp)
		{
			// 주소, 너비, 높이가 같은 이미지가 있을경우
			bExist = true;
			exist = temp; // 이미 있는 데이터를 exist에 넣기
			break;
		}
	}

	// 텍스처 데이터가 이미 있다면
	if (bExist == true) {
		texture->srv = exist.srv;  // 이미 있는 데이터의 srv 넣기
		texture->metaData = metaData;
	}

	// 이전에 만든 텍스쳐 데이터가 없다면
	else {
		// 이미지 파일로 부터 텍스처 데이터를 추출하는데 사용
		ScratchImage image;

		if (ext == L"tga") {
			hr = LoadFromTGAFile(texture->filePath.c_str(), &metaData, image);
			CHECK(hr);
		}
		else if (ext == L"dds") {
			hr = LoadFromDDSFile(texture->filePath.c_str(),
				DDS_FLAGS_NONE, &metaData, image);
			CHECK(hr);
		}
		else {
			hr = LoadFromWICFile(texture->filePath.c_str(),
				WIC_FLAGS_NONE, &metaData, image);
			CHECK(hr);
		}

		ID3D11ShaderResourceView* srv = nullptr;
		hr = CreateShaderResourceView(DEVICE, image.GetImages(),
			image.GetImageCount(), metaData, &srv);
		CHECK(hr);

		desc.srv = srv;
		texture->srv = srv;
		texture->metaData = metaData;

		descs.push_back(desc);
	}
}

void Texture2D::ReadPixel(vector<Color>* pixels)
{
	ID3D11Texture2D* texture;
	srv->GetResource((ID3D11Resource**)&texture);

	ReadPixel(texture, pixels);
}

void Texture2D::ReadPixel(ID3D11Texture2D* texture, vector<Color>* pixels)
{
	// 원본 텍스쳐 정보
	D3D11_TEXTURE2D_DESC srvDesc;
	texture->GetDesc(&srvDesc);

	// 원본 텍츠쳐 복사본
	D3D11_TEXTURE2D_DESC destDesc;
	ZeroMemory(&destDesc, sizeof(D3D11_TEXTURE2D_DESC));

	// 복사본 desc 설정
	destDesc.Usage = D3D11_USAGE_STAGING;
	destDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	destDesc.Width = srvDesc.Width;
	destDesc.Height = srvDesc.Height;
	destDesc.MipLevels = 1;
	destDesc.ArraySize = 1;
	destDesc.Format = srvDesc.Format;
	destDesc.SampleDesc = srvDesc.SampleDesc;

	ID3D11Texture2D* destTex = nullptr;

	HRESULT hr = DEVICE->CreateTexture2D(&destDesc, nullptr,
		&destTex);
	CHECK(hr);
	// 원본 texture를 복사본인 destTex에 집어 넣는다.
	D3DX11LoadTextureFromTexture(DC, texture, nullptr, destTex);

	UINT* colors = new UINT[destDesc.Width * destDesc.Height];

	D3D11_MAPPED_SUBRESOURCE subRe;
	DC->Map(destTex, 0, D3D11_MAP_READ, 0, &subRe);
	{
		// 그림의 픽셀 색상을 전부 추출
		memcpy(colors, subRe.pData, sizeof(UINT) *
			destDesc.Width * destDesc.Height);
	}
	DC->Unmap(destTex, 0);

	// 이미지 가로 * 세로 즉, 픽셀 개수
	int pixelNum = destDesc.Width * destDesc.Height;

	// OpenGL과 호환되기 위해 색상 위치를 수정
	{
		UINT* alpha = new UINT[destDesc.Width * destDesc.Height];
		UINT* red = new UINT[destDesc.Width * destDesc.Height];
		UINT* green = new UINT[destDesc.Width * destDesc.Height];
		UINT* blue = new UINT[destDesc.Width * destDesc.Height];

		for (int i = 0; i < pixelNum; i++)
		{
			alpha[i] = (colors[i] & 0xFF000000);
			red[i] = (colors[i] & 0x00FF0000);
			green[i] = (colors[i] & 0x0000FF00);
			blue[i] = (colors[i] & 0x000000FF);

			// OpenGL은 ARGB가 아닌 ABGR 순서이기 때문에
			// R과 B의 위치를 바꾼다
			red[i] = colors[i] >> 16;
			blue[i] = colors[i] << 16;

			colors[i] = alpha[i] | red[i] | green[i] | blue[i];
		}
		pixels->assign(&colors[0], &colors[pixelNum - 1]);
	}

	SAFE_DELETE_ARRAY(colors);
	SAFE_DELETE(destTex);
}
