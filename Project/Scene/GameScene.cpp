#include "GameScene.h"

void GameScene::Initialize()
{
	player_ = make_unique<Player>();
	player_->Initialize();

	ground_ = make_unique<Ground>();
	ground_->Initialize();

	mainCamera_ = make_unique<MainCamera>();
	mainCamera_->Initialize();

	player_->SetViewProjection(&mainCamera_->GetViewProjection());

	sun_ = make_unique<Sun>();
	sun_->Initialize();

	skyBox_ = make_unique<SkyBox>();
	skyBox_->Initialize();

	viewProjection_.Initialize();
}

void GameScene::Update(GameManager* Scene)
{
	mainCamera_->Update(player_->GetWorldTransform());

	player_->Update(mainCamera_->GetViewProjection());
	ground_->Update();
	skyBox_->Update();
	sun_->Update();
	Scene;
	
	

	viewProjection_ = mainCamera_->GetViewProjection();
}

void GameScene::Back2dSpriteDraw()
{
}

void GameScene::Object3dDraw()
{
	player_->Draw(viewProjection_);
	ground_->Draw(viewProjection_);
	skyBox_->Draw(viewProjection_);
}

void GameScene::Flont2dSpriteDraw()
{
}
