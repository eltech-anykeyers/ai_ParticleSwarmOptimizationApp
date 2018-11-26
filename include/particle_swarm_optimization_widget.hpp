#ifndef PARTICLE_SWARM_OPTIMIZATION_WIDGET_HPP
#define PARTICLE_SWARM_OPTIMIZATION_WIDGET_HPP

#include <QWidget>
#include <QTextEdit>
#include <QComboBox>

class ParticleSwarmOptimizationWidget : public QWidget
{
    Q_OBJECT

public:
    ParticleSwarmOptimizationWidget( QWidget* parent = Q_NULLPTR );
    virtual ~ParticleSwarmOptimizationWidget() override = default;

public slots:
    void optimizeFunction();

private:
    QTextEdit* outputWidget;
    QComboBox* expressionEditWidget;
};

#endif /// PARTICLE_SWARM_OPTIMIZATION_WIDGET_HPP
