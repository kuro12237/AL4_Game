#pragma once
#include"IScene.h"
#include"GameManager.h"
#include"Input.h"
#include"AudioManager.h"
#include"FileLoader.h"
#include"CollisionManager.h"
#include"Particle/Particle.h"
#include"ModelManager.h"
#include"Light/Light.h"

#include"GameObject/FireParticles/FireParticle.h"
#include"Game3dObject.h"

#include"GameObject/Player/Player.h"
#include"GameObject/MainCamera/MainCamera.h"
#include"GameObject/Ground/Ground.h"
#include"GameObject/Sun/Sun.h"
#include"GameObject/SkyBox/SkyBox.h"
#include"GameObject/Enemy/Enemy.h"

#include"GameObject/HitParticle/HitParticle.h"

#include"GameOverScene.h"
#include"ClearScene.h"
#include"GameObject/killCount/KillCount.h"

enum ColorCase
{
	RED = 1,
	GREEN = 2,
	BLUE = 3,
	WHITE = 4,
};

class GameScene :public IScene
{
public:

	GameScene() {};
	~GameScene() {};


	void Initialize()override;

	void Update(GameManager* Scene)override;

	void Back2dSpriteDraw()override;
	void Object3dDraw()override;
	void Flont2dSpriteDraw()override;
private:

	void Collision();

	void EnemysSpown();

	ViewProjection viewProjection_ = {};

	unique_ptr<Ground>ground_ = nullptr;
	unique_ptr<SkyBox>skyBox_ = nullptr;
	unique_ptr<Sun>sun_ = nullptr;

	unique_ptr<MainCamera>mainCamera_ = nullptr;

	unique_ptr<Player>player_ = nullptr;

	list<shared_ptr<Enemy>>enemys_ = {};

	uint32_t enemysSpownTimer_ = 0;
	uint32_t enemysSpownTimerMax_ = 180;
	bool isEnemysSpown_ = false;

	uint32_t enemyMax_ = 20;
	uint32_t enemyCount_ = 0;

	random_device seedGenerator;

	unique_ptr<CollisionManager>collisionManager_ = nullptr;

	uint32_t enemyKillCount_ = 0;

	bool GameStop_ = false;

	unique_ptr<Sprite>missionSprite_ = nullptr;
	WorldTransform missionWorldTransform_{};

	unique_ptr<KillCount>killcount_ = nullptr;

	unique_ptr<Sprite>controlSprite_ = nullptr;
	WorldTransform controlWorldTransform_ = {};
};