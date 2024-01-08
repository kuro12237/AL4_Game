#include "Player.h"

void Player::Initialize()
{
	this->modelbodyHandle_ = ModelManager::LoadObjectFile("Player");

	worldTransform_.Initialize();
	worldTransform_.translate.y = 0.5f;

	model_ = make_unique<Game3dObject>();
	model_->Create();
	model_->SetModel(modelbodyHandle_);
	model_->UseLight(true);

	reticleWorldTransform.Initialize();

	SetSize({0.5f,0.5f,0.5f});

	SetCollosionAttribute(kCollisionAttributePlayer);
	SetCollisionMask(kCollisionMaskPlayer);
}

void Player::Update(const ViewProjection& view)
{
	if (!isAttack_)
	{
		Control(view);
	}
	Attack();
	AnimationMove();

	worldTransform_.UpdateMatrix();
	
	for (shared_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->Update();
	}

	bullets_.remove_if([](shared_ptr<PlayerBullet> bullet) {

		if (!bullet->GetIsAlive()) {
			bullet.reset();
			return true;
		}
		return false;

	});

	OBBCollider::SetSize({ 1.0f,1.0f,1.0f });
	OBBCollider::SetRotate(this->worldTransform_.rotation);
}

void Player::Draw(ViewProjection view)
{

	model_->Draw(worldTransform_, view);

	for (shared_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->Draw(view);
	}

}

void Player::OnCollision(uint32_t id)
{
	id;
}

void Player::Control(const ViewProjection& view)
{
	view;
	Input::NoneJoyState(joyState_);
	Vector3 Move{};
	bool isMove = false;
	Vector3 Rotate{};

	if (Input::GetJoystickState(joyState_))
	{
		//左
		Move.x += (float)joyState_.Gamepad.sThumbLX / SHRT_MAX;
		Move.y += (float)joyState_.Gamepad.sThumbLY / SHRT_MAX;
		//左
		
		Rotate.y = (float)joyState_.Gamepad.sThumbRX / SHRT_MAX * 0.1f;
		//Limit
		//左
		if (Rotate.x < 0.05f && Rotate.x > -0.05f)
		{
			Rotate.x = 0;
		}
		if (Rotate.y < 0.05f && Rotate.y > -0.05f)
		{
			Rotate.y = 0;
		}
		//Limit
	    //左
		if (Move.x < 0.05f && Move.x > -0.05f)
		{
			Move.x = 0;
		}
		if (Move.y < 0.05f && Move.y > -0.05f)
		{
			Move.y = 0;
		}

		if (VectorTransform::Length(Move) > 0.7f) {
			isMove = true;
			
		}
	}

	worldTransform_.rotation = VectorTransform::Add(worldTransform_.rotation, Rotate);

	if (isMove)
	{
		Move = VectorTransform::Multiply(Move, 0.2f);

		Matrix4x4 rotate = MatrixTransform::RotateYMatrix(CameraViewProjection_->rotation_.y);
		Move = VectorTransform::TransformNormal(Move, rotate);
		worldTransform_.translate.x += Move.x;
		worldTransform_.translate.z += Move.y;
		destinationAngleY_ = std::atan2(Move.x, Move.z);
	}

}

void Player::Attack()
{

	const float kMoveLimitX = 30.0f;
	const float kMoveLimitZ = 30.0f;
	worldTransform_.translate.x = max(worldTransform_.translate.x, -kMoveLimitX);
	worldTransform_.translate.x = min(worldTransform_.translate.x, kMoveLimitX);
	worldTransform_.translate.z = max(worldTransform_.translate.z, -kMoveLimitZ);
	worldTransform_.translate.z = min(worldTransform_.translate.z, kMoveLimitZ);

	Vector3 Ppos{};
	Ppos.x = worldTransform_.matWorld.m[3][0];
	Ppos.y = worldTransform_.matWorld.m[3][1];
	Ppos.z = worldTransform_.matWorld.m[3][2];
	worldTransform_.UpdateMatrix();

	const float kDistancePlayerTo3DReticle = 40.0f;
	Vector3 offset = { 0.0f, 0.0f, 1.0f };

	offset = VectorTransform::TransformNormal(offset, worldTransform_.matWorld);
	offset = VectorTransform::Normalize(offset);
	offset = VectorTransform::Multiply(offset, kDistancePlayerTo3DReticle);

	reticleWorldTransform.translate = VectorTransform::Add(offset, Ppos);
	reticleWorldTransform.UpdateMatrix();

	Vector3 Rpos{};
	Rpos.x = reticleWorldTransform.matWorld.m[3][0];
	Rpos.y = reticleWorldTransform.matWorld.m[3][1];
	Rpos.z = reticleWorldTransform.matWorld.m[3][2];

	RPNormalize = VectorTransform::Subtruct(Rpos, Ppos);
	RPNormalize = VectorTransform::Normalize(RPNormalize);


	prevIsAttack = isAttack_;
	if (Input::GetJoystickState(joyState_))
	{
		if (joyState_.Gamepad.bRightTrigger && !isAttack_)
		{
			shared_ptr<PlayerBullet> bullet = make_shared<PlayerBullet>();
			bullet->Initialize(worldTransform_.translate,RPNormalize);
			bullets_.push_back(bullet);
			isAttack_ = true;
		}
	}

	if (isAttack_)
	{
		AttackCoolTime_++;
		if (AttackCoolTime_ > AttackCoolTimeMax_)
		{
			isAttack_ = false;
			AttackCoolTime_ = 0;
		}
	}

}

void Player::AnimationMove()
{

}

float Player::LerpShortAngle(const float& a, const float& b, float t) {
	//角度差分を求める
	float diff = b - a;
	//角度を[-2PI,+2PI]に補正する
	float PI = 3.14159265359f;

	float PI2 = 2.0f * 3.14159265359f;
	float theta = std::fmod(diff, PI2);
	//角度を[-PI,PI]に補正する
	if (theta >= PI) {
		theta -= PI2;
	}
	if (theta <= -PI) {
		theta += PI2;
	}

	return a + theta * t;
}