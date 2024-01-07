#include "Weapon.h"

void Weapon::Initialize()
{
	this->modelHandle_ = ModelManager::LoadObjectFile("Wepon");
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	gameObject_->SetModel(modelHandle_);
	gameObject_->UseLight(true);

	worldTransform_.Initialize();
	worldTransform_.translate.z += 1.0f;
	worldTransform_.scale = { 0.5f,0.5f,0.5f };
}

void Weapon::Update()
{
	if (isAttack_)
	{
		worldTransform_.rotation.x += 0.1f;
		if (worldTransform_.rotation.x >= 2.0f)
		{
			isAttack_ = false;
		}
	}

	worldTransform_.UpdateMatrix();
}

void Weapon::Draw(const ViewProjection& view)
{
	if (isAttack_)
	{
		gameObject_->Draw(worldTransform_, view);
	}
}

void Weapon::Attack()
{
	worldTransform_.rotation.x = 0.0f;
	isAttack_ = true;
}
