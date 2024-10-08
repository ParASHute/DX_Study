#pragma once

class TileSet
{
public:
    //friend class SingletonBase<TileSet>;
    friend class TMap;

    void GUI();

    ID3D11ShaderResourceView* GetSRV() 
    { return tileSRV; }

    void ChangeTileMap(wstring imagePath,
        uint xCount, uint yCount);

    wstring GetTilePath() { return tilePath; }

    uint GetXCount() { return tileXCount; }
    uint GetYCount() { return tileYCount; }

public: // 원래는 싱글턴이라 private
    TileSet(wstring path);
    TileSet();
    ~TileSet();

private:
    ID3D11ShaderResourceView* tileSRV = nullptr;

    uint tileXCount = 0;
    uint tileYCount = 0;

    // 플레이어가 선택한 타일의 시작 UV
    Vector2 selectedStartUV = Values::ZeroVec2;

    // 그림의 이미지 크기 사이즈
    Vector2 texelTileSize = Values::ZeroVec2;

    wstring tilePath = L"";
};