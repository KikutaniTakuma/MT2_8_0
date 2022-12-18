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
#include <assert.h>

///==========================================================================================================================================
///==========================================================================================================================================
///==========================================================================================================================================

const char* kWindowTitle = "LC1A_08_キクタニタクマ_タイトル";

// アップデート処理
void World::Update() {
	camera->Update();

	player->Update();
}

// 描画処理
void World::Draw() {
	MapChip::Draw(*whiteBox);

	player->Draw(*whiteBox);
}



///==========================================================================================================================================
///==========================================================================================================================================
///==========================================================================================================================================



World::World() {
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, MapChip::kWindowWidth, MapChip::kWindowHeight);

	MapChip::Initilize();

	camera = new Camera;

	assert(camera);

	MapChip::SetCamera(camera);

	player = new Player(camera);

	this->whiteBox = new Texture("./Resources/white1x1.png", 32, 32, 32);
}

World::World(int screenSizeX, int screenSizeY) {
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, screenSizeX, screenSizeY);

	camera = new Camera;

	assert(camera);

	MapChip::SetCamera(camera);

	player = new Player(camera);

	this->whiteBox = new Texture("./Resources/white1x1.png", 32, 32, 32);
}

World::~World() {
	delete player;

	delete camera;

	MapChip::Finalize();

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
	if (KeyInput::LongPush(DIK_LSHIFT) || KeyInput::LongPush(DIK_RSHIFT)) {
		if (KeyInput::Released(DIK_R)) {
			MapChip::Reset();
			player->Reset();
		}
	}
}

void World::MainLoop() {
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		this->Input();

		this->Reset();

		this->Update();

		this->Draw();

		// フレームの終了
		Novice::EndFrame();

		if (KeyInput::Released(DIK_ESCAPE)) { break; }
	}
}