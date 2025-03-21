#pragma once

class Rain : public Particle
{
public:
    Rain();
    ~Rain();

    void Update();
    void Render();
    void GUIRender();

private:
    void Create();

private:
    WeatherBuffer* buffer;
    vector<VertexUV> vertices;
};