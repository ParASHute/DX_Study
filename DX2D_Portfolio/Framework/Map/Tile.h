#pragma once


class Tile
{
public:
    
    Vector3 GetPosition() { return position; }
    void SetPosition(Vector3 position)
    { this->position = position; }

    Vector2 GetStartUV() { return startUV; }
    void SetStartUV(Vector2 uv) { this->startUV = uv; }

    Vector2 GetEndUV() { return endUV; }
    void SetEndUV(Vector2 uv) { this->endUV = uv; }

    Color GetColor() { return color; }
    void SetColor(Color color) { this->color = color; }

    uint GetIndex() { return index; }
    void SetIndex(uint index) { this->index = index; }

    ID3D11ShaderResourceView* GetSRV() { return srv; }
    void SetSRV(ID3D11ShaderResourceView* srv) 
    { this->srv = srv; }

private:
    Vector3 position = Values::ZeroVec3;
    // 그림이 그려지지 않은 공간의 색
    Color color = Values::Black;

    Vector2 startUV = Values::ZeroVec2;
    Vector2 endUV = Values::ZeroVec2;

    ID3D11ShaderResourceView* srv = nullptr;

    // 정상적이지 않은 값을 집어넣어둠
    uint index = -1;
};