#include "SpecialEffects.h"



SpecialEffects::SpecialEffects()
{
	particle = std::make_shared<ParticleSystem>(1000);

}


SpecialEffects::~SpecialEffects()
{
}

void SpecialEffects::update(sf::Time elapsed)
{
	particle->update(elapsed);
}

void SpecialEffects::draw(sf::RenderTarget & target)
{
	if (particle)particle->draw(target);
}
