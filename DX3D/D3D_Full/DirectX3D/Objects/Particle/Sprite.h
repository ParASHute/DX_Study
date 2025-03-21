#pragma once

class Sprite : public Particle
{
private:
    class SpriteBuffer : public ConstBuffer
    {
    private:
        struct Data
        {
            Vector2 maxFrame;
            Vector2 curFrame;
        };
    public:
        SpriteBuffer() : ConstBuffer(&data, sizeof(Data))
        {
        }

        Data& Get() { return data; }

    private:
        Data data;
    };

public:
    Sprite(wstring imageFile, float width, float height, UINT frameCol, UINT frameRow, bool isAdditive = false);
    ~Sprite();

    void Update();
    void Render();
    void GUIRender();

    void Play(Vector3 position);

private:
    void Create();

private:
    float time = 0.0f;
    float speed = 1.0f;
    UINT curFrameCount = 0;
    UINT maxFrameCount = 0;
    Vector2 size;

    SpriteBuffer* buffer;
    VertexUV vertex;
};