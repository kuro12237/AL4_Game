#include "TitleScene.h"

void TitleScene::Initialize()
{
	sun_ = make_unique<Sun>();
	sun_->Initialize();

	skyBox_ = make_unique<SkyBox>();
	skyBox_->Initialize();

	ground_ = make_unique<Ground>();
	ground_->Initialize();

	viewProjection_.Initialize();
	viewProjection_.translation_.y = 2.0f;

	titleTexHandle_ = TextureManager::LoadTexture("Title.png");
	titleWorldTransform_.Initialize();
	titleSprite_ = make_unique<Sprite>();
	titleSprite_->Initialize(new SpriteBoxState);
	titleSprite_->SetTexHandle(titleTexHandle_);

	EnemyModelHandle_ = ModelManager::LoadObjectFile("Enemy");
	leftEnemy_ = make_unique<Game3dObject>();
	leftEnemy_->Create();
	leftEnemy_->UseLight(true);
	leftEnemy_->SetModel(EnemyModelHandle_);

	leftEnemyWorldTransform_.Initialize();
	leftEnemyWorldTransform_.translate.x = -2.0f;
	leftEnemyWorldTransform_.translate.z = 10.0f;
	leftEnemyWorldTransform_.translate.y = 0.5f;
	leftEnemyWorldTransform_.rotation.y = 2.6f;

	rightEnemy_ = make_unique<Game3dObject>();
	rightEnemy_->Create();
	rightEnemy_->UseLight(true);
	rightEnemy_->SetModel(EnemyModelHandle_);
	Vector4 color = ColorConverter::ColorVec4Conversion(0x7f7fff);
	rightEnemy_->SetColor(color);

	rightEnemyWorldTransform_.Initialize();
	rightEnemyWorldTransform_.translate.x = +2.0f;
	rightEnemyWorldTransform_.translate.z = 10.0f;
	rightEnemyWorldTransform_.translate.y = 0.5f;
	rightEnemyWorldTransform_.rotation.y = -2.7f;
	
	pushBTexHandle_ = TextureManager::LoadTexture("PushB.png");
	pushBSprite_ = make_unique<Sprite>();
	pushBSprite_->Initialize(new SpriteBoxState);
	pushBSprite_->SetTexHandle(pushBTexHandle_);

	pushBWorldTransform_.Initialize();

}

void TitleScene::Update(GameManager* Scene)
{
	SceneChange::Update();
	if (SceneChange::GetEndFinishFlag())
	{
		GameStop_ = false;

	}
	if (!GameStop_)
	{

		XINPUT_STATE joystate;
		if (Input::GetJoystickState(joystate))
		{

			if (joystate.Gamepad.wButtons & XINPUT_GAMEPAD_B)
			{
				SceneChange::Start();


			}
		}

		if (SceneChange::GetStartFinishFlag())
		{
			Scene->ChangeState(new GameScene);
			return;
		}

		pushBDrawFlagCount_++;
		if (pushBDrawFlagCount_ >= 40)
		{
			if (isPushBDrawFlag_)
			{
				isPushBDrawFlag_ = false;
			}
			else {
				isPushBDrawFlag_ = true;
			}
			pushBDrawFlagCount_ = 0;
		}
	}

	ground_->Update();
	skyBox_->Update();
	sun_->Update();
	titleWorldTransform_.UpdateMatrix();
	leftEnemyWorldTransform_.UpdateMatrix();
	rightEnemyWorldTransform_.UpdateMatrix();
	pushBWorldTransform_.UpdateMatrix();
	
	viewProjection_.UpdateMatrix();
}

void TitleScene::Back2dSpriteDraw()
{
}

void TitleScene::Object3dDraw()
{
	leftEnemy_->Draw(leftEnemyWorldTransform_, viewProjection_);
	rightEnemy_->Draw(rightEnemyWorldTransform_, viewProjection_);
	ground_->Draw(viewProjection_);
	skyBox_->Draw(viewProjection_);
}

void TitleScene::Flont2dSpriteDraw()
{
	titleSprite_->Draw(titleWorldTransform_, viewProjection_);

	if (isPushBDrawFlag_)
	{
		pushBSprite_->Draw(pushBWorldTransform_, viewProjection_);
	}
	SceneChange::Draw(viewProjection_);
}
