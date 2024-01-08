#include "PlayerBulletLine.h"

void PlayerBulletLine::Initialize(const WorldTransform& worldTransform)
{
	modelHandle_ = ModelManager::LoadObjectFile("BulletLine");
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	gameObject_->SetModel(modelHandle_);
	gameObject_->UseLight(true);


	worldTransform_.Initialize();
	worldTransform_.parent = &worldTransform;
	worldTransform_.translate.y = -0.4f;

	worldTransform_.scale = { 0.5f,1.0f,40.0f };

}

void PlayerBulletLine::Update()
{
	gameObject_->SetUvScale({ 1.0f,80.0f,1.0f });
	uvTranslate_.y -= 0.01f;
	gameObject_->SetTranslate({ 0.0f,uvTranslate_.y,0.0f });
	worldTransform_.UpdateMatrix();
}

void PlayerBulletLine::Draw(ViewProjection view)
{
	
	gameObject_->Draw(worldTransform_, view);
}
