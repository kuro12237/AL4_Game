#include "ClearScene.h"

void ClearScene::Initialize()
{
}

void ClearScene::Update(GameManager* Scene)
{
	ImGui::Begin("Clear");
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

void ClearScene::Back2dSpriteDraw()
{
}

void ClearScene::Object3dDraw()
{
}

void ClearScene::Flont2dSpriteDraw()
{
}
