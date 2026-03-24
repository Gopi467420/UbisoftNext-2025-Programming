#include "EndScene.h"
#include "app.h"

void EndScene::Render()
{
	App::Print(1920 / 2  - 50, 1080 / 2, "Press R to Restart");
	App::Print(1920 / 2 - 50, (1080 / 2) - 20, "Press Q to Quit");
}

