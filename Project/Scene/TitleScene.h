#pragma once
#include"IScene.h"
#include"GameManager.h"
#include"GameObject/Ground/Ground.h"
#include"GameObject/SkyBox/SkyBox.h"
#include"GameObject/Sun/Sun.h"
#include"GameObject/SceneChange/SceneChange.h"
#include"GameObject/FireParticles/FireParticle.h"

class TitleScene :public IScene
{
public:

	TitleScene() {};
	~TitleScene() {};

	void Initialize()override;

	void Update(GameManager* Scene)override;

	void Back2dSpriteDraw()override;
	void Object3dDraw()override;
	void Flont2dSpriteDraw()override;

private:

	unique_ptr<Ground>ground_ = nullptr;
	unique_ptr<SkyBox>skyBox_ = nullptr;
	unique_ptr<Sun>sun_ = nullptr;

	uint32_t titleTexHandle_ = 0;
	unique_ptr<Sprite>titleSprite_ = nullptr;
	WorldTransform titleWorldTransform_{};

	ViewProjection viewProjection_ = {};


	uint32_t EnemyModelHandle_ = 0;

	unique_ptr<Game3dObject>leftEnemy_ = nullptr;
	WorldTransform leftEnemyWorldTransform_{};

	unique_ptr<Game3dObject>rightEnemy_ = nullptr;
	WorldTransform rightEnemyWorldTransform_{};

	uint32_t pushBTexHandle_ = 0;
	unique_ptr<Sprite>pushBSprite_ = nullptr;
	WorldTransform pushBWorldTransform_ = {};

	bool isPushBDrawFlag_ = false;
	uint32_t pushBDrawFlagCount_ = 0;
	bool GameStop_ = true;
	unique_ptr<FireParticle>leftFire_ = nullptr;
	PointLight_param leftFireLight_ = {};
	unique_ptr<FireParticle>rightFire_ = nullptr;
	PointLight_param rightFireLight_ = {};
};
