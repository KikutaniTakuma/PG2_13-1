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

const char* kWindowTitle = "LC1A_08_�L�N�^�j�^�N�}_�^�C�g��";

// �X�V����
void World::Update() {
	for (auto& i : object) {
		i->Update();
	}
}

// �`�揈��
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
	// ���C�u�����̏�����
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

	// ���C�u�����̏I��
	Novice::Finalize();
}

void World::Input() {
	// �L�[����
	KeyInput::Input();

	// �}�E�X�̓���
	Mouse::Input();

	// GamePad�̓���
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

	// �E�B���h�E�́~�{�^�����������܂Ń��[�v
	while (Novice::ProcessMessage() == 0) {
		// 1�t���[���̎��Ԍv��
		Camera::DeltaStart();

		// �t���[���̊J�n
		Novice::BeginFrame();

		// ���͏���
		this->Input();

		// window�̍ő剻
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

		// ���Z�b�g
		this->Reset();

		// �X�V����
		Update();

		// �`�揈��
		Draw();

		// �t���[���̏I��
		Novice::EndFrame();

		//�@1�t���[���̎��Ԍv���I��
		Camera::DeltaEnd();

		// �t���[�����[�g�`��
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