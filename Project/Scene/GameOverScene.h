#pragma once
#include"IScene.h"
#include"GameManager.h"
#include"TitleScene.h"
#include"GameObject/SceneChange/SceneChange.h"

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
	unique_ptr<Ground>ground_ = nullptr;
	unique_ptr<SkyBox>skyBox_ = nullptr;
	unique_ptr<Sun>sun_ = nullptr;
	ViewProjection viewProjection_ = {};

	unique_ptr<Game3dObject>gameObject_ = nullptr;
	WorldTransform worldTransform_ = {};

	unique_ptr<Sprite>OverTextSprite_ = nullptr;
	WorldTransform OverTextWorldTransform_ = {};

	unique_ptr<Sprite>pushASprite_ = nullptr;
	WorldTransform pushAWorldTrasform_ = {};

	bool isPushADrawFlag_ = false;

	uint32_t pushADrawFlagCount_ = 0;
};
