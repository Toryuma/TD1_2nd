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
	int radius;
	Status status;
};



// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);


	const int kWindowWidth = 616;
	const int kWindowHeight = 616;


	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Player player1{ {512,552},64,{true,300} };
	Player player2{ {576,616},64,{true,300} };
	Player player3{ {640,552},64,{true,300} };
	Player player4{ {704,616},64,{true,300} };

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

		int map[11][11] = {
			{1,1,1,1,1,1,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,2,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,4,0,1},
			{1,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,1},
			{1,5,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,3,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1,1}
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
		int playerRadius = 64;

		int playerSpeed = 64;

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


		int x = playerPosX / blockSize;
		int y = playerPosY / blockSize;

		//キー操作
		if (keys[DIK_W] && preKeys[DIK_W] == 0) {
			int speedYtmp = playerPosY - playerSpeed;

			y = speedYtmp / blockSize;
			if (map[y][x] == NONE) {
				playerPosY -= playerSpeed;
			}
		}

		if (keys[DIK_S] && preKeys[DIK_S] == 0) {
			int speedYtmp = playerPosY + playerSpeed;

			y = speedYtmp / blockSize;
			if (map[y][x] == NONE) {
				playerPosY += playerSpeed;
			}
		}

		if (keys[DIK_A] && preKeys[DIK_A] == 0) {
			int speedXtmp = playerPosX - playerSpeed;

			x = speedXtmp / blockSize;
			if (map[y][x] == NONE) {
				playerPosX -= playerSpeed;
			}
		}

		if (keys[DIK_D] && preKeys[DIK_D] == 0) {
			int speedXtmp = playerPosX + playerSpeed;

			x = speedXtmp / blockSize;
			if (map[y][x] == NONE) {
				playerPosX += playerSpeed;
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



		if (player1.status.isAlive == true) {
			Novice::DrawBox(player1.pos.x, player1.pos.y,
				player1.radius, player1.radius,
				0, GREEN, kFillModeSolid);
		}

		if (player1.status.isAlive == true) {
			Novice::DrawBox(player2.pos.x, player2.pos.y,
				player2.radius, player2.radius,
				0, RED, kFillModeSolid);
		}

		if (player1.status.isAlive == true) {
			Novice::DrawBox(player3.pos.x, player3.pos.y,
				player3.radius, player3.radius,
				0, BLACK, kFillModeSolid);
		}

		if (player1.status.isAlive == true) {
			Novice::DrawBox(player4.pos.x, player4.pos.y,
				player4.radius, player4.radius,
				0, BLUE, kFillModeSolid);
		}
		for (int y = 0; y < mapCountY; y++) {

			for (int x = 0; x < mapCountX; x++) {
				if (map[y][x] == BLOCK) {
					Novice::DrawSprite(x * blockSize, y * blockSize, block, 0.5f, 0.5f, 0.0f, 0xFFFFFFFF);
				}
				if (map[y][x] == KNIGHT) {
					Novice::DrawSprite(x * blockSize, y * blockSize, knight, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
				}
				if (map[y][x] == WIZARD) {
					Novice::DrawSprite(x * blockSize, y * blockSize, wizard, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
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
