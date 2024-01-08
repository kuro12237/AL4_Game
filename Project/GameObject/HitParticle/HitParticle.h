#pragma once
#include"Particle/Particle.h"

class HitParticle
{
public:
	HitParticle() {};
	~HitParticle() {};

	void Initialize(Vector3 pos);

	void Update();

	void Draw(ViewProjection view);

	void Spown(Vector3 pos);

private:
	unique_ptr<Particle>particle_ = nullptr;
	list<Particle_param> particleList_{};
	uint32_t texHandle_ = 0;
	Vector3 position_ = {};

	uint32_t spownTimer_ = 0;

	random_device seedGenerator;
};

