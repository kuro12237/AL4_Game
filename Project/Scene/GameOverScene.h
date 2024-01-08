#pragma once
#include"IScene.h"
#include"GameManager.h"
#include"TitleScene.h"

class GameOverScene :public IScene
{
public:

	GameOverScene() {};
	~GameOverScene() {};

	void Initialize()override;

	void Update(GameManager* Scene)override;

	void Back2dSpriteDraw()override;
	void Object3dDraw()override;
	void Flont2dSpriteDraw()override;

private:

	ViewProjection viewProjection_ = {};
};
