#include "World.h"
#include "Game/KeyInput/KeyInput.h"
#include "Game/Mouse/Mouse.h"
#include "Game/Object/Object.h"
#include "Game/Gamepad/Gamepad.h"

#include <Novice.h>
#include <assert.h>

#include "Game/Player/Player.h"
#include "Enemy/Enemy.hpp"

///==========================================================================================================================================
///==========================================================================================================================================
///==========================================================================================================================================

const char* kWindowTitle = "LC1A_08_キクタニタクマ_タイトル";

// 更新処理
void World::Update() {
	for (auto& i : object) {
		i->Update();
	}
}

// 描画処理
void World::Draw() {
	camera->Update();

	for (auto& i : object) {
		i->Draw();
	}
}



///==========================================================================================================================================
///==========================================================================================================================================
///==========================================================================================================================================



World::World() :
	object(0),
	winMode(WindowMode::kWindowed),
	camera(nullptr)
{
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	camera = new Camera;

	assert(camera);

	Player* player = new Player(camera);

	object.emplace_back(player);
	object.emplace_back(new Enemy(camera, player, Vector2D(400.0f, 360.0f)));
	object.emplace_back(new Enemy(camera, player, Vector2D(800.0f, 360.0f)));



	Novice::SetWindowMode(winMode);
}


World::~World() {
	delete camera;

	for (auto& i : object) {
		delete i;
	}

	// ライブラリの終了
	Novice::Finalize();
}

void World::Input() {
	// キー入力
	KeyInput::Input();

	// マウスの入力
	Mouse::Input();

	// GamePadの入力
	Gamepad::Input();
}

void World::Reset() {
	if (KeyInput::Released(DIK_R)) {
		for (auto& i : object) {
			delete i;
		}
		object.resize(0);
		Player* player = new Player(camera);

		object.emplace_back(player);
		object.emplace_back(new Enemy(camera, player, Vector2D(400.0f, 360.0f)));
		object.emplace_back(new Enemy(camera, player, Vector2D(800.0f, 360.0f)));
	}
}

void World::MainLoop() {
	Camera::TotalStart();

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// 1フレームの時間計測
		Camera::DeltaStart();

		// フレームの開始
		Novice::BeginFrame();

		// 入力処理
		this->Input();

		// windowの最大化
		if (KeyInput::Released(DIK_F11) || 
			KeyInput::LongPush(DIK_LALT) && KeyInput::Released(DIK_RETURN)) {
			if (winMode == kWindowed) {
				winMode = kFullscreen;
			}
			else if (winMode == kFullscreen) {
				winMode = kWindowed;
			}

			Novice::SetWindowMode(winMode);
		}

		// リセット
		this->Reset();

		// 更新処理
		Update();

		// 描画処理
		Draw();

		// フレームの終了
		Novice::EndFrame();

		//　1フレームの時間計測終了
		Camera::DeltaEnd();

		// フレームレート描画
		Camera::FpsDraw();

		if (KeyInput::Released(DIK_ESCAPE) ||
			Gamepad::LongPush(Gamepad::Button::LEFT_SHOULDER) && 
			Gamepad::LongPush(Gamepad::Button::RIGHT_SHOULDER) && 
			Gamepad::Released(Gamepad::Button::START)) 
		{ 
			Camera::ToatlEnd();
			break;
		}
	}
}