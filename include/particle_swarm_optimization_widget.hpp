#ifndef PARTICLE_SWARM_OPTIMIZATION_WIDGET_HPP
#define PARTICLE_SWARM_OPTIMIZATION_WIDGET_HPP

#include <QWidget>
#include <QTextEdit>
#include <QComboBox>

#include <QVector>

class ParticleSwarmOptimizationWidget : public QWidget
{
    Q_OBJECT

public:
    ParticleSwarmOptimizationWidget( QWidget* parent = Q_NULLPTR );
    virtual ~ParticleSwarmOptimizationWidget() override = default;

public slots:
    void optimizeFunction();

private:
    struct Agent
    {
        QVector< qreal > position;
        QVector< qreal > direction;
        QVector< qreal > personalBestPos;
        qreal personalBest;
    };

    QTextEdit* outputWidget;
    QComboBox* expressionEditWidget;

    static const qint32 N_AGENTS = 10;
};

#endif /// PARTICLE_SWARM_OPTIMIZATION_WIDGET_HPP
