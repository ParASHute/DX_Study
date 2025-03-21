#pragma once

class ImageFont : public Transform
{
public:
    enum AlignedType
    {
        LEFT, CENTER, RIGHT
    };

private:
    const UINT MAX_LENGTH = 8;

public:
    ImageFont(wstring textureFile, float interval = 1.0f);
    ~ImageFont();

    void Update();
    void Render();

    void SetValue(UINT value) { this->value = value; }
    void SetAligned(AlignedType type) { alignedType = type; }

private:
    UINT value = 0;
    string strValue;

    vector<Quad*> quads;
    vector<Texture*> textures;
    IntValueBuffer* valueBuffer;

    float interval;

    AlignedType alignedType;
    Vector2 fontSize;
};