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

		///
		/// ↓更新処理ここから
		///
		

		if (player1.status.isAlive == true) {

			//当たり判定/現在無し


			//体力が0なら生きてるフラグをオフ
			if (player1.status.hitPoint == 0) {
				player1.status.isAlive = false;


			}
		}
		//キャラクターの行動
		/*switch (characterAction) {
		case 0:

		case 1:

		case2:

		case3:


		}*/



		//キャラクター別のターン
		//switch (characterTurn) {

		//default:
		//	//バトルスタート
		//	//

		//case 0:

		//case 1:

		//case 2:

		//case 3:

		//case 4:


		//	
		//}


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
