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

	collisionManager_ = make_unique<CollisionManager>();

	
	viewProjection_.Initialize();
}

void GameScene::Update(GameManager* Scene)
{
	Collision();
	mainCamera_->Update(player_->GetWorldTransform());

	player_->Update(mainCamera_->GetViewProjection());

	if (Input::PushKeyPressed(DIK_Y))
	{
		shared_ptr<Enemy>testEnemy_ = nullptr;
		testEnemy_ = make_shared<Enemy>();
		testEnemy_->Initialize({ 0.0f,0.0f,12.0f });
		enemys_.push_back(testEnemy_);
	}

	EnemysSpown();

	for (shared_ptr<Enemy>enemy : enemys_)
	{
		enemy->Update();
	}

	ImGui::Begin("size");
	ImGui::Text("%d", uint32_t(enemys_.size()));
	ImGui::Text("%d", enemyCount_);
	ImGui::End();

	if (enemys_.remove_if([](shared_ptr<Enemy> enemy) {

		if (!enemy->GetIsAlive()) {
			enemy.reset();

			return true;
		}

		return false;

		})) {
		if (enemyCount_ >= 0)
		{
			enemyCount_--;
		}
	}

	ground_->Update();
	skyBox_->Update();
	sun_->Update();
	Scene;
	
	viewProjection_ = mainCamera_->GetViewProjection();
}

void GameScene::Back2dSpriteDraw()
{
}

void GameScene::Object3dDraw()
{
	player_->Draw(viewProjection_);

	for (shared_ptr<Enemy>enemy : enemys_)
	{
		enemy->Draw(viewProjection_);
	}
	ground_->Draw(viewProjection_);
	skyBox_->Draw(viewProjection_);
}

void GameScene::Flont2dSpriteDraw()
{
	player_->ParticleDraw(viewProjection_);
}

void GameScene::Collision()
{
	collisionManager_->ClliderClear();

	collisionManager_->ColliderOBBPushBack(player_.get());
	
	for (shared_ptr<PlayerBullet>& bullet : player_->GetBullets())
	{
		collisionManager_->ColliderOBBPushBack(bullet.get());
	}

	for (shared_ptr<Enemy>enemy : enemys_)
	{
		collisionManager_->ColliderOBBPushBack(enemy.get());
	}

	collisionManager_->CheckAllCollision();
}

void GameScene::EnemysSpown()
{
	mt19937 randomEngine(seedGenerator());
	
	enemysSpownTimer_++;
	if (enemysSpownTimer_ > enemysSpownTimerMax_)
	{
		isEnemysSpown_ = true;
		enemysSpownTimer_ = 0;
	}

	if (isEnemysSpown_ && enemyCount_ <= enemyMax_)
	{
		mt19937 randomEngine(seedGenerator());
		uniform_real_distribution<float>distribution(-14.0f,14.0f);
		
		Vector3 SpownPosition = {};
		SpownPosition.x = distribution(randomEngine);
		SpownPosition.y = 0;
		SpownPosition.z = distribution(randomEngine);

		shared_ptr<Enemy>testEnemy_ = nullptr;
		testEnemy_ = make_shared<Enemy>();
		testEnemy_->Initialize(SpownPosition);
		enemys_.push_back(testEnemy_);
		enemyCount_++;
		isEnemysSpown_ = false;
	}

}
