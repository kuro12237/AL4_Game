#include "KillCount.h"

void KillCount::Initialize()
{
	texHandle_ = TextureManager::LoadTexture("killCount.png");
	sprite_ = make_unique<Sprite>();
	sprite_->Initialize(new SpriteBoxState);
	sprite_->SetTexHandle(texHandle_);
	sprite_->SetSrc({ 0.0f,0.0f }, { 0.0f,0.25f }, { 0.25f,0.0f }, { 0.25f,0.25f });
	worldTransform_.Initialize();
	worldTransform_.scale = { 0.125f,0.125f,0.125f };
	worldTransform_.translate.x = 1120;

	textSprite_ = make_unique<Sprite>();
	textSprite_->Initialize(new SpriteBoxState);
	textSprite_->SetTexHandle(TextureManager::LoadTexture("KillCountText.png"));
	textWorldTransform_.Initialize();
	textWorldTransform_.translate.x += 80.0f;
	textWorldTransform_.translate.y += 42.0f;
}

void KillCount::Update(uint32_t enemykillCount)
{
	
	if (enemykillCount != 0)
	{
		isDrawFlag_ = true;
	}

	
	if (isDrawFlag_&&prevKillCount_!=enemykillCount)
	{
		
		xy.x = float(count_);

		count_++;
	
		if ((count_-1) / 4  - heightCount_ == 1.0f)
		{
			heightCount_++;
			xy.x = 0.0f;
			xy.y += 0.25f;
		}

		

		Vector2 LT{};
		LT.x = 0.0f+(xy.x)*0.25f;
		LT.y = xy.y;
		Vector2 LB{};
		LB.x = 0.0f + (xy.x) * 0.25f;
		LB.y = xy.y + 0.25f;

		Vector2 RT{};
		RT.x = 0.25f + (xy.x) * 0.25f;
		RT.y = xy.y;
		Vector2 RB{};
		RB.x = 0.25f + (xy.x) * 0.25f;
		RB.y = xy.y + 0.25f;
		sprite_->SetSrc(LT, LB, RT, RB);
	}
	prevKillCount_ = enemykillCount;
	textWorldTransform_.UpdateMatrix();
	worldTransform_.UpdateMatrix();
}

void KillCount::Draw(ViewProjection view)
{
	if (isDrawFlag_)
	{
		textSprite_->Draw(textWorldTransform_, view);
		sprite_->Draw(worldTransform_, view);
	}
}
