#include "Scene.h"
Screen One;		// start = 3,2		-> 제일 큰곳
Screen Two;		// start = 81, 2	-> one 옆에
Screen Three;	// start = 81,20	-> two 아래
Screen Four;	// start = 3, 20	-> one 아래

void TutorialScene() {
	Four.SetStart(3, 20);
	gotoxy(Four.GetCoord().X, Four.GetCoord().Y); 
	cout << "공격은 검사 -> 마법사 -> 정직자 -> 성기사 -> 몬스터 순으로 공격한다."; Four.EndLine();
	gotoxy(Four.GetCoord().X, Four.GetCoord().Y);
	cout << "공격에 사용 되는 다이스는 0 ~ 7의 정팔면체 주사위 3개다."; Four.EndLine();
	gotoxy(Four.GetCoord().X, Four.GetCoord().Y);
	cout << "굴러가는 다이스는 보이지 않으며 엔터를 누를시 선택된다."; Four.EndLine();
	gotoxy(Four.GetCoord().X, Four.GetCoord().Y);
	cout << "(연타는 씹힘, 어느정도 여유를 가지고 누를 것)"; Four.EndLine();
	gotoxy(Four.GetCoord().X, Four.GetCoord().Y);
	cout << "상태이상은 상태이상 주사위 2개를 다시 굴린다 (똑같은 정 팔면체 주사위)";
	gotoxy(Four.GetCoord().X, Four.GetCoord().Y);
	cout << "첫번째 주사위는 상태이상을 걸수 있는지 판단"; Four.EndLine();
	gotoxy(Four.GetCoord().X, Four.GetCoord().Y);
	cout <<	"두번째 주사위는 턴을 결정 한다.";
}
void Battle(cPlayer* player[], cMonster* monster[], int Stage, int stage) {
	random_device rand;
	uniform_int_distribution<int> nRand(0, 7);
	uniform_int_distribution<int> PlayerC(0, 3);
	uniform_int_distribution<int> SkillC(1, 4);

	int choice;
	int MonChoice;
	double pst;
	clock_t start, end;

	int dice[3];
	int ccDice[2];

	int count = 0;
	int two = 1;
	int dam = 0;
	int pDeth = 4;
	int mDeth = 4;

	// 겜 시작하기전에 화면 싹 지워 주고 
	system("cls");
	// 스크린 다시 뽑고 시작
	PrintScreen();

	// 플레이어 선턴(무조건)
	// 검사(2), 메이지(3), 클래릭(4), 성기사(1) -> 순서로 진행
	while (true) {
		system("cls");
		PrintScreen();

		// 검사 공격턴, 블리딩 상태 이상
		if (player[1]->GetState().Hp > 0) {
			One.SetStart(3, 2);
			PrintPlayerState(player[1]);
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << player[1]->GetName() << "의 공격턴"; One.EndLine();
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << "1. " << player[1]->GetSkill_1Name() << "\t"
				<< "2. " << player[1]->GetSkill_2Name(); One.EndLine();
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << "3. " << player[1]->GetSkill_3Name() << "\t"
				<< "4. " << player[1]->GetSkill_4Name(); One.EndLine();
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << "선택지 : ";
			cin >> choice;
			getchar();
			One.EndLine();
			if (choice == 1 || choice == 2) {
				while (true) {
					if (One.GetCoord().Y == 15) {
						system("cls");
						PrintScreen();
						One.SetStart(3, 2);

						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << player[2]->GetName() << "의 공격턴"; One.EndLine();
						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << "1. " << player[2]->GetSkill_1Name() << "\t"
							<< "2. " << player[2]->GetSkill_2Name(); One.EndLine();
						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << "3. " << player[2]->GetSkill_3Name() << "\t"
							<< "4. " << player[2]->GetSkill_4Name(); One.EndLine();
						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << "선택지 : " << choice; One.EndLine();
					}
					gotoxy(One.GetCoord().X, One.GetCoord().Y);
					cout << "공격할 몬스터 번호 : "; One.EndLine();
					cin >> MonChoice;
					getchar();
					One.EndLine();
					MonChoice -= 1;
					if (MonChoice < 0 || MonChoice > 3) {
						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << "존재하지 않은 몬스터 입니다."; One.EndLine();
						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << "다시 고르시오.";
					}
					else if (monster[MonChoice]->GetMonState().Hp == 0) {
						if (monster[MonChoice]->GetName() != "Blank") {
							gotoxy(One.GetCoord().X, One.GetCoord().Y);
							cout << "이미 사망한 몬스터 입니다."; One.EndLine();
							gotoxy(One.GetCoord().X, One.GetCoord().Y);
							cout << "다시 고르시오."; One.EndLine();
						}
						else {
							gotoxy(One.GetCoord().X, One.GetCoord().Y);
							cout << "존재하지 않은 몬스터 입니다."; One.EndLine();
							gotoxy(One.GetCoord().X, One.GetCoord().Y);
							cout << "다시 고르시오."; One.EndLine();
						}
					}
					else if (monster[MonChoice]->GetName() == "Blank") {
						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << "올바르지 않은 몬스터 입니다."; One.EndLine();
						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << "다시 고르시오.";
					}
					else break;
				}
			}
			switch (choice) {
			case 1: {
				dam = player[1]->GetState().ad;
				system("cls");
				PrintScreen();
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[2]->GetName() << "의 공격턴"; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "1. " << player[2]->GetSkill_1Name() << "\t"
					<< "2. " << player[2]->GetSkill_2Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "3. " << player[2]->GetSkill_3Name() << "\t"
					<< "4. " << player[2]->GetSkill_4Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "선택지 : " << choice; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "공격할 몬스터 번호 : " << MonChoice + 1; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[1]->GetSkill_1Name(); One.EndLine();
				PrintPlayerState(player[1]);
				PrintMonsterState(monster[MonChoice]);

				for (int i = 0; i < 3; i++) {
					start = clock();
					do {
						Three.SetStart(81, 20);
						for (int j = i; j < 3; j++) {
							dice[j] = nRand(rand);
						}
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "주사위가"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "굴러가는중"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "아무키나 눌러 결정"; Three.EndLine();
						end = clock();
						pst = (double)(end - start) / CLK_TCK;
					} while (!_kbhit() || (pst < 1)); //1초안에 혹은 키를 누를경우
					getchar();
					if (i != 0 && dice[i - 1] == dice[i] && dice[i] == 0) {
						dam = 0;
						i = 3;
					}
					if (i == 2 && dice[i] == 0 && dice[0] == dice[i]) {
						dam = 0;
						i = 3;
					}
					if (dice[0] == dice[1] && dice[1] == dice[2]) {
						i = 0;
						count++;
					}
				}

				for (int i = 0; i < count; i++) two *= 2;
				dam *= two;
				system("cls");
				PrintScreen();
				PrintPlayerState(player[1]);
				PrintMonsterState(monster[MonChoice]);
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << dice[0] << "\t" << dice[1] << "\t" << dice[2]; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "트리플 횟수 : " << count; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "최종 대미지 : " << dam; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);

				monster[MonChoice]->SetHp(dam);
				cout << monster[MonChoice]->GetName() << "의 남은 체력 : " << monster[MonChoice]->GetMonState().Hp; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
			} break;

			case 2: {
				player[3]->UseSkill();
				dam = player[1]->GetState().ap;
				system("cls");
				PrintScreen();
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[2]->GetName() << "의 공격턴"; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "1. " << player[2]->GetSkill_1Name() << "\t"
					<< "2. " << player[2]->GetSkill_2Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "3. " << player[2]->GetSkill_3Name() << "\t"
					<< "4. " << player[2]->GetSkill_4Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "선택지 : " << choice; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "공격할 몬스터 번호 : " << MonChoice + 1; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[1]->GetSkill_2Name(); One.EndLine();
				PrintPlayerState(player[1]);
				PrintMonsterState(monster[MonChoice]);

				// 공격 주사위 굴리기
				for (int i = 0; i < 3; i++) {
					start = clock();
					do {
						Three.SetStart(81, 20);
						for (int j = i; j < 3; j++) {
							dice[j] = nRand(rand);
						}
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "주사위가"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "굴러가는중"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "아무키나 눌러 결정"; Three.EndLine();
						end = clock();
						pst = (double)(end - start) / CLK_TCK;
					} while (!_kbhit() || (pst < 1)); //1초안에 혹은 키를 누를경우
					getchar();
					if (i != 0 && dice[i - 1] == dice[i] && dice[i] == 0) {
						dam = 0;
						i = 3;
					}
					if (i == 2 && dice[i] == 0 && dice[0] == dice[i]) {
						dam = 0;
						i = 3;
					}
					if (dice[0] == dice[1] && dice[1] == dice[2]) {
						i = 0;
						count++;
					}
				}

				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "상태이상 주사위를 굴립니다.";  One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				system("pause");

				// 상태이상 주사위 굴리기
				for (int i = 0; i < 2; i++) {
					start = clock();
					do {
						Three.SetStart(81, 20);
						for (int j = i; j < 2; j++) {
							ccDice[j] = nRand(rand);
						}
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "주사위가"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "굴러가는중"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "아무키나 눌러 결정"; Three.EndLine();
						end = clock();
						pst = (double)(end - start) / CLK_TCK;
					} while (!_kbhit() || (pst < 1)); //1초안에 혹은 키를 누를경우
					getchar();
					if (ccDice[0] % 2 == 0) monster[MonChoice]->SetBleed(ccDice[1]);
				}

				for (int i = 0; i < count; i++) two *= 2;
				dam *= two;
				system("cls");
				PrintScreen();
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << dice[0] << "\t" << dice[1] << "\t" << dice[2]; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << ccDice[0] << "\t" << ccDice[1]; One.EndLine();
				if (ccDice[0] % 2 == 0) {
					gotoxy(One.GetCoord().X, One.GetCoord().Y);
					cout << "상태이상 : 성공"; One.EndLine();
					gotoxy(One.GetCoord().X, One.GetCoord().Y);
					cout << "턴 : " << ccDice[1]; One.EndLine();
				}
				else {
					gotoxy(One.GetCoord().X, One.GetCoord().Y);
					cout << "상태이상 : 실패"; One.EndLine();
				}
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "트리플 횟수 : " << count; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "최종 대미지 : " << dam; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);

				monster[MonChoice]->SetHp(dam);
				cout << monster[MonChoice]->GetName() << "의 남은 체력 : " << monster[MonChoice]->GetMonState().Hp; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
			}break;

			case 3: {
				dam = player[1]->GetState().adDef;
				system("cls");
				PrintScreen();
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[2]->GetName() << "의 공격턴"; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "1. " << player[2]->GetSkill_1Name() << "\t"
					<< "2. " << player[2]->GetSkill_2Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "3. " << player[2]->GetSkill_3Name() << "\t"
					<< "4. " << player[2]->GetSkill_4Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "선택지 : " << choice; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[1]->GetSkill_3Name(); One.EndLine();
				PrintPlayerState(player[1]);

				for (int i = 0; i < 3; i++) {
					start = clock();
					do {
						Three.SetStart(81, 20);
						for (int j = i; j < 3; j++) {
							dice[j] = nRand(rand);
						}
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "주사위가"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "굴러가는중"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "아무키나 눌러 결정"; Three.EndLine();
						end = clock();
						pst = (double)(end - start) / CLK_TCK;
					} while (!_kbhit() || (pst < 1)); //1초안에 혹은 키를 누를경우
					getchar();
					if (i != 0 && dice[i - 1] == dice[i] && dice[i] == 0) {
						dam = 0;
						i = 3;
					}
					if (i == 2 && dice[i] == 0 && dice[0] == dice[i]) {
						dam = 0;
						i = 3;
					}
					if (dice[0] == dice[1] && dice[1] == dice[2]) {
						i = 0;
						count++;
					}
				}

				for (int i = 0; i < count; i++) two *= 2;
				dam *= two;
				system("cls");
				PrintScreen();
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << dice[0] << "\t" << dice[1] << "\t" << dice[2]; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "트리플 횟수 : " << count; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "최종 방어치 : " << dam; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);

				player[1]->SetAdDeffence(dam);

			}break;

			case 4: {
				dam = player[1]->GetState().apDef;
				system("cls");
				PrintScreen();
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[2]->GetName() << "의 공격턴"; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "1. " << player[2]->GetSkill_1Name() << "\t"
					<< "2. " << player[2]->GetSkill_2Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "3. " << player[2]->GetSkill_3Name() << "\t"
					<< "4. " << player[2]->GetSkill_4Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "선택지 : " << choice; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[1]->GetSkill_4Name(); One.EndLine();
				PrintPlayerState(player[1]);

				for (int i = 0; i < 3; i++) {
					start = clock();
					do {
						Three.SetStart(81, 20);
						for (int j = i; j < 3; j++) {
							dice[j] = nRand(rand);
						}
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "주사위가"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "굴러가는중"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "아무키나 눌러 결정"; Three.EndLine();
						end = clock();
						pst = (double)(end - start) / CLK_TCK;
					} while (!_kbhit() || (pst < 1)); //1초안에 혹은 키를 누를경우
					getchar();
					if (i != 0 && dice[i - 1] == dice[i] && dice[i] == 0) {
						dam = 0;
						i = 3;
					}
					if (i == 2 && dice[i] == 0 && dice[0] == dice[i]) {
						dam = 0;
						i = 3;
					}
					if (dice[0] == dice[1] && dice[1] == dice[2]) {
						i = 0;
						count++;
					}
				}

				for (int i = 0; i < count; i++) two *= 2;
				dam *= two;
				system("cls");
				PrintScreen();
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << dice[0] << "\t" << dice[1] << "\t" << dice[2]; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "트리플 횟수 : " << count; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "최종 방어치 : " << dam; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);

				player[1]->SetApDeffence(dam);

			}break;

			default: {
				cout << "올바른 선택지가 아닙니다." << endl << "올바른 선택지를 고르시오.";
			}break;
			}
			count = 0;
			two = 1;
		}
		else if (player[1]->GetState().Hp <= 0) pDeth--;
		count = 0;
		two = 1;

		system("pause");
		system("cls");
		PrintScreen();
		// 메이지 공격턴, 화상 상태이상
		if (player[2]->GetState().Hp > 0) {
			PrintPlayerState(player[2]);
			One.SetStart(3, 2);
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << player[2]->GetName() << "의 공격턴"; One.EndLine();
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << "1. " << player[2]->GetSkill_1Name() << "\t"
				<< "2. " << player[2]->GetSkill_2Name(); One.EndLine();
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << "3. " << player[2]->GetSkill_3Name() << "\t"
				<< "4. " << player[2]->GetSkill_4Name(); One.EndLine();
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << "선택지 : ";
			cin >> choice;
			getchar();
			One.EndLine();
			if (choice == 1 || choice == 2) {
				while (true) {
					if (One.GetCoord().Y == 15) {
						system("cls");
						PrintScreen();
						One.SetStart(3, 2);

						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << player[2]->GetName() << "의 공격턴"; One.EndLine();
						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << "1. " << player[2]->GetSkill_1Name() << "\t"
							<< "2. " << player[2]->GetSkill_2Name(); One.EndLine();
						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << "3. " << player[2]->GetSkill_3Name() << "\t"
							<< "4. " << player[2]->GetSkill_4Name(); One.EndLine();
						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << "선택지 : " << choice; One.EndLine();
					}
					gotoxy(One.GetCoord().X, One.GetCoord().Y);
					cout << "공격할 몬스터 번호 : "; One.EndLine();
					cin >> MonChoice;
					getchar();
					MonChoice -= 1;
					if (MonChoice < 0 || MonChoice > 3) {
						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << "존재하지 않은 몬스터 입니다."; One.EndLine();
						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << "다시 고르시오.";
					}
					else if (monster[MonChoice]->GetMonState().Hp == 0) {
						if (monster[MonChoice]->GetName() != "Blank") {
							gotoxy(One.GetCoord().X, One.GetCoord().Y);
							cout << "이미 사망한 몬스터 입니다."; One.EndLine();
							gotoxy(One.GetCoord().X, One.GetCoord().Y);
							cout << "다시 고르시오."; One.EndLine();
						}
						else {
							gotoxy(One.GetCoord().X, One.GetCoord().Y);
							cout << "존재하지 않은 몬스터 입니다."; One.EndLine();
							gotoxy(One.GetCoord().X, One.GetCoord().Y);
							cout << "다시 고르시오."; One.EndLine();
						}
					}
					else if (monster[MonChoice]->GetName() == "Blank") {
						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << "올바르지 않은 몬스터 입니다."; One.EndLine();
						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << "다시 고르시오.";
					}
					else break;
				}
			}
			switch (choice) {
			case 1: {
				dam = player[2]->GetState().ad;
				system("cls");
				PrintScreen();
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[2]->GetName() << "의 공격턴"; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "1. " << player[2]->GetSkill_1Name() << "\t"
					<< "2. " << player[2]->GetSkill_2Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "3. " << player[2]->GetSkill_3Name() << "\t"
					<< "4. " << player[2]->GetSkill_4Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "선택지 : " << choice; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "공격할 몬스터 번호 : " << MonChoice + 1; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[2]->GetSkill_1Name(); One.EndLine();
				PrintPlayerState(player[2]);
				PrintMonsterState(monster[MonChoice]);

				for (int i = 0; i < 3; i++) {
					start = clock();
					do {
						Three.SetStart(81, 20);
						for (int j = i; j < 3; j++) {
							dice[j] = nRand(rand);
						}
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "주사위가"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "굴러가는중"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "아무키나 눌러 결정"; Three.EndLine();
						end = clock();
						pst = (double)(end - start) / CLK_TCK;
					} while (!_kbhit() || (pst < 1)); //1초안에 혹은 키를 누를경우
					getchar();
					if (i != 0 && dice[i - 1] == dice[i] && dice[i] == 0) {
						dam = 0;
						i = 3;
					}
					if (i == 2 && dice[i] == 0 && dice[0] == dice[i]) {
						dam = 0;
						i = 3;
					}
					if (dice[0] == dice[1] && dice[1] == dice[2]) {
						i = 0;
						count++;
					}
				}

				for (int i = 0; i < count; i++) two *= 2;
				dam *= two;
				system("cls");
				PrintScreen();
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << dice[0] << "\t" << dice[1] << "\t" << dice[2]; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "트리플 횟수 : " << count; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "최종 대미지 : " << dam; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);

				monster[MonChoice]->SetHp(dam);
				cout << monster[MonChoice]->GetName() << "의 남은 체력 : " << monster[MonChoice]->GetMonState().Hp; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
			} break;

			case 2: {
				player[3]->UseSkill();
				dam = player[2]->GetState().ap;
				system("cls");
				PrintScreen();
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[2]->GetName() << "의 공격턴"; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "1. " << player[2]->GetSkill_1Name() << "\t"
					<< "2. " << player[2]->GetSkill_2Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "3. " << player[2]->GetSkill_3Name() << "\t"
					<< "4. " << player[2]->GetSkill_4Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "선택지 : " << choice; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "공격할 몬스터 번호 : " << MonChoice + 1; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[2]->GetSkill_2Name(); One.EndLine();
				PrintPlayerState(player[2]);
				PrintMonsterState(monster[MonChoice]);

				for (int i = 0; i < 3; i++) {
					start = clock();
					do {
						Three.SetStart(81, 20);
						for (int j = i; j < 3; j++) {
							dice[j] = nRand(rand);
						}
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "주사위가"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "굴러가는중"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "아무키나 눌러 결정"; Three.EndLine();
						end = clock();
						pst = (double)(end - start) / CLK_TCK;
					} while (!_kbhit() || (pst < 1)); //1초안에 혹은 키를 누를경우
					getchar();
					if (i != 0 && dice[i - 1] == dice[i] && dice[i] == 0) {
						dam = 0;
						i = 3;
					}
					if (i == 2 && dice[i] == 0 && dice[0] == dice[i]) {
						dam = 0;
						i = 3;
					}
					if (dice[0] == dice[1] && dice[1] == dice[2]) {
						i = 0;
						count++;
					}
				}

				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "상태이상 주사위를 굴립니다.";  One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				system("pause");

				// 상태이상 주사위 굴리기
				for (int i = 0; i < 2; i++) {
					start = clock();
					do {
						Three.SetStart(81, 20);
						for (int j = i; j < 2; j++) {
							ccDice[j] = nRand(rand);
						}
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "주사위가"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "굴러가는중"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "아무키나 눌러 결정"; Three.EndLine();
						end = clock();
						pst = (double)(end - start) / CLK_TCK;
					} while (!_kbhit() || (pst < 1)); //1초안에 혹은 키를 누를경우
					getchar();
					if (ccDice[0] % 2 == 0) monster[MonChoice]->SetBleed(ccDice[1]);
				}

				for (int i = 0; i < count; i++) two *= 2;
				dam *= two;
				system("cls");
				PrintScreen();
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << dice[0] << "\t" << dice[1] << "\t" << dice[2]; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << ccDice[0] << "\t" << ccDice[1]; One.EndLine();
				if (ccDice[0] % 2 == 0) {
					gotoxy(One.GetCoord().X, One.GetCoord().Y);
					cout << "상태이상 : 성공"; One.EndLine();
					gotoxy(One.GetCoord().X, One.GetCoord().Y);
					cout << "턴 : " << ccDice[1]; One.EndLine();
				}
				else {
					gotoxy(One.GetCoord().X, One.GetCoord().Y);
					cout << "상태이상 : 실패"; One.EndLine();
				}
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "트리플 횟수 : " << count; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "최종 대미지 : " << dam; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);

				monster[MonChoice]->SetHp(dam);
				cout << monster[MonChoice]->GetName() << "의 남은 체력 : " << monster[MonChoice]->GetMonState().Hp; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
			}break;

			case 3: {
				dam = player[2]->GetState().adDef;
				system("cls");
				PrintScreen();
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[2]->GetName() << "의 공격턴"; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "1. " << player[2]->GetSkill_1Name() << "\t"
					<< "2. " << player[2]->GetSkill_2Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "3. " << player[2]->GetSkill_3Name() << "\t"
					<< "4. " << player[2]->GetSkill_4Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "선택지 : " << choice; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[2]->GetSkill_3Name(); One.EndLine();
				PrintPlayerState(player[2]);

				for (int i = 0; i < 3; i++) {
					start = clock();
					do {
						Three.SetStart(81, 20);
						for (int j = i; j < 3; j++) {
							dice[j] = nRand(rand);
						}
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "주사위가"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "굴러가는중"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "아무키나 눌러 결정"; Three.EndLine();
						end = clock();
						pst = (double)(end - start) / CLK_TCK;
					} while (!_kbhit() || (pst < 1)); //1초안에 혹은 키를 누를경우
					getchar();
					if (i != 0 && dice[i - 1] == dice[i] && dice[i] == 0) {
						dam = 0;
						i = 3;
					}
					if (i == 2 && dice[i] == 0 && dice[0] == dice[i]) {
						dam = 0;
						i = 3;
					}
					if (dice[0] == dice[1] && dice[1] == dice[2]) {
						i = 0;
						count++;
					}
				}

				for (int i = 0; i < count; i++) two *= 2;
				dam *= two;
				system("cls");
				PrintScreen();
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << dice[0] << "\t" << dice[1] << "\t" << dice[2]; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "트리플 횟수 : " << count; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "최종 방어치 : " << dam; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);

				player[2]->SetAdDeffence(dam);

			}break;

			case 4: {
				dam = player[2]->GetState().apDef;
				system("cls");
				PrintScreen();
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[2]->GetName() << "의 공격턴"; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "1. " << player[2]->GetSkill_1Name() << "\t"
					<< "2. " << player[2]->GetSkill_2Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "3. " << player[2]->GetSkill_3Name() << "\t"
					<< "4. " << player[2]->GetSkill_4Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "선택지 : " << choice; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[2]->GetSkill_4Name(); One.EndLine();
				PrintPlayerState(player[2]);

				for (int i = 0; i < 3; i++) {
					start = clock();
					do {
						Three.SetStart(81, 20);
						for (int j = i; j < 3; j++) {
							dice[j] = nRand(rand);
						}
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "주사위가"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "굴러가는중"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "아무키나 눌러 결정"; Three.EndLine();
						end = clock();
						pst = (double)(end - start) / CLK_TCK;
					} while (!_kbhit() || (pst < 1)); //1초안에 혹은 키를 누를경우
					getchar();
					if (i != 0 && dice[i - 1] == dice[i] && dice[i] == 0) {
						dam = 0;
						i = 3;
					}
					if (i == 2 && dice[i] == 0 && dice[0] == dice[i]) {
						dam = 0;
						i = 3;
					}
					if (dice[0] == dice[1] && dice[1] == dice[2]) {
						i = 0;
						count++;
					}
				}

				for (int i = 0; i < count; i++) two *= 2;
				dam *= two;
				system("cls");
				PrintScreen();
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << dice[0] << "\t" << dice[1] << "\t" << dice[2]; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "트리플 횟수 : " << count; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "최종 방어치 : " << dam; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);

				player[2]->SetApDeffence(dam);

			}break;

			default: {
				cout << "올바른 선택지가 아닙니다." << endl << "올바른 선택지를 고르시오.";
			}break;
			}
			count = 0;
			two = 1;
		}
		else if (player[2]->GetState().Hp <= 0) pDeth--;
		count = 0;
		two = 1;

		system("pause");
		system("cls");
		PrintScreen();
		// 클래릭 공격턴
		if (player[3]->GetState().Hp > 0) {
			PrintPlayerState(player[1]);
			One.SetStart(3, 2);
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << player[3]->GetName() << "의 공격턴"; One.EndLine();
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << "1. " << player[3]->GetSkill_1Name() << "\t"
				<< "2. " << player[3]->GetSkill_2Name(); One.EndLine();
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << "3. " << player[3]->GetSkill_3Name() << "\t"
				<< "4. " << player[3]->GetSkill_4Name(); One.EndLine();
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << "선택지 : ";
			cin >> choice;
			One.EndLine();
			getchar();
			if (choice == 1) {
				while (true) {
					if (One.GetCoord().Y == 15) {
						system("cls");
						PrintScreen();
						One.SetStart(3, 2);

						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << player[2]->GetName() << "의 공격턴"; One.EndLine();
						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << "1. " << player[2]->GetSkill_1Name() << "\t"
							<< "2. " << player[2]->GetSkill_2Name(); One.EndLine();
						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << "3. " << player[2]->GetSkill_3Name() << "\t"
							<< "4. " << player[2]->GetSkill_4Name(); One.EndLine();
						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << "선택지 : " << choice; One.EndLine();
					}
					gotoxy(One.GetCoord().X, One.GetCoord().Y);
					cout << "공격할 몬스터 번호 : "; One.EndLine();
					cin >> MonChoice;
					getchar();
					MonChoice -= 1;
					if (MonChoice < 0 || MonChoice > 3) {
						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << "존재하지 않은 몬스터 입니다."; One.EndLine();
						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << "다시 고르시오.";
					}
					else if (monster[MonChoice]->GetMonState().Hp == 0) {
						if (monster[MonChoice]->GetName() != "Blank") {
							gotoxy(One.GetCoord().X, One.GetCoord().Y);
							cout << "이미 사망한 몬스터 입니다."; One.EndLine();
							gotoxy(One.GetCoord().X, One.GetCoord().Y);
							cout << "다시 고르시오."; One.EndLine();
						}
						else {
							gotoxy(One.GetCoord().X, One.GetCoord().Y);
							cout << "존재하지 않은 몬스터 입니다."; One.EndLine();
							gotoxy(One.GetCoord().X, One.GetCoord().Y);
							cout << "다시 고르시오."; One.EndLine();
						}
					}
					else if (monster[MonChoice]->GetName() == "Blank") {
						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << "올바르지 않은 몬스터 입니다."; One.EndLine();
						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << "다시 고르시오.";
					}
					else break;
				}
			}
			if (choice == 2) {
				One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "힐을 줄 플레이어 : ";
				cin >> MonChoice;
				MonChoice--;

			}
			switch (choice) {
			case 1: {
				dam = player[3]->GetState().ad;
				system("cls");
				PrintScreen();
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[3]->GetName() << "의 공격턴"; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "1. " << player[3]->GetSkill_1Name() << "\t"
					<< "2. " << player[3]->GetSkill_2Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "3. " << player[3]->GetSkill_3Name() << "\t"
					<< "4. " << player[3]->GetSkill_4Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "선택지 : " << choice; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "공격할 몬스터 번호 : " << MonChoice + 1; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[3]->GetSkill_1Name(); One.EndLine();
				PrintPlayerState(player[3]);
				PrintMonsterState(monster[MonChoice]);

				for (int i = 0; i < 3; i++) {
					start = clock();
					do {
						Three.SetStart(81, 20);
						for (int j = i; j < 3; j++) {
							dice[j] = nRand(rand);
						}
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "주사위가"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "굴러가는중"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "아무키나 눌러 결정"; Three.EndLine();
						end = clock();
						pst = (double)(end - start) / CLK_TCK;
					} while (!_kbhit() || (pst < 1)); //1초안에 혹은 키를 누를경우
					getchar();
					if (i != 0 && dice[i - 1] == dice[i] && dice[i] == 0) {
						dam = 0;
						i = 3;
					}
					if (i == 2 && dice[i] == 0 && dice[0] == dice[i]) {
						dam = 0;
						i = 3;
					}
					if (dice[0] == dice[1] && dice[1] == dice[2]) {
						i = 0;
						count++;
					}
				}

				for (int i = 0; i < count; i++) two *= 2;
				dam *= two;
				system("cls");
				PrintScreen();
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << dice[0] << "\t" << dice[1] << "\t" << dice[2]; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "트리플 횟수 : " << count; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "최종 대미지 : " << dam; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);

				monster[MonChoice]->SetHp(dam);
				cout << monster[MonChoice]->GetName() << "의 남은 체력 : " << monster[MonChoice]->GetMonState().Hp; One.EndLine();
				PrintPlayerState(player[3]);
				PrintMonsterState(monster[MonChoice]);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
			} break;

			case 2: {
				player[3]->UseSkill();
				dam = player[3]->GetState().ap;
				system("cls");
				PrintScreen();
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[3]->GetName() << "의 공격턴"; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "1. " << player[3]->GetSkill_1Name() << "\t"
					<< "2. " << player[3]->GetSkill_2Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "3. " << player[3]->GetSkill_3Name() << "\t"
					<< "4. " << player[3]->GetSkill_4Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "선택지 : " << choice; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "힐을 줄 플레이어 : " << MonChoice + 1; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[3]->GetSkill_2Name(); One.EndLine();
				PrintPlayerState(player[3]);
				PrintPlayerState(player[MonChoice]);

				for (int i = 0; i < 3; i++) {
					start = clock();
					do {
						Three.SetStart(81, 20);
						for (int j = i; j < 3; j++) {
							dice[j] = nRand(rand);
						}
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "주사위가"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "굴러가는중"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "아무키나 눌러 결정"; Three.EndLine();
						end = clock();
						pst = (double)(end - start) / CLK_TCK;
					} while (!_kbhit() || (pst < 1)); //1초안에 혹은 키를 누를경우
					getchar();
					if (i != 0 && dice[i - 1] == dice[i] && dice[i] == 0) {
						dam = 0;
						i = 3;
					}
					if (i == 2 && dice[i] == 0 && dice[0] == dice[i]) {
						dam = 0;
						i = 3;
					}
					if (dice[0] == dice[1] && dice[1] == dice[2]) {
						i = 0;
						count++;
					}
				}

				for (int i = 0; i < count; i++) two *= 2;
				dam *= two;
				system("cls");
				PrintScreen();
				PrintPlayerState(player[3]);
				PrintPlayerState(player[MonChoice]);
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << dice[0] << "\t" << dice[1] << "\t" << dice[2]; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "트리플 횟수 : " << count; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "최종 힐량 : " << dam; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);

				player[MonChoice]->SetHp(-dam);
				if (player[MonChoice]->GetState().Hp > player[MonChoice]->GetMaxState().Hp) player[MonChoice]->GoHotel(player[MonChoice]->GetMaxState().Hp, player[MonChoice]->GetState().Mp);
			}break;

			case 3: {
				dam = player[3]->GetState().adDef;
				system("cls");
				PrintScreen();
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[3]->GetName() << "의 공격턴"; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "1. " << player[3]->GetSkill_1Name() << "\t"
					<< "2. " << player[3]->GetSkill_2Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "3. " << player[3]->GetSkill_3Name() << "\t"
					<< "4. " << player[3]->GetSkill_4Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "선택지 : " << choice; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[3]->GetSkill_3Name(); One.EndLine();
				PrintPlayerState(player[3]);

				for (int i = 0; i < 3; i++) {
					start = clock();
					do {
						Three.SetStart(81, 20);
						for (int j = i; j < 3; j++) {
							dice[j] = nRand(rand);
						}
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "주사위가"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "굴러가는중"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "아무키나 눌러 결정"; Three.EndLine();
						end = clock();
						pst = (double)(end - start) / CLK_TCK;
					} while (!_kbhit() || (pst < 1)); //1초안에 혹은 키를 누를경우
					getchar();
					if (i != 0 && dice[i - 1] == dice[i] && dice[i] == 0) {
						dam = 0;
						i = 3;
					}
					if (i == 2 && dice[i] == 0 && dice[0] == dice[i]) {
						dam = 0;
						i = 3;
					}
					if (dice[0] == dice[1] && dice[1] == dice[2]) {
						i = 0;
						count++;
					}
				}

				for (int i = 0; i < count; i++) two *= 2;
				dam *= two;
				system("cls");
				PrintScreen();
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << dice[0] << "\t" << dice[1] << "\t" << dice[2]; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "트리플 횟수 : " << count; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "최종 방어치 : " << dam; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);

				player[3]->SetAdDeffence(dam);

			}break;

			case 4: {
				dam = player[3]->GetState().apDef;
				system("cls");
				PrintScreen();
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[3]->GetName() << "의 공격턴"; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "1. " << player[3]->GetSkill_1Name() << "\t"
					<< "2. " << player[3]->GetSkill_2Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "3. " << player[3]->GetSkill_3Name() << "\t"
					<< "4. " << player[3]->GetSkill_4Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "선택지 : " << choice; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[3]->GetSkill_4Name(); One.EndLine();
				PrintPlayerState(player[3]);

				for (int i = 0; i < 3; i++) {
					start = clock();
					do {
						Three.SetStart(81, 20);
						for (int j = i; j < 3; j++) {
							dice[j] = nRand(rand);
						}
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "주사위가"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "굴러가는중"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "아무키나 눌러 결정"; Three.EndLine();
						end = clock();
						pst = (double)(end - start) / CLK_TCK;
					} while (!_kbhit() || (pst < 1)); //1초안에 혹은 키를 누를경우
					getchar();
					if (i != 0 && dice[i - 1] == dice[i] && dice[i] == 0) {
						dam = 0;
						i = 3;
					}
					if (i == 2 && dice[i] == 0 && dice[0] == dice[i]) {
						dam = 0;
						i = 3;
					}
					if (dice[0] == dice[1] && dice[1] == dice[2]) {
						i = 0;
						count++;
					}
				}

				for (int i = 0; i < count; i++) two *= 2;
				dam *= two;
				system("cls");
				PrintScreen();
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << dice[0] << "\t" << dice[1] << "\t" << dice[2]; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "트리플 횟수 : " << count; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "최종 방어치 : " << dam; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);

				player[3]->SetApDeffence(dam);

			}break;

			default: {
				cout << "올바른 선택지가 아닙니다." << endl << "올바른 선택지를 고르시오.";
			}break;
			}
			count = 0;
			two = 1;
		}
		else if (player[3]->GetState().Hp <= 0) pDeth--;

		system("pause");
		system("cls");
		PrintScreen();
		// 탱커 공격턴
		if (player[0]->GetState().Hp > 0) {
			PrintPlayerState(player[1]);
			One.SetStart(3, 2);
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << player[0]->GetName() << "의 공격턴"; One.EndLine();
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << "1. " << player[0]->GetSkill_1Name() << "\t"
				<< "2. " << player[0]->GetSkill_2Name(); One.EndLine();
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << "3. " << player[0]->GetSkill_3Name() << "\t"
				<< "4. " << player[0]->GetSkill_4Name(); One.EndLine();
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << "선택지 : ";
			cin >> choice;
			getchar();
			One.EndLine();
			if (choice == 1 || choice == 2) {
				while (true) {
					if (One.GetCoord().Y == 15) {
						system("cls");
						PrintScreen();
						One.SetStart(3, 2);

						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << player[2]->GetName() << "의 공격턴"; One.EndLine();
						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << "1. " << player[2]->GetSkill_1Name() << "\t"
							<< "2. " << player[2]->GetSkill_2Name(); One.EndLine();
						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << "3. " << player[2]->GetSkill_3Name() << "\t"
							<< "4. " << player[2]->GetSkill_4Name(); One.EndLine();
						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << "선택지 : " << choice; One.EndLine();
					}
					gotoxy(One.GetCoord().X, One.GetCoord().Y);
					cout << "공격할 몬스터 번호 : "; One.EndLine();
					cin >> MonChoice;
					One.EndLine();
					getchar();
					MonChoice -= 1;
					if (MonChoice < 0 || MonChoice > 3) {
						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << "존재하지 않은 몬스터 입니다."; One.EndLine();
						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << "다시 고르시오.";
					}
					else if (monster[MonChoice]->GetMonState().Hp == 0) {
						if (monster[MonChoice]->GetName() != "Blank") {
							gotoxy(One.GetCoord().X, One.GetCoord().Y);
							cout << "이미 사망한 몬스터 입니다."; One.EndLine();
							gotoxy(One.GetCoord().X, One.GetCoord().Y);
							cout << "다시 고르시오."; One.EndLine();
						}
						else {
							gotoxy(One.GetCoord().X, One.GetCoord().Y);
							cout << "존재하지 않은 몬스터 입니다."; One.EndLine();
							gotoxy(One.GetCoord().X, One.GetCoord().Y);
							cout << "다시 고르시오."; One.EndLine();
						}
					}
					else if (monster[MonChoice]->GetName() == "Blank") {
						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << "올바르지 않은 몬스터 입니다."; One.EndLine();
						gotoxy(One.GetCoord().X, One.GetCoord().Y);
						cout << "다시 고르시오.";
					}
					else break;
				}
			}
			switch (choice) {
			case 1: {
				dam = player[0]->GetState().ad;
				system("cls");
				PrintScreen();
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[0]->GetName() << "의 공격턴"; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "1. " << player[0]->GetSkill_1Name() << "\t"
					<< "2. " << player[0]->GetSkill_2Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "3. " << player[0]->GetSkill_3Name() << "\t"
					<< "4. " << player[0]->GetSkill_4Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "선택지 : " << choice; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "공격할 몬스터 번호 : " << MonChoice + 1; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[0]->GetSkill_1Name(); One.EndLine();
				PrintPlayerState(player[0]);
				PrintMonsterState(monster[MonChoice]);

				for (int i = 0; i < 3; i++) {
					start = clock();
					do {
						Three.SetStart(81, 20);
						for (int j = i; j < 3; j++) {
							dice[j] = nRand(rand);
						}
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "주사위가"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "굴러가는중"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "아무키나 눌러 결정"; Three.EndLine();
						end = clock();
						pst = (double)(end - start) / CLK_TCK;
					} while (!_kbhit() || (pst < 1)); //1초안에 혹은 키를 누를경우
					getchar();
					if (i != 0 && dice[i - 1] == dice[i] && dice[i] == 0) {
						dam = 0;
						i = 3;
					}
					if (i == 2 && dice[i] == 0 && dice[0] == dice[i]) {
						dam = 0;
						i = 3;
					}
					if (dice[0] == dice[1] && dice[1] == dice[2]) {
						i = 0;
						count++;
					}
				}

				for (int i = 0; i < count; i++) two *= 2;
				dam *= two;
				system("cls");
				PrintScreen();
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << dice[0] << "\t" << dice[1] << "\t" << dice[2]; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "트리플 횟수 : " << count; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "최종 대미지 : " << dam; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				if (dam % 3 == 0) {
					gotoxy(One.GetCoord().X, One.GetCoord().Y);
					cout << monster[MonChoice]->GetName() << "를 도발하는데 성공했다."; One.EndLine();
				}
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				monster[MonChoice]->SetHp(dam);
				cout << monster[MonChoice]->GetName() << "의 남은 체력 : " << monster[MonChoice]->GetMonState().Hp; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
			} break;

			case 2: {
				player[3]->UseSkill();
				dam = player[0]->GetState().ap;
				system("cls");
				PrintScreen();
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[0]->GetName() << "의 공격턴"; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "1. " << player[0]->GetSkill_1Name() << "\t"
					<< "2. " << player[0]->GetSkill_2Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "3. " << player[0]->GetSkill_3Name() << "\t"
					<< "4. " << player[0]->GetSkill_4Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "선택지 : " << choice; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "공격할 몬스터 번호 : " << MonChoice + 1; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[0]->GetSkill_2Name(); One.EndLine();
				PrintPlayerState(player[0]);
				PrintMonsterState(monster[MonChoice]);

				for (int i = 0; i < 3; i++) {
					start = clock();
					do {
						Three.SetStart(81, 20);
						for (int j = i; j < 3; j++) {
							dice[j] = nRand(rand);
						}
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "주사위가"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "굴러가는중"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "아무키나 눌러 결정"; Three.EndLine();
						end = clock();
						pst = (double)(end - start) / CLK_TCK;
					} while (!_kbhit() || (pst < 1)); //1초안에 혹은 키를 누를경우
					getchar();
					if (i != 0 && dice[i - 1] == dice[i] && dice[i] == 0) {
						dam = 0;
						i = 3;
					}
					if (i == 2 && dice[i] == 0 && dice[0] == dice[i]) {
						dam = 0;
						i = 3;
					}
					if (dice[0] == dice[1] && dice[1] == dice[2]) {
						i = 0;
						count++;
					}
				}

				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "상태이상 주사위를 굴립니다.";  One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				system("pause");

				// 상태이상 주사위 굴리기
				for (int i = 0; i < 2; i++) {
					start = clock();
					do {
						Three.SetStart(81, 20);
						for (int j = i; j < 2; j++) {
							ccDice[j] = nRand(rand);
						}
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "주사위가"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "굴러가는중"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "아무키나 눌러 결정"; Three.EndLine();
						end = clock();
						pst = (double)(end - start) / CLK_TCK;
					} while (!_kbhit() || (pst < 1)); //1초안에 혹은 키를 누를경우
					getchar();
					if (ccDice[0] % 2 == 0) monster[MonChoice]->SetBleed(ccDice[1]);
				}

				for (int i = 0; i < count; i++) two *= 2;
				dam *= two;
				system("cls");
				PrintScreen();
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << dice[0] << "\t" << dice[1] << "\t" << dice[2]; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << ccDice[0] << "\t" << ccDice[1]; One.EndLine();
				if (ccDice[0] % 2 == 0) {
					gotoxy(One.GetCoord().X, One.GetCoord().Y);
					cout << "상태이상 : 성공"; One.EndLine();
					gotoxy(One.GetCoord().X, One.GetCoord().Y);
					cout << "턴 : " << ccDice[1]; One.EndLine();
				}
				else {
					gotoxy(One.GetCoord().X, One.GetCoord().Y);
					cout << "상태이상 : 실패"; One.EndLine();
				}
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "트리플 횟수 : " << count; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "최종 대미지 : " << dam; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);

				monster[MonChoice]->SetHp(dam);
				cout << monster[MonChoice]->GetName() << "의 남은 체력 : " << monster[MonChoice]->GetMonState().Hp; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
			}break;

			case 3: {
				dam = player[0]->GetState().adDef;
				system("cls");
				PrintScreen();
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[0]->GetName() << "의 공격턴"; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "1. " << player[0]->GetSkill_1Name() << "\t"
					<< "2. " << player[0]->GetSkill_2Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "3. " << player[0]->GetSkill_3Name() << "\t"
					<< "4. " << player[0]->GetSkill_4Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "선택지 : " << choice; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[0]->GetSkill_3Name(); One.EndLine();
				PrintPlayerState(player[0]);

				for (int i = 0; i < 3; i++) {
					start = clock();
					do {
						Three.SetStart(81, 20);
						for (int j = i; j < 3; j++) {
							dice[j] = nRand(rand);
						}
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "주사위가"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "굴러가는중"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "아무키나 눌러 결정"; Three.EndLine();
						end = clock();
						pst = (double)(end - start) / CLK_TCK;
					} while (!_kbhit() || (pst < 1)); //1초안에 혹은 키를 누를경우
					getchar();
					if (i != 0 && dice[i - 1] == dice[i] && dice[i] == 0) {
						dam = 0;
						i = 3;
					}
					if (i == 2 && dice[i] == 0 && dice[0] == dice[i]) {
						dam = 0;
						i = 3;
					}
					if (dice[0] == dice[1] && dice[1] == dice[2]) {
						i = 0;
						count++;
					}
				}

				for (int i = 0; i < count; i++) two *= 2;
				dam *= two;
				system("cls");
				PrintScreen();
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << dice[0] << "\t" << dice[1] << "\t" << dice[2]; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "트리플 횟수 : " << count; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "최종 방어치 : " << dam; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);

				player[0]->SetAdDeffence(dam);

			}break;

			case 4: {
				dam = player[0]->GetState().apDef;
				system("cls");
				PrintScreen();
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[0]->GetName() << "의 공격턴"; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "1. " << player[0]->GetSkill_1Name() << "\t"
					<< "2. " << player[0]->GetSkill_2Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "3. " << player[0]->GetSkill_3Name() << "\t"
					<< "4. " << player[0]->GetSkill_4Name(); One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "선택지 : " << choice; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << player[0]->GetSkill_4Name(); One.EndLine();
				PrintPlayerState(player[0]);

				for (int i = 0; i < 3; i++) {
					start = clock();
					do {
						Three.SetStart(81, 20);
						for (int j = i; j < 3; j++) {
							dice[j] = nRand(rand);
						}
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "주사위가"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "굴러가는중"; Three.EndLine();
						gotoxy(Three.GetCoord().X, Three.GetCoord().Y);
						cout << "아무키나 눌러 결정"; Three.EndLine();
						end = clock();
						pst = (double)(end - start) / CLK_TCK;
					} while (!_kbhit() || (pst < 1)); //1초안에 혹은 키를 누를경우
					getchar();
					if (i != 0 && dice[i - 1] == dice[i] && dice[i] == 0) {
						dam = 0;
						i = 3;
					}
					if (i == 2 && dice[i] == 0 && dice[0] == dice[i]) {
						dam = 0;
						i = 3;
					}
					if (dice[0] == dice[1] && dice[1] == dice[2]) {
						i = 0;
						count++;
					}
				}

				for (int i = 0; i < count; i++) two *= 2;
				dam *= two;
				system("cls");
				PrintScreen();
				One.SetStart(3, 2);
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << dice[0] << "\t" << dice[1] << "\t" << dice[2]; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "트리플 횟수 : " << count; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);
				cout << "최종 방어치 : " << dam; One.EndLine();
				gotoxy(One.GetCoord().X, One.GetCoord().Y);

				player[0]->SetApDeffence(dam);

			}break;

			default: {
				cout << "올바른 선택지가 아닙니다." << endl << "올바른 선택지를 고르시오.";
			}break;
			}
			count = 0;
			two = 1;
		}
		else if (player[0]->GetState().Hp <= 0) pDeth--;

		One.EndLine();
		system("pause");
		gotoxy(One.GetCoord().X, One.GetCoord().Y);
		cout << "몬스터의 공격턴이 시작됩니다.";
		system("cls");
		PrintScreen();
		// 몬스터 공격턴
		for (int i = 3; i > -1; i--) {
			int mChoice, plChoice;
			system("cls");
			PrintScreen();
			One.SetStart(3, 2);
			Four.SetStart(3, 20);
			PrintMonsterState(monster[i]);
			if (monster[i]->GetName() != "Blank") {
				if (monster[i]->GetMonState().Hp != 0) {
				if (monster[i]->GetBleed().bleeding == true) {
					monster[i]->SetBleedTurn();
					monster[i]->SetHp(monster[i]->GetMonState().Hp * (1 / 10));
					gotoxy(Four.GetCoord().X, Four.GetCoord().Y);
					cout << "출혈에 걸려 있습니다."; Four.EndLine();
					gotoxy(Four.GetCoord().X, Four.GetCoord().Y);
					cout << "대미지 : " << (monster[i]->GetMonState().Hp * (1 / 10)); Four.EndLine();
				}
				if (monster[i]->GetBurn().burn == true) {
					monster[i]->SetBurnTurn();
					monster[i]->SetHp(monster[i]->GetMonState().Hp * (1 / 10));
					gotoxy(Four.GetCoord().X, Four.GetCoord().Y);
					cout << "화상에 걸려 있습니다."; Four.EndLine();
					gotoxy(Four.GetCoord().X, Four.GetCoord().Y);
					cout << "대미지 : " << (monster[i]->GetMonState().Hp * (1 / 10)); Four.EndLine();
				}
				if (monster[i]->GetSturn().sturn != true) {
					if (monster[1]->GetMonState().Hp != 0) {

						if (monster[i]->GetTaunt().taunt == true) {
							gotoxy(Four.GetCoord().X, Four.GetCoord().Y);
							cout << "도발에 걸려 있다."; Four.EndLine();
							plChoice = 0;
							if (player[plChoice]->GetState().Hp != 0) {
								monster[i]->SetTuntTurn();
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << monster[i]->GetName() << "의 공격턴"; One.EndLine();
								dam = monster[i]->GetMonState().ad;
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << monster[i]->GetSkill_1Name(); One.EndLine();
								PrintMonsterState(monster[i]);
								PrintPlayerState(player[plChoice]);

								for (int i = 0; i < 3; i++) {
									for (int j = 0; j < 10000; j++) dice[i] = nRand(rand);
									if (i != 0 && dice[i - 1] == dice[i] && dice[i] == 0) {
										dam = 0;
										i = 3;
									}
									if (i == 2 && dice[i] == 0 && dice[0] == dice[i]) {
										dam = 0;
										i = 3;
									}
									if (dice[0] == dice[1] && dice[1] == dice[2]) {
										i = 0;
										count++;
									}
								}

								for (int i = 0; i < count; i++) two *= 2;
								system("cls");
								PrintScreen();
								One.SetStart(3, 2);
								cout << monster[i]->GetName() << "의 공격턴"; One.EndLine();
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << "1. " << monster[i]->GetSkill_1Name() << "\t"
									<< "2. " << monster[i]->GetSkill_2Name(); One.EndLine();
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << "3. " << monster[i]->GetSkill_3Name() << "\t"
									<< "4. " << monster[i]->GetSkill_4Name(); One.EndLine();
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << "선택지 : 1"; One.EndLine();

								dam *= two;
								dam /= 3;
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << "타격에 대비해 적은 피해였다." << count; One.EndLine();
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << dice[0] << "\t" << dice[1] << "\t" << dice[2]; One.EndLine();
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << "트리플 횟수 : " << count; One.EndLine();
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << "최종 대미지 : " << dam; One.EndLine();

								player[plChoice]->SetHp(dam);
							}
							else {
								One.SetStart(3, 2);
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << player[plChoice]->GetName() << "이(가) 이미 쓰러졌다."; One.EndLine();
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << monster[i]->GetName() << "은 어리둥절하다."; One.EndLine();
							}
						}

						if (monster[i]->GetTaunt().taunt != true) {
							PrintMonsterState(monster[i]);
							One.SetStart(3, 2);
							gotoxy(One.GetCoord().X, One.GetCoord().Y);
							cout << monster[i]->GetName() << "의 공격턴"; One.EndLine();
							gotoxy(One.GetCoord().X, One.GetCoord().Y);
							cout << "1. " << monster[i]->GetSkill_1Name() << "\t"
								<< "2. " << monster[i]->GetSkill_2Name(); One.EndLine();
							gotoxy(One.GetCoord().X, One.GetCoord().Y);
							cout << "3. " << monster[i]->GetSkill_3Name() << "\t"
								<< "4. " << monster[i]->GetSkill_4Name(); One.EndLine();
							gotoxy(One.GetCoord().X, One.GetCoord().Y);
							cout << "선택지 : ";
							Sleep(1500);
							cout << SkillC(rand); One.EndLine();
							while (true) {
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << "공격할 플레이어 번호 : ";
								Sleep(1500);
								plChoice = PlayerC(rand);
								if (player[plChoice]->GetState().Hp == 0) {
									plChoice = PlayerC(rand);
								}
								else {
									cout << plChoice + 1; One.EndLine();
									break;
								}
							}
							gotoxy(One.GetCoord().X, One.GetCoord().Y);
							system("pause");
							switch (choice) {
							case 1: {
								system("cls");
								PrintScreen();
								PrintMonsterState(monster[i]);
								PrintPlayerState(player[plChoice]);
								One.SetStart(3, 2);
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								dam = monster[i]->GetMonState().ad;
								cout << monster[i]->GetSkill_1Name(); One.EndLine();

								for (int i = 0; i < 3; i++) {
									for (int j = 0; j < 10000; j++) dice[i] = nRand(rand);
									if (i != 0 && dice[i - 1] == dice[i] && dice[i] == 0) {
										dam = 0;
										i = 3;
									}
									if (i == 2 && dice[i] == 0 && dice[0] == dice[i]) {
										dam = 0;
										i = 3;
									}
									if (dice[0] == dice[1] && dice[1] == dice[2]) {
										i = 0;
										count++;
									}
								}

								for (int i = 0; i < count; i++) two *= 2;
								dam *= two;

								system("cls");
								PrintScreen();
								PrintMonsterState(monster[i]);
								PrintPlayerState(player[plChoice]);
								One.SetStart(3, 2);
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << monster[i]->GetName() << "의 공격턴"; One.EndLine();
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << "1. " << monster[i]->GetSkill_1Name() << "\t"
									<< "2. " << monster[i]->GetSkill_2Name(); One.EndLine();
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << "3. " << monster[i]->GetSkill_3Name() << "\t"
									<< "4. " << monster[i]->GetSkill_4Name(); One.EndLine();
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << "선택지 : " << choice; One.EndLine();
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << "공격할 플레이어 번호 : " << plChoice + 1; One.EndLine();
								if (player[plChoice]->GetDeffence().adDef != 0) {
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									cout << dice[0] << "\t" << dice[1] << "\t" << dice[2]; One.EndLine();
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									cout << "트리플 횟수 : " << count; One.EndLine();
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									cout << "상대 방어 계수 : " << player[plChoice]->GetDeffence().adDef; One.EndLine();
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									if (dam <= player[plChoice]->GetDeffence().adDef) {
										dam = 0;
										player[plChoice]->SetAdDeffence(-dam);
									}
									if (dam > player[plChoice]->GetDeffence().adDef) {
										dam -= player[plChoice]->GetDeffence().adDef;
										player[plChoice]->SetAdDeffence(-player[plChoice]->GetDeffence().adDef);
									}
									cout << "최종 대미지 : " << dam; One.EndLine();
									player[plChoice]->SetHp(dam);
								}
								if (player[plChoice]->GetDeffence().adDef == 0) {
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									cout << dice[0] << "\t" << dice[1] << "\t" << dice[2]; One.EndLine();
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									cout << "트리플 횟수 : " << count; One.EndLine();
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									cout << "상대 방어 계수 : " << player[plChoice]->GetDeffence().adDef; One.EndLine();
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									cout << "최종 대미지 : " << dam; One.EndLine();
									player[plChoice]->SetHp(dam);
								}
							} break;

							case 2: {
								system("cls");
								PrintScreen();
								PrintMonsterState(monster[i]);
								PrintPlayerState(player[plChoice]);
								One.SetStart(3, 2);
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								dam = monster[i]->GetMonState().ap;
								cout << monster[i]->GetSkill_2Name(); One.EndLine();

								for (int i = 0; i < 3; i++) {
									for (int j = 0; j < 10000; j++) dice[i] = nRand(rand);
									if (i != 0 && dice[i - 1] == dice[i] && dice[i] == 0) {
										dam = 0;
										i = 3;
									}
									if (i == 2 && dice[i] == 0 && dice[0] == dice[i]) {
										dam = 0;
										i = 3;
									}
									if (dice[0] == dice[1] && dice[1] == dice[2]) {
										i = 0;
										count++;
									}
								}

								for (int i = 0; i < count; i++) two *= 2;
								dam *= two;
								system("cls");
								PrintScreen();
								PrintMonsterState(monster[i]);
								PrintPlayerState(player[plChoice]);
								One.SetStart(3, 2);
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << monster[i]->GetName() << "의 공격턴"; One.EndLine();
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << "1. " << monster[i]->GetSkill_1Name() << "\t"
									<< "2. " << monster[i]->GetSkill_2Name(); One.EndLine();
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << "3. " << monster[i]->GetSkill_3Name() << "\t"
									<< "4. " << monster[i]->GetSkill_4Name(); One.EndLine();
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << "선택지 : " << choice; One.EndLine();
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << "공격할 플레이어 번호 : " << plChoice + 1; One.EndLine();
								if (player[plChoice]->GetDeffence().apDef != 0) {
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									cout << dice[0] << "\t" << dice[1] << "\t" << dice[2]; One.EndLine();
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									cout << "트리플 횟수 : " << count; One.EndLine();
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									cout << "상대 방어 계수 : " << player[plChoice]->GetDeffence().apDef; One.EndLine();
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									if (dam <= player[plChoice]->GetDeffence().apDef) {
										dam = 0;
										player[plChoice]->SetApDeffence(-dam);
									}
									if (dam > player[plChoice]->GetDeffence().apDef) {
										dam -= player[plChoice]->GetDeffence().apDef;
										player[plChoice]->SetApDeffence(-player[plChoice]->GetDeffence().apDef);
									}
									cout << "최종 대미지 : " << dam; One.EndLine();
									player[plChoice]->SetHp(dam);
								}
								if (player[plChoice]->GetDeffence().apDef == 0) {
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									cout << dice[0] << "\t" << dice[1] << "\t" << dice[2]; One.EndLine();
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									cout << "트리플 횟수 : " << count; One.EndLine();
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									cout << "상대 방어 계수 : " << player[plChoice]->GetDeffence().adDef; One.EndLine();
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									cout << "최종 대미지 : " << dam; One.EndLine();
									player[plChoice]->SetHp(dam);
								}
							} break;

							case 3: {
								system("cls");
								PrintScreen();
								PrintMonsterState(monster[i]);
								PrintPlayerState(player[plChoice]);
								One.SetStart(3, 2);
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								dam = monster[i]->GetMonState().ad;
								cout << monster[i]->GetSkill_3Name(); One.EndLine();

								for (int i = 0; i < 3; i++) {
									for (int j = 0; j < 10000; j++) dice[i] = nRand(rand);
									if (i != 0 && dice[i - 1] == dice[i] && dice[i] == 0) {
										dam = 0;
										i = 3;
									}
									if (i == 2 && dice[i] == 0 && dice[0] == dice[i]) {
										dam = 0;
										i = 3;
									}
									if (dice[0] == dice[1] && dice[1] == dice[2]) {
										i = 0;
										count++;
									}
								}

								for (int i = 0; i < count; i++) two *= 2;
								dam *= two;

								system("cls");
								PrintScreen();
								PrintMonsterState(monster[i]);
								PrintPlayerState(player[plChoice]);
								One.SetStart(3, 2);
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << monster[i]->GetName() << "의 공격턴"; One.EndLine();
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << "1. " << monster[i]->GetSkill_1Name() << "\t"
									<< "2. " << monster[i]->GetSkill_2Name(); One.EndLine();
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << "3. " << monster[i]->GetSkill_3Name() << "\t"
									<< "4. " << monster[i]->GetSkill_4Name(); One.EndLine();
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << "선택지 : " << choice; One.EndLine();
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << "공격할 플레이어 번호 : " << plChoice + 1; One.EndLine();
								if (player[plChoice]->GetDeffence().adDef != 0) {
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									cout << dice[0] << "\t" << dice[1] << "\t" << dice[2]; One.EndLine();
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									cout << "트리플 횟수 : " << count; One.EndLine();
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									cout << "상대 방어 계수 : " << player[plChoice]->GetDeffence().adDef; One.EndLine();
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									if (dam <= player[plChoice]->GetDeffence().adDef) {
										dam = 0;
										player[plChoice]->SetAdDeffence(-dam);
									}
									if (dam > player[plChoice]->GetDeffence().adDef) {
										dam -= player[plChoice]->GetDeffence().adDef;
										player[plChoice]->SetAdDeffence(-player[plChoice]->GetDeffence().adDef);
									}
									cout << "최종 대미지 : " << dam; One.EndLine();
									player[plChoice]->SetHp(dam);
								}
								if (player[plChoice]->GetDeffence().adDef == 0) {
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									cout << dice[0] << "\t" << dice[1] << "\t" << dice[2]; One.EndLine();
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									cout << "트리플 횟수 : " << count; One.EndLine();
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									cout << "상대 방어 계수 : " << player[plChoice]->GetDeffence().adDef; One.EndLine();
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									cout << "최종 대미지 : " << dam; One.EndLine();
									player[plChoice]->SetHp(dam);
								}
							} break;

							case 4: {
								system("cls");
								PrintMonsterState(monster[i]);
								PrintPlayerState(player[plChoice]);
								PrintScreen();
								One.SetStart(3, 2);
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								dam = monster[i]->GetMonState().ap;
								cout << monster[i]->GetSkill_4Name(); One.EndLine();

								for (int i = 0; i < 3; i++) {
									for (int j = 0; j < 10000; j++) dice[i] = nRand(rand);
									if (i != 0 && dice[i - 1] == dice[i] && dice[i] == 0) {
										dam = 0;
										i = 3;
									}
									if (i == 2 && dice[i] == 0 && dice[0] == dice[i]) {
										dam = 0;
										i = 3;
									}
									if (dice[0] == dice[1] && dice[1] == dice[2]) {
										i = 0;
										count++;
									}
								}

								for (int i = 0; i < count; i++) two *= 2;
								dam *= two;
								system("cls");
								PrintScreen();
								PrintMonsterState(monster[i]);
								PrintPlayerState(player[plChoice]);
								One.SetStart(3, 2);
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << monster[i]->GetName() << "의 공격턴"; One.EndLine();
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << "1. " << monster[i]->GetSkill_1Name() << "\t"
									<< "2. " << monster[i]->GetSkill_2Name(); One.EndLine();
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << "3. " << monster[i]->GetSkill_3Name() << "\t"
									<< "4. " << monster[i]->GetSkill_4Name(); One.EndLine();
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << "선택지 : " << choice; One.EndLine();
								gotoxy(One.GetCoord().X, One.GetCoord().Y);
								cout << "공격할 플레이어 번호 : " << plChoice + 1; One.EndLine();
								if (player[plChoice]->GetDeffence().apDef != 0) {
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									cout << dice[0] << "\t" << dice[1] << "\t" << dice[2]; One.EndLine();
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									cout << "트리플 횟수 : " << count; One.EndLine();
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									cout << "상대 방어 계수 : " << player[plChoice]->GetDeffence().apDef; One.EndLine();
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									if (dam <= player[plChoice]->GetDeffence().apDef) {
										dam = 0;
										player[plChoice]->SetApDeffence(-dam);
									}
									if (dam > player[plChoice]->GetDeffence().apDef) {
										dam -= player[plChoice]->GetDeffence().apDef;
										player[plChoice]->SetApDeffence(-player[plChoice]->GetDeffence().apDef);
									}
									cout << "최종 대미지 : " << dam; One.EndLine();
									player[plChoice]->SetHp(dam);
								}
								if (player[plChoice]->GetDeffence().apDef == 0) {
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									cout << dice[0] << "\t" << dice[1] << "\t" << dice[2]; One.EndLine();
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									cout << "트리플 횟수 : " << count; One.EndLine();
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									cout << "상대 방어 계수 : " << player[plChoice]->GetDeffence().adDef; One.EndLine();
									gotoxy(One.GetCoord().X, One.GetCoord().Y);
									cout << "최종 대미지 : " << dam; One.EndLine();
									player[plChoice]->SetHp(dam);
								}
							} break;
							}
							count = 0;
							two = 1;
						}

					}
					
					if (monster[i]->GetName() == "Blank") mDeth--;
				}
				if (monster[i]->GetSturn().sturn == true) {
					gotoxy(Four.GetCoord().X, Four.GetCoord().Y);
					cout << "스턴에 걸려 움직일수 없다.";
					monster[i]->SetSturnTurn();
				}
			}
			gotoxy(Four.GetCoord().X, Four.GetCoord().Y);
			if(monster[i]->GetName() != "Blank")system("pause");
		}

		// 데스 체크
		if (pDeth == 0) {
			system("cls");
			PrintScreen();
			One.SetStart(3, 2);
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << "파티가 전부 기력을 잃었다."; One.EndLine();
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << "지나가는 파티원에게 발견되 마을로 돌아갔다."; One.EndLine();
			break;
		}
		else if (mDeth == 0) {
			system("cls");
			PrintScreen();
			One.SetStart(3, 2);
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << "모든 몬스터를 해치웠다."; One.EndLine();
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << "다음 던전으로 향하는 길을 찾았다."; One.EndLine();
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << "일단은 마을로 돌아가 다음 모험을 준비하자."; One.EndLine();
			int exp, Max, Min;
			for (int i = 0; i < 4; i++) {
				if (i == 0) Max = monster[i]->GetMonState().EXP;
				else {
					if (Max > monster[i]->GetMonState().EXP) Max = monster[i]->GetMonState().EXP;
					else Min = monster[i]->GetMonState().EXP;
				}
				exp = (Min + Max) / 2;
			}
			for (int i = 0; i < 4; i++) {				
				player[i]->SetExp(exp);
			}
			break;
		}
		else{
		/*
			플레이어 배열이나 몬스터 배열중 하나가 빌때 까진 계속 돌아야함,
			따라서 일단은 계속 체크하고 돌린다. 
			특히 몬스터의 경우에는 스테이지 별로 몬스터가 생성 되기 때문에
			배틀 안에서 죽을때 마다 몬스터를 딜리트 할 필요는 없음,
			따라서 일단 둘중하나가 비면, 마을로 돌아가게 하면서 
			필요 없어진 몬스터도 그전에 삭제 한다.
		*/  
			pDeth = 4;
			mDeth = 4;
		}
	}
	}
}
void StageManeger(int Stage, int stage, cPlayer* player[], cMonster* monster[]) {
	switch (Stage) {
	case 1: {
		switch (stage) {
		case 1: {
			cout << "1-1 Stage" << endl;
			monster[0] = new Slime();
			monster[1] = new Slime();
			monster[2] = new Blank();
			monster[3] = new Blank();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;

		case 2: {
			cout << "1-2 Stage" << endl;
			monster[0] = new Slime();
			monster[1] = new Gobllin();
			monster[2] = new Blank();
			monster[3] = new Blank();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;

		case 3: {
			cout << "1-3 Stage" << endl;
			monster[0] = new Slime();
			monster[1] = new Gobllin();
			monster[2] = new Kobold();
			monster[3] = new Blank();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;

		case 4: {
			cout << "1-4 Stage" << endl;
			monster[0] = new Mandrake();
			monster[1] = new Blank();
			monster[2] = new Blank();
			monster[3] = new Blank();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;

		case 5: {
			cout << "1-5 Stage" << endl;
			monster[0] = new Slime();
			monster[1] = new Gobllin();
			monster[2] = new Kobold();
			monster[3] = new LizardMan();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;

		case 6: {
			cout << "1-6 Stage" << endl;
			monster[0] = new Gobllin();
			monster[1] = new Gobllin();
			monster[2] = new Kobold();
			monster[3] = new LizardMan();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;

		case 7: {
			cout << "1-7 Stage" << endl;
			monster[0] = new Kobold();
			monster[1] = new Kobold();
			monster[2] = new LizardMan();
			monster[3] = new LizardMan();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;

		case 8: {
			cout << "1-8 Stage" << endl;
			monster[0] = new Ent();
			monster[1] = new Blank();
			monster[2] = new Blank();
			monster[3] = new Blank();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;
		}

	}break;

	case 2: {
		switch (stage) {
		case 1: {
			cout << "2-1 Stage" << endl;
			monster[0] = new Scorpion();
			monster[1] = new Scorpion();
			monster[2] = new Blank();
			monster[3] = new Blank();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;

		case 2: {
			cout << "2-2 Stage" << endl;
			monster[0] = new Scorpion();
			monster[1] = new Mummy();
			monster[2] = new Blank();
			monster[3] = new Blank();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;

		case 3: {
			cout << "2-3 Stage" << endl;
			monster[0] = new Scorpion();
			monster[1] = new Mummy();
			monster[2] = new Mimmic();
			monster[3] = new Blank();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;

		case 4: {
			cout << "2-4 Stage" << endl;
			monster[0] = new Sphinx();
			monster[1] = new Blank();
			monster[2] = new Blank();
			monster[3] = new Blank();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;

		case 5: {
			cout << "2-5 Stage" << endl;
			monster[0] = new Scorpion();
			monster[1] = new Mummy();
			monster[2] = new Mimmic();
			monster[3] = new Sandman();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;

		case 6: {
			cout << "2-6 Stage" << endl;
			monster[0] = new Mummy();
			monster[1] = new Mummy();
			monster[2] = new Mimmic();
			monster[3] = new Sandman();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;

		case 7: {
			cout << "2-7 Stage" << endl;
			monster[0] = new Mimmic();
			monster[1] = new Mimmic();
			monster[2] = new Sandman();
			monster[3] = new Sandman();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;

		case 8: {
			cout << "2-8 Stage" << endl;
			monster[0] = new Behymes();
			monster[1] = new Blank();
			monster[2] = new Blank();
			monster[3] = new Blank();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;
		}

	}break;

	case 3: {
		switch (stage) {
		case 1: {
			cout << "3-1 Stage" << endl;
			monster[0] = new Skeleton();
			monster[1] = new Skeleton();
			monster[2] = new Blank();
			monster[3] = new Blank();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;

		case 2: {
			cout << "3-2 Stage" << endl;
			monster[0] = new Skeleton();
			monster[1] = new Zombie();
			monster[2] = new Blank();
			monster[3] = new Blank();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;

		case 3: {
			cout << "3-3 Stage" << endl;
			monster[0] = new Skeleton();
			monster[1] = new Zombie();
			monster[2] = new Wraith();
			monster[3] = new Blank();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;

		case 4: {
			cout << "3-4 Stage" << endl;
			monster[0] = new Dullahan();
			monster[1] = new Blank();
			monster[2] = new Blank();
			monster[3] = new Blank();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;

		case 5: {
			cout << "3-5 Stage" << endl;
			monster[0] = new Skeleton();
			monster[1] = new Zombie();
			monster[2] = new Wraith();
			monster[3] = new Gagotle();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;

		case 6: {
			cout << "3-6 Stage" << endl;
			monster[0] = new Zombie();
			monster[1] = new Zombie();
			monster[2] = new Wraith();
			monster[3] = new Gagotle();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;

		case 7: {
			cout << "3-7 Stage" << endl;
			monster[0] = new Wraith();
			monster[1] = new Wraith();
			monster[2] = new Gagotle();
			monster[3] = new Gagotle();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;

		case 8: {
			cout << "2-1 Stage" << endl;
			monster[0] = new Lich();
			monster[1] = new Blank();
			monster[2] = new Blank();
			monster[3] = new Blank();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;
		}

	}break;

	case 4: {
		switch (stage) {
		case 1: {
			cout << "4-1 Stage" << endl;
			monster[0] = new Yeti();
			monster[1] = new Yeti();
			monster[2] = new Blank();
			monster[3] = new Blank();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;

		case 2: {
			cout << "4-2 Stage" << endl;
			monster[0] = new Yeti();
			monster[1] = new Gorlem();
			monster[2] = new Blank();
			monster[3] = new Blank();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;

		case 3: {
			cout << "4-3 Stage" << endl;
			monster[0] = new Yeti();
			monster[1] = new Gorlem();
			monster[2] = new WereWolve();
			monster[3] = new Blank();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;

		case 4: {
			cout << "4-4 Stage" << endl;
			monster[0] = new Wyvern();
			monster[1] = new Blank();
			monster[2] = new Blank();
			monster[3] = new Blank();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;

		case 5: {
			cout << "4-5 Stage" << endl;
			monster[0] = new Yeti();
			monster[1] = new Gorlem();
			monster[2] = new WereWolve();
			monster[3] = new Griffon();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;

		case 6: {
			cout << "4-6 Stage" << endl;
			monster[0] = new Gorlem();
			monster[1] = new Gorlem();
			monster[2] = new WereWolve();
			monster[3] = new Griffon();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;

		case 7: {
			cout << "4-7 Stage" << endl;
			monster[0] = new WereWolve();
			monster[1] = new WereWolve();
			monster[2] = new Griffon();
			monster[3] = new Griffon();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;

		case 8: {
			cout << "4-8 Stage" << endl;
			monster[0] = new RedDragon();
			monster[1] = new Blank();
			monster[2] = new Blank();
			monster[3] = new Blank();
			for (int i = 0; i < 4; i++)monster[i]->SetName();
			for (int i = 0; i < 4; i++)monster[i]->SetMonState();
			for (int i = 0; i < 4; i++)monster[i]->Skill_1();
			for (int i = 0; i < 4; i++)monster[i]->Skill_2();
			for (int i = 0; i < 4; i++)monster[i]->Skill_3();
			for (int i = 0; i < 4; i++)monster[i]->Skill_4();
			Battle(player, monster, Stage, stage);
			for (int i = 0; i < 4; i++) delete monster[i];
			for (int i = 0; i < 4; i++) player[i]->SetLevel();
		}break;
		}

	}break;
	default:
		break;
	}
}
void Place(PLACE& ePlace) {
	One.SetStart(3, 2);
	switch (ePlace) {
	case PLACE::ENUM_TOWN: {
		gotoxy(One.GetCoord().X, One.GetCoord().Y); One.EndLine();
		cout << "현재 위치 : 마을";
	} break;
	case PLACE::ENUM_HOTEL: {
		gotoxy(One.GetCoord().X, One.GetCoord().Y); One.EndLine();
		cout << "현재 위치 : 여관";
	} break;
	case PLACE::ENUM_Tutorial: {
		gotoxy(One.GetCoord().X, One.GetCoord().Y); One.EndLine();
		cout << "현재 위치 : 마을 개시판 앞";
	} break;
	default:
		break;
	}
	gotoxy(One.GetCoord().X, One.GetCoord().Y);
	cout << "1. 마을 \t 2. 여관"; One.EndLine();
	gotoxy(One.GetCoord().X, One.GetCoord().Y);
	cout << "3. 튜토리얼 개시판 \t 4. 던전"; One.EndLine();
	gotoxy(One.GetCoord().X, One.GetCoord().Y);
	cout << "이동할 장소를 입력하시오 : ";
	int place;
	cin >> place;
	One.EndLine();
	switch (place) {
	case 1: {
		if (ePlace != PLACE::ENUM_TOWN) {
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << "마을로 이동합니다."; One.EndLine();
			Sleep(1500);
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << "마을에 도착했습니다.";
			Sleep(1500);
			One.EndLine();
			ePlace = PLACE::ENUM_TOWN;
		}
		else {
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << "이미 마을에 있습니다"; One.EndLine();
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			system("pause");
		}
		
	} break;
	case 2: {
		if (ePlace != PLACE::ENUM_HOTEL) {
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << "여관으로 이동합니다."; One.EndLine();
			Sleep(1500);
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << "여관에 도착했습니다.";
			Sleep(1500);
			ePlace = PLACE::ENUM_HOTEL;
		}
		else {
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << "이미 여관에 있습니다"; One.EndLine();
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			system("pause");
		}
	} break;
	case 3: {
		if (ePlace != PLACE::ENUM_Tutorial) {
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << "마을의 개시판을 보기 위해 이동합니다."; One.EndLine();
			Sleep(1500);
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << "마을의 개시판 앞에 도착했습니다."; One.EndLine();
			Sleep(500);
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << "전투 방식에 대한 글이 써있다."; One.EndLine();
			Sleep(1500);
			ePlace = PLACE::ENUM_Tutorial;
		}
		else {
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << "마을의 개시판을 보고 있다"; One.EndLine();
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			cout << "전투 방식말고 쓸모 있는 글은 안보인다."; One.EndLine();
			gotoxy(One.GetCoord().X, One.GetCoord().Y);
			system("pause");
		}
	} break;
	case 4: {
		gotoxy(One.GetCoord().X, One.GetCoord().Y);
		cout << "던전으로 이동하기 위해 마을 밖으로 떠납니다."; One.EndLine();
		Sleep(1500);
		gotoxy(One.GetCoord().X, One.GetCoord().Y);
		cout << "던전 앞에 도착했다."; One.EndLine();
		gotoxy(One.GetCoord().X, One.GetCoord().Y);
		cout << "던전의 안내를 담당하는 정령이 물었다."; One.EndLine();
		Sleep(1500);
		ePlace = PLACE::ENUM_DUNGEON;
	} break;
	default: {
		One.SetStart(3, 2);
		gotoxy(One.GetCoord().X, One.GetCoord().Y);
		cout << "옳지 않은 지역입니다."; One.EndLine();
		gotoxy(One.GetCoord().X, One.GetCoord().Y);
		cout << "다른 선택지를 고르시오"; One.EndLine();
	} break;
	}
}
void gotoxy(int x, int y) {
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void PrintPlayerState(cPlayer* player){
	Two.SetStart(81, 2);
	gotoxy(Two.GetCoord().X, Two.GetCoord().Y);
	cout << "이름	: " << player->GetName(); Two.EndLine();
	gotoxy(Two.GetCoord().X, Two.GetCoord().Y);
	cout << "레벨	: " << player->GetLevel() ; Two.EndLine();
	gotoxy(Two.GetCoord().X, Two.GetCoord().Y);
	cout << "경험치	: " << player->GetEXP() << " / " << player->GetMaxState().MaxEXP; Two.EndLine();
	gotoxy(Two.GetCoord().X, Two.GetCoord().Y);
	cout << "체력	: " << player->GetState().Hp << " / " << player->GetMaxState().Hp; Two.EndLine();
	gotoxy(Two.GetCoord().X, Two.GetCoord().Y);
	cout << "마나	: " << player->GetState().Mp << " / " << player->GetMaxState().Mp; Two.EndLine();
	gotoxy(Two.GetCoord().X, Two.GetCoord().Y);
	cout << "공격력	: " << player->GetState().ad << " / " << player->GetState().ap; Two.EndLine();
	gotoxy(Two.GetCoord().X, Two.GetCoord().Y);
	cout << "방어력	: " << player->GetState().adDef 
		<< "(" << player->GetDeffence().adDef << ")" 
		<< " / " << player->GetState().apDef 
		<< "(" << player->GetDeffence().apDef << ")"; Two.EndLine();
}
void PrintMonsterState(cMonster* monster){
	Two.SetStart(81, 10);
	gotoxy(Two.GetCoord().X, Two.GetCoord().Y);
	cout << "이름	: " << monster->GetName(); Two.EndLine();
	gotoxy(Two.GetCoord().X, Two.GetCoord().Y);
	cout << "체력	: " << monster->GetMonState().Hp;  Two.EndLine();
	gotoxy(Two.GetCoord().X, Two.GetCoord().Y);
	cout << "마나	: " << monster->GetMonState().Hp; Two.EndLine();
	gotoxy(Two.GetCoord().X, Two.GetCoord().Y);
	cout << "상태이상: " << monster->GetBleed().turn << "/" << monster->GetBurn().turn << "/" << monster->GetSturn().turn << "/" << monster->GetTaunt().turn; Two.EndLine();
	gotoxy(Two.GetCoord().X, Two.GetCoord().Y);
	cout << "출혈, 화상, 스턴, 도발";
	
}