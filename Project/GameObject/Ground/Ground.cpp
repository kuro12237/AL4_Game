#include "Ground.h"

void Ground::Initialize()
{
	this->modelHandle_ = ModelManager::LoadObjectFile("Ground");
	this->gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	gameObject_->SetModel(this->modelHandle_);

	this->worldTransform_.Initialize();
}

void Ground::Update()
{
	this->worldTransform_.UpdateMatrix();
}

void Ground::Draw(ViewProjection view)
{
	gameObject_->Draw(this->worldTransform_, view);
}
