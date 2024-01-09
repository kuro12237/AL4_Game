#pragma once
#include"Sprite/Sprite.h"

class SceneChange
{
public:
	SceneChange() {};
	~SceneChange() {};

	static SceneChange* Getinstance();

	static void Initialize();

	static void Update();

	static void Draw(ViewProjection view);

	static void Start();

	static bool GetStartFinishFlag() { return SceneChange::Getinstance()->StartfinishFlag_; }
	static bool GetEndFinishFlag() { return SceneChange::Getinstance()->EndFinishFlag_; }
	static bool GetStartFlag() { return SceneChange::Getinstance()->StartFlag_; }
	static bool GetEbdFlag() { return SceneChange::Getinstance()->EndFlag_; }

	static void ClearFlag()
	{
		SceneChange::Getinstance()->EndFinishFlag_ = true;
		SceneChange::Getinstance()->StartfinishFlag_ = false;
		SceneChange::Getinstance()->StartFlag_ = false;
		SceneChange::Getinstance()->EndFlag_ = false;
	}
private:

	bool StartFlag_ = false;
	bool StartfinishFlag_ = false;

	bool EndFlag_ = false;
	bool EndFinishFlag_ = true;
	uint32_t texHandle_ = 0;

	const static uint32_t SpriteMax = 60;
	const static uint32_t SpriteXMax = 10;
	const static uint32_t SpriteYMax = 6;

	unique_ptr<Sprite>sprite_[SpriteMax]={};
	WorldTransform worldTransform_[SpriteMax]={};

};