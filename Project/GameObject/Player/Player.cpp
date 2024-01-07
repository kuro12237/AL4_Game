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

	weapon_ = make_unique<Weapon>();
	weapon_->Initialize();
	weapon_->SetParent(worldTransform_);
}

void Player::Update(const ViewProjection& view)
{
	Control(view);

	Attack();

	const float kMoveLimitX = 30.0f;
	const float kMoveLimitZ = 30.0f;
	worldTransform_.translate.x = max(worldTransform_.translate.x, -kMoveLimitX);
	worldTransform_.translate.x = min(worldTransform_.translate.x, kMoveLimitX);
	worldTransform_.translate.z = max(worldTransform_.translate.z, -kMoveLimitZ);
	worldTransform_.translate.z = min(worldTransform_.translate.z, kMoveLimitZ);

	worldTransform_.UpdateMatrix();
	weapon_->Update();
}

void Player::Draw(ViewProjection view)
{
	model_->Draw(worldTransform_, view);
	weapon_->Draw(view);
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
	if (Input::GetJoystickState(joyState_))
	{
		if (joyState_.Gamepad.bRightTrigger && !isAttack_)
		{
			weapon_->Attack();
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