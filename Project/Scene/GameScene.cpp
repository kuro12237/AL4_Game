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

	uint32_t texHandle = TextureManager::LoadTexture("missionTex.png");
	missionSprite_ = make_unique<Sprite>();
	missionSprite_->Initialize(new SpriteBoxState);
	missionSprite_->SetTexHandle(texHandle);

	missionWorldTransform_.Initialize();
	
	killcount_ = make_unique<KillCount>();
	killcount_->Initialize();

	controlSprite_ = make_unique<Sprite>();
	controlSprite_->Initialize(new SpriteBoxState);
	controlSprite_->SetTexHandle(TextureManager::LoadTexture("ControlText.png"));

	controlWorldTransform_.Initialize();

	viewProjection_.Initialize();
}

void GameScene::Update(GameManager* Scene)
{

	if (!GameStop_)
	{


		Collision();
		mainCamera_->Update(player_->GetWorldTransform());

		player_->Update(mainCamera_->GetViewProjection());

		EnemysSpown();

		for (shared_ptr<Enemy>enemy : enemys_)
		{
			enemy->Update(player_->GetIsHit());
		}

		ImGui::Begin("size");
		ImGui::Text("%d", uint32_t(enemys_.size()));
		ImGui::Text("%d", enemyCount_);
		ImGui::Text("killcount %d", enemyKillCount_);
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
				enemyKillCount_++;
				enemyCount_--;
			}
		}

		ground_->Update();
		skyBox_->Update();
		sun_->Update();
		killcount_->Update(enemyKillCount_);
		missionWorldTransform_.UpdateMatrix();
		controlWorldTransform_.UpdateMatrix();
		Scene;
	}

	viewProjection_ = mainCamera_->GetViewProjection();
	
	if (!GameStop_)
	{
		if (player_->GetHp() == 0)
		{
			GameStop_ = true;
			Scene->ChangeState(new GameOverScene);
			return;
		}
		if (enemyKillCount_ >= 15)
		{
			GameStop_ = true;
			Scene->ChangeState(new ClearScene);
			return;
		}


	}

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
	player_->SpriteDraw(viewProjection_);
	missionSprite_->Draw(missionWorldTransform_, viewProjection_);
	controlSprite_->Draw(controlWorldTransform_, viewProjection_);
	killcount_->Draw(viewProjection_);
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

		
		uniform_int_distribution<int>colorDistribution(1,4);
		
		uint32_t resultRandColor = colorDistribution(randomEngine);

		uint32_t colorCode = 0xffffffff;
		if (resultRandColor == RED)
		{
			colorCode = 0xff7f7fff;
		}
		if (resultRandColor == BLUE)
		{
			colorCode = 0x7f7fff;
		}
		if (resultRandColor == GREEN)
		{
			colorCode = 0xbfff7fff;
		}
		if (resultRandColor == WHITE)
		{
			colorCode = 0xffffffff;
		}
		
		shared_ptr<Enemy>testEnemy_ = nullptr;
		testEnemy_ = make_shared<Enemy>();
		testEnemy_->Initialize(SpownPosition,colorCode);
		enemys_.push_back(testEnemy_);
		enemyCount_++;
		isEnemysSpown_ = false;
	}

}
