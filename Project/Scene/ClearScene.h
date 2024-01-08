#pragma once
#include"IScene.h"
#include"GameManager.h"
#include"TitleScene.h"

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

	ViewProjection viewProjection_ = {};
};
