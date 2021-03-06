/* 
 * File:   ParticleSystemDefinitions.h
 * Author: Roberto
 *
 * Created on 10 de abril de 2011, 20:19
 */

#ifndef PARTICLESYSTEMDEFINITIONS_H
#define	PARTICLESYSTEMDEFINITIONS_H

#include <string>
#include <WasabiEngine/Utils/Vectors.h>
#include <WasabiEngine/GraphicEngine/ColourValue.h>

namespace WasabiEngine {

    enum ParticleSystemType {
        PARTICLE_LINEAR,
        PARTICLE_RADIAL
    };

    class ParticleSystemDef {
    public:
        /**
         * The maximum particles amount the system can emmit.
         */
        int maxParticles;
        /**
         * Path to the texture to apply to each particle
         */
        std::string texturePath;
        /**
         * System life time
         */
        float systemLifeSpan;
        /**
         * The general life span of each particle (in ms).
         */
        float particleLifeSpan;
        /**
         * The maximum particles amount the system can emmit per second.
         */
        float emissionRate;
        /**
         * A randomness factor, which is used to initialize the particles's
         * lifeSpan, growRate and acceleration in a different way.
         */
        int chaos;
        /**
         * The gravity which will vary the particles' movement.
         */
        float gravity;
        /**
         * Acceleration of each particle
         */
        float acceleration;
        /**
         * The particle's base size. All the particles will have this size.
         */
        float baseSize;
        /**
         * The speed the baseSize will be changed at. Value between 0 and positive infinity. With 1 the size remains constant. Less than 1 the particle shrinks.
         */
        float growRate;
        /**
         * The color the particles will have. It's the same color for all of them.
         */
        ColourValue color;
        virtual ParticleSystemType getType() const = 0;
    };

    class LinearParticleSystemDef : public ParticleSystemDef {
    public:
        WasVec2d emissionVelocity;

        ParticleSystemType getType() const {
            return PARTICLE_LINEAR;
        }
    };

    class RadialParticleSystemDef : public ParticleSystemDef {
    public:
        float emissionVelocity;

        ParticleSystemType getType() const {
            return PARTICLE_RADIAL;
        }
    };

}

#endif	/* PARTICLESYSTEMDEFINITIONS_H */

