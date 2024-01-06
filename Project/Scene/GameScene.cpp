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

	viewProjection_.Initialize();
}

void GameScene::Update(GameManager* Scene)
{
	mainCamera_->Update(player_->GetWorldTransform());

	player_->Update(mainCamera_->GetViewProjection());
	ground_->Update();
	
	Scene;
	
	ImGui::Begin("view");
	ImGui::DragFloat3("translate", &viewProjection_.translation_.x, -0.1f, 0.1f);
	ImGui::End();
	
	//viewProjection_.UpdateMatrix();
	viewProjection_ = mainCamera_->GetViewProjection();
}

void GameScene::Back2dSpriteDraw()
{
}

void GameScene::Object3dDraw()
{
	player_->Draw(viewProjection_);
	ground_->Draw(viewProjection_);
}

void GameScene::Flont2dSpriteDraw()
{
}
