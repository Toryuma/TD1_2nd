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

typedef struct MapPos {
	int mapX;
	int mapY;
};


typedef struct Player {

	Vector2 pos;
	int speed;
	int radius;
	Status status;
	MapPos mapPos;
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

	Player player1{ {256,640},64,64,{true,300}, {0,0} };
	Player player2{ {320,640},64,64,{true,300} ,{0,0} };
	Player player3{ {384,640},64,64,{true,300} ,{0,0} };
	Player player4{ {448,640},64,64,{true,300},{0,0} };

	int ghTestMap = Novice::LoadTexture("./testMap.png");

	int x = 0;
	int y = 0;
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
		int paladin = Novice::LoadTexture("./player4.png");
		int devil = Novice::LoadTexture("./boss.png");

		//不変
		const int blockSize = 64;

		int block = Novice::LoadTexture("./box.png");

		int map[12][12] = {
			{6,6,6,6,6,6,6,6,6,6,6,6},
			{6,0,0,0,0,0,0,0,0,0,0,6},
			{6,0,0,0,0,5,0,0,0,0,0,6},
			{6,0,0,0,0,0,0,0,0,0,0,6},
			{6,0,0,0,0,0,0,0,0,0,0,6},
			{6,0,0,0,0,0,0,0,0,0,0,6},
			{6,0,0,0,0,0,0,0,0,0,0,6},
			{6,0,0,0,0,0,0,0,0,0,0,6},
			{6,0,0,0,0,0,0,0,0,0,0,6},
			{6,0,0,0,0,0,0,0,0,0,0,6},
			{6,0,0,0,0,0,0,0,0,0,0,6},
			{6,6,6,6,6,6,6,6,6,6,6,6}
		};

		enum MapInfo {

			NONE,//0
			KNIGHT,//1
			WIZARD,//2
			FIGHTER,//3
			PALADIN,//4
			DEVIL,//5
			BLOCK//6

		};

		int mapCountX = sizeof(map[0]) / sizeof(map[0][0]);
		int mapCountY = sizeof(map) / sizeof(map[0]);

		int orderOfAction = 0;

		enum OrdeOfAction {

			BREAKTIME,//0
			PLAYER1,//1
			PLAYER2,//2
			PLAYER3,//3
			PLAYER4,//4
			BOSS,//5

		};

		player1.mapPos.mapX = player1.pos.x / blockSize;
		player1.mapPos.mapY = player1.pos.y / blockSize;
		///
		/// ↓更新処理ここから
		///

		//座標をマップ単位に(ここを独立させる方法をお悩み中//いったん移動キーの中に移す)
		x = player1.pos.x / blockSize;
		y = player1.pos.y / blockSize;

		//機体の行動順序(orderOfAction)を作る
		switch (orderOfAction) {

		default://ゲームスタート時とエンド時

			break;






		}


		//行動選択(actionSelection,選択の種類は未定)を作る
		//行動選択は行動順序の中へ

		//プレイヤー1キー操作
		if (keys[DIK_W] && preKeys[DIK_W] == 0) {
			//仮の座標を進ませる
			int posYTmp = player1.pos.y - player1.speed;
			player1.mapPos.mapY = posYTmp / blockSize;
			if (map[player1.mapPos.mapY][player1.mapPos.mapX] == NONE) {


				player1.pos.y -= player1.speed;
			}
		}

		if (keys[DIK_S] && preKeys[DIK_S] == 0) {

			int posYTmp = player1.pos.y + player1.speed;

			player1.mapPos.mapY = posYTmp / blockSize;

			if (map[player1.mapPos.mapY][player1.mapPos.mapX] == NONE) {
				player1.pos.y += player1.speed;
			}
		}

		if (keys[DIK_A] && preKeys[DIK_A] == 0) {

			int posXTmp = player1.pos.x - player1.speed;

			player1.mapPos.mapX = posXTmp / blockSize;
			if (map[player1.mapPos.mapY][player1.mapPos.mapX] == NONE) {
				player1.pos.x -= player1.speed;
			}
		}

		if (keys[DIK_D] && preKeys[DIK_D] == 0) {

			int posXTmp = player1.pos.x + player1.speed;
			player1.mapPos.mapX = posXTmp / blockSize;
				if (map[player1.mapPos.mapY][player1.mapPos.mapX] == NONE) {
				player1.pos.x += player1.speed;
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
					Novice::DrawSprite(x * blockSize, y * blockSize, block, 0.5f, 0.5f, 0.0f, 0xFFFFFFFF);
				}



				if (player1.status.isAlive == true) {

					Novice::DrawSprite(player1.pos.x, player1.pos.y, knight, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
				}




				if (player2.status.isAlive == true) {

					Novice::DrawSprite(player2.pos.x, player2.pos.y, wizard, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
				}



				//if (player3.status.isAlive == true) {

				//	Novice::DrawSprite(x * blockSize, y * blockSize, fighter, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
				//}




				//if (player4.status.isAlive == true) {

				//	Novice::DrawSprite(x * blockSize, y * blockSize, paladin, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
				//}


				if (map[y][x] == DEVIL) {
					Novice::DrawSprite(x * blockSize, y * blockSize, devil, 0.25f, 0.25f, 0.0f, 0xFFFFFFFF);
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
