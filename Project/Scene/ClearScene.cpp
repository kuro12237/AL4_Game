#include "ClearScene.h"

void ClearScene::Initialize()
{
	sun_ = make_unique<Sun>();
	sun_->Initialize();

	skyBox_ = make_unique<SkyBox>();
	skyBox_->Initialize();

	ground_ = make_unique<Ground>();
	ground_->Initialize();

	viewProjection_.Initialize();
	viewProjection_.translation_.y = 2.0f;

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
	sun_->Update();
	skyBox_->Update();
	ground_->Update();
	viewProjection_.UpdateMatrix();
}

void ClearScene::Back2dSpriteDraw()
{
}

void ClearScene::Object3dDraw()
{
	skyBox_->Draw(viewProjection_);
	ground_->Draw(viewProjection_);
}

void ClearScene::Flont2dSpriteDraw()
{
}
