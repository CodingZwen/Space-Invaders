#pragma once
#include "ParticleSystem.h"
class SpecialEffects
{
	std::shared_ptr<ParticleSystem> particle;

public:
	SpecialEffects();
	~SpecialEffects();


	void update(sf::Time elapsed);
	void draw(sf::RenderTarget &target);
	ParticleSystem* const getParticles() { return particle.get(); }
};

