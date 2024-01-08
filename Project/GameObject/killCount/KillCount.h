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


	uint32_t texHandle_ = 0;

	unique_ptr<Sprite>sprite_ = nullptr;
	WorldTransform worldTransform_ = {};

};


