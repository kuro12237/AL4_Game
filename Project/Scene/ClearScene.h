#pragma once
#include"IScene.h"
#include"GameManager.h"
#include"TitleScene.h"
#include"GameObject/FireParticles/FireParticle.h"

class ClearScene :public IScene
{
public:

	ClearScene() {};
	~ClearScene() {};

	void Initialize()override;

	void Update(GameManager* Scene)override;

	void Back2dSpriteDraw()override;
	void Object3dDraw()override;
	void Flont2dSpriteDraw()override;

private:
	unique_ptr<Ground>ground_ = nullptr;
	unique_ptr<SkyBox>skyBox_ = nullptr;
	unique_ptr<Sun>sun_ = nullptr;
	
	unique_ptr<Sprite>pushASprite_ = nullptr;
	WorldTransform pushAWorldTrasform_ = {};

	unique_ptr<Sprite>clearTextSprite_ = nullptr;
	WorldTransform clearSpriteWorldTransform_ = {};

	unique_ptr<Game3dObject>gameObject_ = nullptr;
	WorldTransform worldTransform_ = {};

	ViewProjection viewProjection_ = {};
	bool isPushADrawFlag_ = false;

	uint32_t pushADrawFlagCount_ = 0;

	const static uint32_t enemyMax_ = 20;
	unique_ptr<Game3dObject>enemys_[enemyMax_]{};
	WorldTransform worldTransforms_[enemyMax_]{};
	Vector3 rotateVelocity_[enemyMax_]{};
	random_device seedGenerator;

};
