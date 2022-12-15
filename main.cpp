#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "GAME/WORLD/World.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	World project;

	project.MainLoop();

	return 0;
}