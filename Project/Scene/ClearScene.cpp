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
	pushASprite_ = make_unique<Sprite>();
	pushASprite_->Initialize(new SpriteBoxState);
	pushASprite_->SetTexHandle(TextureManager::LoadTexture("PushA.png"));
	pushAWorldTrasform_.Initialize();

	clearTextSprite_ = make_unique<Sprite>();
	clearTextSprite_->Initialize(new SpriteBoxState);
	clearTextSprite_->SetTexHandle(TextureManager::LoadTexture("GameClearText.png"));
	clearSpriteWorldTransform_.Initialize();

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

void ClearScene::Update(GameManager* Scene)
{
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
	sun_->Update();
	skyBox_->Update();
	ground_->Update();
	pushAWorldTrasform_.UpdateMatrix();
	clearSpriteWorldTransform_.UpdateMatrix();
	worldTransform_.UpdateMatrix();
	viewProjection_.UpdateMatrix();
}

void ClearScene::Back2dSpriteDraw()
{
}

void ClearScene::Object3dDraw()
{

	gameObject_->Draw(worldTransform_, viewProjection_);
	skyBox_->Draw(viewProjection_);
	ground_->Draw(viewProjection_);
}

void ClearScene::Flont2dSpriteDraw()
{
	clearTextSprite_->Draw(clearSpriteWorldTransform_, viewProjection_);
	pushASprite_->Draw(pushAWorldTrasform_, viewProjection_);
}
