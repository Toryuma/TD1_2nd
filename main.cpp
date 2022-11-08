#include <Novice.h>

const char kWindowTitle[] = "学籍番号";

/************************
* 構造体宣言
************************/

//ベクトル
typedef struct Vector2 {
	int x;
	int y;
};

//ステータス
typedef struct Status {

	int isAlive;
	int hitPoint;
};


typedef struct Player {

	Vector2 pos;
	int speed;
	int radius;
	Status status;
};



// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 768);


	const int kWindowWidth = 616;
	const int kWindowHeight = 616;


	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Player player1{ {64,64},64,64,{true,300} };
	Player player2{ {128,64},64,64,{true,300} };
	Player player3{ {192,64},64,64,{true,300} };
	Player player4{ {256,64},64,64,{true,300} };

	int ghTestMap = Novice::LoadTexture("./testMap.png");
	int characterTurn = 0;
	int characterAction = 0;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		int knight = Novice::LoadTexture("./player1.png");
		int wizard = Novice::LoadTexture("./player2.png");
		int fighter = Novice::LoadTexture("./player3.png");
		int boss = Novice::LoadTexture("./boss.png");

		//不変
		const int blockSize = 64;

		int block = Novice::LoadTexture("./box.png");

		int map[12][12] = {
			{1,1,1,1,1,1,1,1,1,1,1,1},
			{1,3,0,0,0,0,0,0,0,0,0,1},
			{1,4,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,2,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,1},
			{1,5,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1,1,1}
		};

		enum MapInfo {

			NONE,//0
			BLOCK,//1
			BOSS,//2
			KNIGHT,//3
			WIZARD,//4
			FIGHTER//5
		};

		int mapCountX = sizeof(map[0]) / sizeof(map[0][0]);
		int mapCountY = sizeof(map) / sizeof(map[0]);



		int playerPosX = 64;
		int playerPosY = 64;

		int speedTmp = 64;

		int playerLeftTopX = 0;
		int playerLeftTopY = 0;

		int playerRightTopX = 0;
		int playerRightTopY = 0;

		int playerLeftBottomX = 0;
		int playerLeftBottomY = 0;

		int playerRightBottomX = 0;
		int playerRightBottomY = 0;




		///
		/// ↓更新処理ここから
		///

		//座標をマップ単位に
		int x = player1.pos.x / blockSize;
		int y = player1.pos.y / blockSize;

		//機体の行動順序(orderOfAction)を作る


		//行動選択(actionSelection,選択の種類は未定)を作る
		//行動選択は行動順序の中へ

		//プレイヤー1キー操作
		if (keys[DIK_W] && preKeys[DIK_W] == 0) {
			int speedYtmp = player1.pos.y - player1.speed;

			y = speedYtmp / blockSize;
			if (map[y][x] == NONE) {
				player1.pos.y -= player1.speed;
			}
		}

		if (keys[DIK_S] && preKeys[DIK_S] == 0) {
			int speedYtmp = player1.pos.y + player1.speed;

			y = speedYtmp / blockSize;
			if (map[y][x] == NONE) {
				player1.pos.y += player1.speed;
			}
		}

		if (keys[DIK_A] && preKeys[DIK_A] == 0) {
			int speedXtmp = player1.pos.x - player1.speed;

			x = speedXtmp / blockSize;
			if (map[y][x] == NONE) {
				player1.pos.x -= player1.speed;
			}
		}

		if (keys[DIK_D] && preKeys[DIK_D] == 0) {
			int speedXtmp = player1.pos.x + player1.speed;

			x = speedXtmp / blockSize;
			if (map[y][x] == NONE) {
				player1.pos.x += player1.speed;
			}
		}

		//プレイヤー2キー操作
		if (keys[DIK_W] && preKeys[DIK_W] == 0) {
			int speedYtmp = player2.pos.y - player2.speed;

			y = speedYtmp / blockSize;
			if (map[y][x] == NONE) {
				player2.pos.y -= player2.speed;
			}
		}

		if (keys[DIK_S] && preKeys[DIK_S] == 0) {
			int speedYtmp = player2.pos.y + player2.speed;

			y = speedYtmp / blockSize;
			if (map[y][x] == NONE) {
				player2.pos.y += player2.speed;
			}
		}

		if (keys[DIK_A] && preKeys[DIK_A] == 0) {
			int speedXtmp = player2.pos.x - player2.speed;

			x = speedXtmp / blockSize;
			if (map[y][x] == NONE) {
				player2.pos.x -= player2.speed;
			}
		}

		if (keys[DIK_D] && preKeys[DIK_D] == 0) {
			int speedXtmp = player2.pos.x + player2.speed;

			x = speedXtmp / blockSize;
			if (map[y][x] == NONE) {
				player2.pos.x += player2.speed;
			}
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		Novice::DrawSprite(0, 0, ghTestMap,
			1, 1, 0, WHITE);


		for (int y = 0; y < mapCountY; y++) {

			for (int x = 0; x < mapCountX; x++) {
				if (map[y][x] == BLOCK) {
					Novice::DrawSprite(x * blockSize, y * blockSize,block, 0.5f, 0.5f, 0.0f, 0xFFFFFFFF);
				}

				if (map[y][x] == KNIGHT) {

					if (player1.status.isAlive == true) {

						Novice::DrawSprite(player1.pos.x, player1.pos.y, knight, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
					}
				}

				if (map[y][x] == WIZARD) {

					if (player2.status.isAlive == true) {

						Novice::DrawSprite(player2.pos.x, player2.pos.y, wizard, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
					}
				}
				if (map[y][x] == FIGHTER) {
					Novice::DrawSprite(x * blockSize, y * blockSize, fighter, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
				}
				if (map[y][x] == BOSS) {
					Novice::DrawSprite(x * blockSize, y * blockSize, boss, 0.5f, 0.5f, 0.0f, 0xFFFFFFFF);
				}
			}
		}



		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
