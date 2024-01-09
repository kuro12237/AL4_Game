#pragma once
#include"Cleyera.h"
#include"IScene.h"
#include"../DebugTools/Camera/DebugCamera.h"
#include"GameScene.h"
#include"TitleScene.h"
#include"GameObject/SceneChange/SceneChange.h"
#include"ClearScene.h"
class GameManager
{
public:

	GameManager();
	~GameManager();

    void Run();
    void ChangeState(IScene *newScene);

private:

	IScene* Scene_ = nullptr;

};

