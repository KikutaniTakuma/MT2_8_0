#include "World.h"
#include "Game/KeyInput/KeyInput.h"
#include "Game/Mouse/Mouse.h"
#include "Game/Vector2D/Vector2D.h"
#include "Game/Matrix3x3/Matrix3x3.h"
#include "Game/Player/Player.h"
#include "Game/Gamepad/Gamepad.h"
#include "Game/MapChip/MapChip.h"
#include "Game/Texture/Texture.h"
#include "Game/Camera/Camera.h"
#include <Novice.h>

///==========================================================================================================================================
///==========================================================================================================================================
///==========================================================================================================================================

const char* kWindowTitle = "LC1A_08_�L�N�^�j�^�N�}_�^�C�g��";

// �A�b�v�f�[�g����
void World::Update() {
	Camera::Update({player->getWorldPosX(), static_cast<float>(MapChip::kWindowHeight / 2)});

	player->Update();
}

// �`�揈��
void World::Draw() {
	MapChip::Draw(*whiteBox);

	player->Draw(*whiteBox);
}



///==========================================================================================================================================
///==========================================================================================================================================
///==========================================================================================================================================



World::World() {
	// ���C�u�����̏�����
	Novice::Initialize(kWindowTitle, MapChip::kWindowWidth, MapChip::kWindowHeight);

	Camera::Initalize();

	MapChip::Initilize();

	player = new Player;

	this->whiteBox = new Texture("./Resources/white1x1.png", 32, 32, 32);
}

World::World(int screenSizeX, int screenSizeY) {
	// ���C�u�����̏�����
	Novice::Initialize(kWindowTitle, screenSizeX, screenSizeY);

	Camera::Initalize();

	MapChip::Initilize();

	player = new Player;

	this->whiteBox = new Texture("./Resources/white1x1.png", 32, 32, 32);
}

World::~World() {
	delete player;

	Camera::Finalize();

	MapChip::Finalize();

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
	if (KeyInput::LongPush(DIK_LSHIFT) || KeyInput::LongPush(DIK_RSHIFT)) {
		if (KeyInput::Released(DIK_R)) {
			MapChip::Reset();
			player->Reset();
		}
	}
}

void World::MainLoop() {
	// �E�B���h�E�́~�{�^�����������܂Ń��[�v
	while (Novice::ProcessMessage() == 0) {
		// �t���[���̊J�n
		Novice::BeginFrame();

		this->Input();

		this->Reset();

		this->Update();

		this->Draw();

		// �t���[���̏I��
		Novice::EndFrame();

		if (KeyInput::Released(DIK_ESCAPE)) { break; }
	}
}