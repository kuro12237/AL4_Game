#include"GameOverScene.h"

void GameOverScene::Initialize()
{
}

void GameOverScene::Update(GameManager* Scene)
{
	ImGui::Begin("GameOver");
	ImGui::End();
	XINPUT_STATE joystate;
	if (Input::GetJoystickState(joystate))
	{

		if (joystate.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			Scene->ChangeState(new TitleScene);
			return;
		}
	}

}

void GameOverScene::Back2dSpriteDraw()
{
}

void GameOverScene::Object3dDraw()
{
}

void GameOverScene::Flont2dSpriteDraw()
{
}
