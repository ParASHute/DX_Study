#include "Framework.h"
#include "TileSet.h"

TileSet::TileSet(wstring path)
{
    tilePath = TileTexturePath + path;

    Texture2D* tex = new Texture2D(tilePath);

    tileSRV = tex->GetSRV();
    SAFE_DELETE(tex);

    // GUI에서 표현할 이미지 버튼의 X와 Y축 개수
    // X로 10개 Y로 10개
    // 이미지를 가로로 10등분 세로로 10등분 하여
    // GUI에 표시
    tileXCount = 5;
    tileYCount = 15;

    texelTileSize = Vector2(1 / (float)tileXCount,
        1 / (float)tileYCount);
}

TileSet::TileSet()
{
    tilePath = TileTexturePath + L"TilesetField.png";

    Texture2D* tex = new Texture2D(tilePath);

    tileSRV = tex->GetSRV();
    SAFE_DELETE(tex);

    // GUI에서 표현할 이미지 버튼의 X와 Y축 개수
    // X로 10개 Y로 10개
    // 이미지를 가로로 10등분 세로로 10등분 하여
    // GUI에 표시
    tileXCount = 5;
    tileYCount = 15;

    texelTileSize = Vector2(1 / (float)tileXCount,
        1 / (float)tileYCount);
}

TileSet::~TileSet()
{
}

void TileSet::GUI()
{
    ImGui::Begin("TileSet");
    {
        int count = 0;
        for (uint y = 0; y < tileYCount; y++)
        {
            for (uint x = 0; x < tileXCount; x++)
            {
                float startX = texelTileSize.x * x;
                float startY = texelTileSize.y * y;

                ImGui::PushID(count);
                if (ImGui::ImageButton(tileSRV, ImVec2(40, 40),
                    ImVec2(startX, startY),
                    ImVec2(startX + texelTileSize.x,
                        startY + texelTileSize.y)))
                {
                    selectedStartUV = Vector2(startX, startY);
                }

                count++;

                ImGui::PopID();

                if (count % tileXCount != 0)
                    ImGui::SameLine();
            }
        }
    }
    ImGui::End();
}

void TileSet::ChangeTileMap(wstring imagePath, uint xCount, uint yCount)
{
    tilePath = imagePath;

    Texture2D* tex = new Texture2D(tilePath);
    tileSRV = tex->GetSRV();
    SAFE_DELETE(tex);

    tileXCount = xCount;
    tileYCount = yCount;

    texelTileSize = Vector2(1 / (float)tileXCount,
        1 / (float)tileYCount);
}

