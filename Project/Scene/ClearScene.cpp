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

	uint32_t modelHandle = ModelManager::LoadObjectFile("Enemy");
	
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	gameObject_->SetModel(modelHandle);
	gameObject_->UseLight(true);
	worldTransform_.Initialize();
	worldTransform_.rotation.x = 1.5f;
	worldTransform_.translate.z = 10.0f;
	worldTransform_.scale = { 0.5f,0.5f,0.5f };
	worldTransform_.translate.y = 0.5f;
	mt19937 randomEngine(seedGenerator());
	for (uint32_t i = 0; i < enemyMax_; i++)
	{
		enemys_[i] = make_unique<Game3dObject>();
		enemys_[i]->Create();
		enemys_[i]->SetModel(modelHandle);
		enemys_[i]->UseLight(true);
		worldTransforms_[i].Initialize();
		
		uniform_int_distribution<int>distributionColor(1, 4);
		int32_t color = distributionColor(randomEngine);
		uint32_t colorCode = 0xffffffff;
		if (color == RED)
		{
			colorCode = 0xff7f7fff;
		}
		if (color == BLUE)
		{
			colorCode = 0x7f7fff;
		}
		if (color == GREEN)
		{
			colorCode = 0xbfff7fff;
		}
		if (color == WHITE)
		{
			colorCode = 0xffffffff;
		}
		enemys_[i]->SetColor(ColorConverter::ColorVec4Conversion(colorCode));

		uniform_real_distribution<float>distributionRotate(-3.01f, 3.01f);
		uniform_real_distribution<float>distributionRotateMove(-0.01f, 0.01f);

		uniform_real_distribution<float>distributionVelocityX(-7.01f, 7.01f);
		uniform_real_distribution<float>distributionVelocityY(-0.5f, 6.0f);
		uniform_real_distribution<float>distributionVelocityZ(6.0f, 20.0f);
		
		worldTransforms_[i].translate = { distributionVelocityX(randomEngine) ,distributionVelocityY(randomEngine) ,distributionVelocityZ(randomEngine) };
		worldTransforms_[i].rotation = { distributionRotate(randomEngine),distributionRotate(randomEngine) ,distributionRotate(randomEngine) };
		worldTransforms_[i].scale = { 0.3f,0.3f,0.3f };
		rotateVelocity_[i] = {distributionRotateMove(randomEngine) ,distributionRotateMove(randomEngine) ,distributionRotateMove(randomEngine)};
	}

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
	pushADrawFlagCount_++;
	if (pushADrawFlagCount_ >= 40)
	{
		if (isPushADrawFlag_)
		{
			isPushADrawFlag_ = false;
		}
		else {
			isPushADrawFlag_ = true;
		}
		pushADrawFlagCount_ = 0;
	}

	for (uint32_t i = 0; i < enemyMax_; i++)
	{
		worldTransforms_[i].rotation = VectorTransform::Add(worldTransforms_[i].rotation, rotateVelocity_[i]);
		worldTransforms_[i].UpdateMatrix();
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

	//gameObject_->Draw(worldTransform_, viewProjection_);
	skyBox_->Draw(viewProjection_);
	ground_->Draw(viewProjection_);

	for (uint32_t i = 0; i < enemyMax_; i++)
	{
		enemys_[i]->Draw(worldTransforms_[i], viewProjection_);
	}
}

void ClearScene::Flont2dSpriteDraw()
{
	clearTextSprite_->Draw(clearSpriteWorldTransform_, viewProjection_);
	if (isPushADrawFlag_)
	{
		pushASprite_->Draw(pushAWorldTrasform_, viewProjection_);
	}
}
