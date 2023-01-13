#include <Novice.h>
#include "Game/KeyInput/KeyInput.h"
#include "Game/Resources/Resources.h"
#include "Effect/Effect.h"
#include "Game/Camera/Camera.h"
#include "Game/Mouse/Mouse.h"

const char kWindowTitle[] = "LC1A_08_キクタニタクマ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Resources tex("Resources", "png");

	Camera* camera = new Camera;

	Effect effct(camera);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		key.Input();
		Mouse::Input();

		///
		/// ↓更新処理ここから
		///
		effct.Update();
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		camera->Update();
		Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0xff, kFillModeSolid);

		effct.Draw(tex["particle"]);
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (key.Released(DIK_ESCAPE)) {
			break;
		}
	}

	delete camera;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
