#pragma once
#include "../Global/Define/GlobalDefine.h"
#include "../Global/Define/Maneger.h"

enum class PLACE { ENUM_GAMEOVER = -1, ENUM_TOWN, ENUM_HOTEL, ENUM_Tutorial, ENUM_DUNGEON };

void TutorialScene();
void Battle(cPlayer* player[], cMonster* monster[], int Stage, int stage);
void Place(PLACE& ePlace);
void StageManeger(int Stage, int stage, cPlayer* player[], cMonster* monster[]);
void gotoxy(int x, int y);
void PrintPlayerState(cPlayer* player);
void PrintMonsterState(cMonster* monster);