#pragma once
#include"Sprite/Sprite.h"

class KillCount
{
public:
	KillCount() {};
	~KillCount() {};

	void Initialize();

	void Update(uint32_t enemykillCount);

	void Draw(ViewProjection view);

private:

	uint32_t prevKillCount_ = 0;
	uint32_t texHandle_ = 0;

	unique_ptr<Sprite>sprite_ = nullptr;
	WorldTransform worldTransform_ = {};
	bool isDrawFlag_ = false;

	Vector2 xy{};

	Vector2 widthHeight_{};

	unique_ptr<Sprite>textSprite_ = nullptr;
	WorldTransform textWorldTransform_{};

	int32_t count_ = 0;
	int32_t heightCount_ = 0;
};


