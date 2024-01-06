#include "Weapon.h"

void Weapon::Initialize()
{
	this->modelHandle_ = ModelManager::LoadObjectFile("Wepon");
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	gameObject_->SetModel(modelHandle_);

	worldTransform_.Initialize();
	worldTransform_.translate.z += 1.0f;
	worldTransform_.scale = { 0.5f,0.5f,0.5f };
}

void Weapon::Update()
{
	worldTransform_.UpdateMatrix();
}

void Weapon::Draw(const ViewProjection& view)
{
	gameObject_->Draw(worldTransform_, view);
}
