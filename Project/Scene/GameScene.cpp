#include "GameScene.h"

void GameScene::Initialize()
{

	sun_ = make_unique<Sun>();
	sun_->Initialize();

	skyBox_ = make_unique<SkyBox>();
	skyBox_->Initialize();

	ground_ = make_unique<Ground>();
	ground_->Initialize();

	mainCamera_ = make_unique<MainCamera>();
	mainCamera_->Initialize();

	player_ = make_unique<Player>();
	player_->Initialize();

	player_->SetViewProjection(&mainCamera_->GetViewProjection());


	testEnemy_ = make_unique<Enemy>();
	testEnemy_->Initialize({0.0f,0.0f,12.0f});

	collisionManager_ = make_unique<CollisionManager>();

	viewProjection_.Initialize();
}

void GameScene::Update(GameManager* Scene)
{
	Collision();
	mainCamera_->Update(player_->GetWorldTransform());

	player_->Update(mainCamera_->GetViewProjection());

	
	testEnemy_->Update();

	ground_->Update();
	skyBox_->Update();
	sun_->Update();
	Scene;
	
	if (Input::PushKeyPressed(DIK_P))
	{
		LogManager::Log("r\n");
	}



	viewProjection_ = mainCamera_->GetViewProjection();
}

void GameScene::Back2dSpriteDraw()
{
}

void GameScene::Object3dDraw()
{
	player_->Draw(viewProjection_);

	testEnemy_->Draw(viewProjection_);
	ground_->Draw(viewProjection_);
	//skyBox_->Draw(viewProjection_);
}

void GameScene::Flont2dSpriteDraw()
{
}

void GameScene::Collision()
{
	collisionManager_->ClliderClear();

	collisionManager_->ColliderOBBPushBack(player_.get());
	
	for (shared_ptr<PlayerBullet>& bullet : player_->GetBullets())
	{
		collisionManager_->ColliderOBBPushBack(bullet.get());
	}

	collisionManager_->ColliderOBBPushBack(testEnemy_.get());

	collisionManager_->CheckAllCollision();
}
