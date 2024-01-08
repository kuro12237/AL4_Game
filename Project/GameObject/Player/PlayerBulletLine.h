#pragma once
#include"Game3dObject.h"

class PlayerBulletLine
{
public:
	PlayerBulletLine() {};
	~PlayerBulletLine() {};

	void Initialize(const WorldTransform&worldTransform);

	void Update();

	void Draw(ViewProjection view);

private:

	unique_ptr<Game3dObject>gameObject_ = nullptr;
	WorldTransform worldTransform_ = {};
	uint32_t modelHandle_ = 0;
	
	Vector2 uvTranslate_ = { 0,0 };
};
