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

	unique_ptr<Player>player_ = nullptr;
	ViewProjection viewProjection_ = {};

	unique_ptr<MainCamera>mainCamera_ = nullptr;
	unique_ptr<Ground>ground_ = nullptr;

};