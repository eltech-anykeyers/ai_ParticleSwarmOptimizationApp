#include <particle_swarm_optimization_app.hpp>
#include <QApplication>

int main( int argc, char* argv[] )
{
    QApplication app( argc, argv );
    ParticleSwarmOptimizationApp mainWindow;
    mainWindow.show();

    return app.exec();
}
