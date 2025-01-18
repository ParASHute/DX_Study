#include "Global/Define/GlobalDefine.h"
#include "Global/Define/Maneger.h"
int main(int argc, char** args) {
	// 게임 전체
	bool	bGameOver = false;
	bool	bDungeon = true;

	int		stage;
	int		Stage;
	int		MaxStage = 1;
	int		Maxstage = 1;

	Screen Main;

	// 플레이어 관련
	cPlayer* player[4];
	player[0] = new HollyKnight();
	player[1] = new Worrier();
	player[2] = new Maige();
	player[3] = new Cleric();
	
	// 플레이어 정보 입력(세터콜)
	for (int i = 0; i < 4; i++) {
		player[i]->SetMaxState();
		player[i]->SetName();
		player[i]->SetState();
		player[i]->Skill_1();
		player[i]->Skill_2();
		player[i]->Skill_3();
		player[i]->Skill_4();
	}

	PLACE E_PLACE = PLACE::ENUM_TOWN; //플레이어 위치 정보

	// 몬스터 관련
	cMonster* monster[4];
	monster[0] = new Slime();

	PrintScreen();
	TutorialScene();
	system("pause");
	system("cls");
	PrintScreen();

	while (!bGameOver) {
		Place(E_PLACE);
		switch (E_PLACE) {
		case PLACE::ENUM_TOWN: {
			system("cls");
			PrintScreen();
			Main.EndLine();
		} break;
		case PLACE::ENUM_HOTEL: {
			system("cls");
			PrintScreen();
			for (int i = 0; i < 4; i++) player[i]->GoHotel(player[i]->GetMaxState().Hp, player[i]->GetMaxState().Mp);
			Main.EndLine();
		} break;
		case PLACE::ENUM_Tutorial: {
			system("cls");
			PrintScreen();
			TutorialScene();
		} break;
		case PLACE::ENUM_DUNGEON: {
			int count = 0;
			system("cls");
			PrintScreen();
			Main.SetStart(3, 2);
			gotoxy(Main.GetCoord().X, Main.GetCoord().Y);
			cout << "현재 위치 : 던전"; Main.EndLine();
			gotoxy(Main.GetCoord().X, Main.GetCoord().Y);
			cout << "'어디로 이동하고 싶니?'"; Main.EndLine();
			gotoxy(Main.GetCoord().X, Main.GetCoord().Y);
			cout << "스테이지 입력(숫자 숫자) : ";
			cin >> Stage;
			getchar();
			gotoxy(Main.GetCoord().X + 28, Main.GetCoord().Y);
			cout << " - ";
			cin >> stage;
			getchar();
			if (Stage <= MaxStage && stage <= Maxstage) StageManeger(Stage, stage, player, monster);
			else {
				gotoxy(Main.GetCoord().X, Main.GetCoord().Y);
				cout << "아직 오픈 되지 않은 스테이지 입니다."; Main.EndLine();
				cout << "마을로 돌아갑니다."; Main.EndLine();
				E_PLACE = PLACE::ENUM_TOWN;
			}
			system("cls");
			PrintScreen();
			Main.SetStart(3, 2);
			for (int i = 0; i < 4; i++) {
				if (player[i]->GetState().Hp == 0) {
					count++;
				}
			}
			if (count == 4) {
				int Check;
				gotoxy(Main.GetCoord().X, Main.GetCoord().Y);
				cout << "파티가 전멸하였습니다."; Main.EndLine();
				gotoxy(Main.GetCoord().X, Main.GetCoord().Y);
				cout << "게임을 계속 하시겠습니까?"; Main.EndLine();
				gotoxy(Main.GetCoord().X, Main.GetCoord().Y);
				cout << "계속하기 원하시면 1을 원하지 않는다면 0을 입력해주세요."; Main.EndLine();
				gotoxy(Main.GetCoord().X, Main.GetCoord().Y);
				cout << "Continue ?"; 
				cin >> Check;
				Main.EndLine();
				if (Check == 0) bGameOver = true;
			}
		} break;
		}
	}
	system("cls");
}