#ifndef PARTICLE_SWARM_OPTIMIZATION_APP_HPP
#define PARTICLE_SWARM_OPTIMIZATION_APP_HPP

#include <QMainWindow>

class ParticleSwarmOptimizationApp : public QMainWindow
{
    Q_OBJECT

public:
    ParticleSwarmOptimizationApp( QWidget* parent = Q_NULLPTR );
    virtual ~ParticleSwarmOptimizationApp() override = default;
};

#endif /// PARTICLE_SWARM_OPTIMIZATION_APP_HPP
