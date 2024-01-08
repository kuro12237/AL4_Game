#include"GameOverScene.h"

void GameOverScene::Initialize()
{
	sun_ = make_unique<Sun>();
	sun_->Initialize();

	skyBox_ = make_unique<SkyBox>();
	skyBox_->Initialize();

	ground_ = make_unique<Ground>();
	ground_->Initialize();

	viewProjection_.Initialize();
	viewProjection_.translation_.y = 2.0f;

	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	gameObject_->SetModel(ModelManager::LoadObjectFile("Enemy"));
	gameObject_->UseLight(true);
	worldTransform_.Initialize();
	worldTransform_.rotation.x = 1.5f;
	worldTransform_.translate.z = 10.0f;
	worldTransform_.scale = { 0.5f,0.5f,0.5f };
	worldTransform_.translate.y = 0.5f;
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
	worldTransform_.rotation.y += 0.1f;
	sun_->SetColor(ColorConverter::ColorVec4Conversion(0x5F2F2FFF));
	sun_->Update();
	skyBox_->Update();
	ground_->Update();
	worldTransform_.UpdateMatrix();
	viewProjection_.UpdateMatrix();
}

void GameOverScene::Back2dSpriteDraw()
{
}

void GameOverScene::Object3dDraw()
{
	gameObject_->Draw(worldTransform_, viewProjection_);
	skyBox_->Draw(viewProjection_);
	ground_->Draw(viewProjection_);
}
\
void GameOverScene::Flont2dSpriteDraw()
{
}
