#include "SkyBox.h"

void SkyBox::Initialize()
{
	modelHandle_ = ModelManager::LoadObjectFile("SkyBox");
	worldTransform_.Initialize();
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	gameObject_->SetModel(modelHandle_);
	gameObject_->UseLight(true);
}

void SkyBox::Update()
{
	worldTransform_.UpdateMatrix();
}

void SkyBox::Draw(ViewProjection view)
{
	gameObject_->Draw(worldTransform_, view);
}
