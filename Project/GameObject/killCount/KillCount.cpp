#include "KillCount.h"

void KillCount::Initialize()
{
	texHandle_ = TextureManager::LoadTexture("killCount.png");
	sprite_ = make_unique<Sprite>();
	sprite_->Initialize(new SpriteBoxState);
	sprite_->SetTexHandle(texHandle_);

	worldTransform_.Initialize();
}

void KillCount::Update(uint32_t enemykillCount)
{
	worldTransform_.UpdateMatrix();
}

void KillCount::Draw(ViewProjection view)
{
	sprite_->Draw(worldTransform_, view);

}
