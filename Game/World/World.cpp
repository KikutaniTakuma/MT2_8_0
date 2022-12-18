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
	if (KeyInput::getKeys(DIK_LCONTROL)) {
		if (KeyInput::getKeys(DIK_UP)) {
			drawLeftTop.y += 5.0f;
		}
		if (KeyInput::getKeys(DIK_DOWN)) {
			drawLeftTop.y -= 5.0f;
		}
		if (KeyInput::getKeys(DIK_RIGHT)) {
			drawLeftTop.x += 5.0f;
		}
		if (KeyInput::getKeys(DIK_LEFT)) {
			drawLeftTop.x -= 5.0f;
		}
	}
	else if (KeyInput::getKeys(DIK_LALT)) {
		if (KeyInput::getKeys(DIK_UP)) {
			drawRightBottm.y += 5.0f;
		}
		if (KeyInput::getKeys(DIK_DOWN)) {
			drawRightBottm.y -= 5.0f;
		}
		if (KeyInput::getKeys(DIK_RIGHT)) {
			drawRightBottm.x += 5.0f;
		}
		if (KeyInput::getKeys(DIK_LEFT)) {
			drawRightBottm.x -= 5.0f;
		}
	}
	else if (KeyInput::getKeys(DIK_LSHIFT)) {
		if (KeyInput::getKeys(DIK_UP)) {
			cameraWorldPos.y += 5.0f;
		}
		if (KeyInput::getKeys(DIK_DOWN)) {
			cameraWorldPos.y -= 5.0f;
		}
		if (KeyInput::getKeys(DIK_RIGHT)) {
			cameraWorldPos.x += 5.0f;
		}
		if (KeyInput::getKeys(DIK_LEFT)) {
			cameraWorldPos.x -= 5.0f;
		}
	}
	else {
		if (KeyInput::getKeys(DIK_UP)) {
			cameraScreenPos.y += 5.0f;
		}
		if (KeyInput::getKeys(DIK_DOWN)) {
			cameraScreenPos.y -= 5.0f;
		}
		if (KeyInput::getKeys(DIK_RIGHT)) {
			cameraScreenPos.x += 5.0f;
		}
		if (KeyInput::getKeys(DIK_LEFT)) {
			cameraScreenPos.x -= 5.0f;
		}
	}

	if (KeyInput::Pushed(DIK_PGUP)) {
		scale += 0.1f;
	}
	else if (KeyInput::Pushed(DIK_PGDN)) {
		scale -= 0.1f;
	}
	


	camera->Update(cameraWorldPos, cameraScreenPos, scale);

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

	cameraScreenPos = { 0.0f,0.0f };
	cameraWorldPos = { 640.0f, 352.0f };
	scale = 1.0f;

	drawLeftTop = {-640.0f, 352.0f};
	drawRightBottm = { 640.0f, -352.0f };
}

World::World(int screenSizeX, int screenSizeY) {
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, screenSizeX, screenSizeY);

	camera = new Camera;

	assert(camera);

	MapChip::SetCamera(camera);

	player = new Player(camera);

	this->whiteBox = new Texture("./Resources/white1x1.png", 32, 32, 32);

	cameraScreenPos = { 0.0f,0.0f };
	cameraWorldPos = { 640.0f, 352.0f };
	scale = 1.0f;
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