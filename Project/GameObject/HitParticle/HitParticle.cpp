#include "HitParticle.h"

void HitParticle::Initialize(Vector3 pos)
{
	texHandle_ = TextureManager::LoadTexture("Particle/Smoke.png");
	
	particle_ = make_unique<Particle>();
	particle_->SetTexHandle(texHandle_);
	particle_->Initialize(new ParticlePlaneState, 1000);
	particle_->SetBlendMode(BlendAdd);
	
	position_ = pos;
}

void HitParticle::Update()
{
	particleList_ = particle_->begin();
	int  count = 0;
	for (Particle_param particle : particleList_)
	{
		particle.color_.w -= 0.01f;
		
		particle.worldTransform_.translate.y += particle.Velocity.y;
		particle.worldTransform_.translate.x += particle.Velocity.x;
		particle.worldTransform_.translate.z += particle.Velocity.z;

		if (particle.color_.w <= 0.0f)
		{
			continue;
		}

		count++;
		particle_->PushList(particle);
	}
}

void HitParticle::Draw(ViewProjection view)
{
	particle_->Draw(view);
}

void HitParticle::Spown(Vector3 pos)
{
	position_ = pos;

    for (int i = 0; i < 30; i++)
	{
		Particle_param p1{};

		mt19937 randomEngine(seedGenerator());
		uniform_real_distribution<float>distribution(0.025f, 0.1f);

		Vector3 randpos = { distribution(randomEngine),distribution(randomEngine) ,distribution(randomEngine) };
		p1.worldTransform_.translate = VectorTransform::Add(VectorTransform::Add(p1.worldTransform_.translate, position_), randpos);
		p1.worldTransform_.scale = { 1, 1, 1 };

		uniform_real_distribution<float>distributionAlpha(0.2f, 1.0f);
		Vector4 color = { 1,1,1,1 };
		p1.color_ = { color.x,color.y,color.z,255 };
		p1.color_ = { color.x,color.y,color.z,distributionAlpha(randomEngine) };

		uniform_real_distribution<float>distributionVelocityX(-0.05f, 0.05f);
		uniform_real_distribution<float>distributionVelocityZ(-0.05f, 0.05f);
		uniform_real_distribution<float>distributionVelocityY(-0.05f, 0.05f);
		p1.Velocity.x = distributionVelocityX(randomEngine);
		p1.Velocity.y = distributionVelocityY(randomEngine);
		p1.Velocity.z = distributionVelocityZ(randomEngine);

		particle_->PushList(p1);
	}
	//spownTimer_ = 0;

	
}
