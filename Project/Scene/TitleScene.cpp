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

	leftFire_ = make_unique<FireParticle>();
	leftFire_->Initialize({ 2.0f,0.5f,5.0f });
	leftFireLight_.position = { 2.5f,0.5f,5.0f };
	leftFireLight_.radious = 1.8f;
	leftFireLight_.color = { 0,154.0f,255,255 };
	leftFireLight_.intencity = 5.9f;
	leftFireLight_.decay = 10.5f;

	rightFire_ = make_unique<FireParticle>();
	rightFire_->Initialize({ -2.0f,0.5f,5.0f });
	rightFireLight_.position = { -2.5f,0.5f,5.0f };
	rightFireLight_.radious = 1.8f;
	rightFireLight_.color = { 0,154.0f,255,255 };
	rightFireLight_.intencity = 5.9f;
	rightFireLight_.decay = 10.5f;

	
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
	LightingManager::AddList(leftFireLight_);
	LightingManager::AddList(rightFireLight_);


	ground_->Update();
	skyBox_->Update();
	sun_->Update();
	titleWorldTransform_.UpdateMatrix();
	leftEnemyWorldTransform_.UpdateMatrix();
	rightEnemyWorldTransform_.UpdateMatrix();
	pushBWorldTransform_.UpdateMatrix();
	leftFire_->Update({ 2.0f,0.5f,3.0f });
	rightFire_->Update({ -2.0f,0.5f,3.0f });
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
	
	if (isPushBDrawFlag_)
	{
		pushBSprite_->Draw(pushBWorldTransform_, viewProjection_);
	}

	leftFire_->Draw(viewProjection_);
	rightFire_->Draw(viewProjection_);
	titleSprite_->Draw(titleWorldTransform_, viewProjection_);

	SceneChange::Draw(viewProjection_);
}
