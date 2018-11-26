#include <particle_swarm_optimization_app.hpp>
#include <particle_swarm_optimization_widget.hpp>

ParticleSwarmOptimizationApp::ParticleSwarmOptimizationApp( QWidget* parent )
    : QMainWindow( parent )
{
    auto widget = new ParticleSwarmOptimizationWidget();

    this->setCentralWidget( widget );
    this->setWindowTitle( "Particle Swarm Optimization" );
}
