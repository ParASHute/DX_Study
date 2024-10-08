#pragma once

#include "Tile.h"
#include "TileSet.h"

class IndexNumBuffer : public ShaderBuffer
{
public:

    IndexNumBuffer()  
        : ShaderBuffer(&data, sizeof(Data))
    {
        data.index = 0;
    }

    void SetIndex(uint index) { data.index = index; }

    struct Data
    {
        uint index;
        Vector3 dummy;
    };

private:
    Data data;
};

class TMap
{
public:
    // width = 가로에 깔 타일의 개수
    // height = 세로에 깔 타일의 개수
    // width , height 각각 10이라면 총 100의
    // 타일이 깔린다.
    // spacing은 한 타일의 가로,세로 길이
    TMap(uint width, uint height, uint spacing);
    TMap(uint width, uint height, uint spacing, wstring path);
    ~TMap();

    void Update();
    void Render();
    void GUI();

    void GenerateTileMap();

    void MapVertexBuffer();
    void UnmapVertexBuffer();

    void Save(string path);
    void Load(string path);

    Tile* GetTile(Vector3 mPos);

    TileSet* GetTileSet() { return tileSet; }

private:
    
    vector<VertexTile> vertices;
    VertexBuffer* vb = nullptr;

    InputLayout* il = nullptr;

    vector<uint> indices;
    IndexBuffer* ib = nullptr;

    VertexShader* vs = nullptr;
    PixelShader* ps = nullptr;

    Matrix world = Values::Identity;
    WorldBuffer* wb = nullptr;

    IndexNumBuffer* inb = nullptr;

    ID3D11SamplerState* sampler[2];
    ID3D11BlendState* blend[2];

    uint width = 0;
    uint height = 0;
    uint spacing = 0;

    uint vertexCount = 0;
    uint indexCount = 0;

    D3D11_MAPPED_SUBRESOURCE subResource;

    Tile** tiles = nullptr;   
    
    TileSet* tileSet = nullptr;


};