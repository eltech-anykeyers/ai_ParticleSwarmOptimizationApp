#include <particle_swarm_optimization_widget.hpp>
#include <parser.hpp>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

#include <QRandomGenerator>

ParticleSwarmOptimizationWidget::ParticleSwarmOptimizationWidget( QWidget* parent )
    : QWidget( parent )
{
    expressionEditWidget = new QComboBox();
    expressionEditWidget->setEditable( true );
    expressionEditWidget->addItem( "( @x1 - @x2 )^2 + (( @x1 + @x2 - 10 ) / 3 )^2" );
    expressionEditWidget->addItem( "100 * ( @x1^2 - @x2 )^2 + ( 1 - @x1 )^2" );

    auto optimizeButton = new QPushButton( "Optimize" );
    connect( optimizeButton, &QPushButton::clicked,
             this, &ParticleSwarmOptimizationWidget::optimizeFunction );

    auto inputLayout = new QHBoxLayout();
    inputLayout->addWidget( expressionEditWidget );
    inputLayout->addWidget( optimizeButton );

    outputWidget = new QTextEdit();
    outputWidget->setReadOnly( true );

    auto mainLayout = new QVBoxLayout();
    mainLayout->addLayout( inputLayout );
    mainLayout->addWidget( outputWidget );

    this->setLayout( mainLayout );
}

void ParticleSwarmOptimizationWidget::optimizeFunction()
{
    Parser parser( expressionEditWidget->currentText() );
    auto vars = parser.getArguments().keys();

    /// Initialize global best and acceleration.
    const QVector< qreal > acceleration1( vars.size(), 1.0 );
    const QVector< qreal > acceleration2( vars.size(), 1.0 );
    QVector< qreal > globalBestPos( vars.size(), 0.0 );
    for( qint32 i = 0; i < vars.size(); ++i )
    {
        parser.setValue( vars[ i ], globalBestPos[ i ] );
    }
    qreal globalBest = parser.evaluate();

    /// Initialize agents.
    QVector< Agent > agents( N_AGENTS );
    for( auto& agent : agents )
    {
        agent.position = globalBestPos;
        agent.personalBestPos = globalBestPos;
        agent.personalBest = globalBest;
        agent.direction = QVector< qreal >( vars.size() );
        std::generate( agent.direction.begin(), agent.direction.end(),
                       [](){ return QRandomGenerator::global()->generateDouble(); });
    }

    /// Optimize.
    static const qint32 MAX_ITERATIONS = 1000;;
    qint32 iterNo = 0;
    do
    {
        for( auto& agent : agents )
        {
            /// Update position.
            for( qint32 i = 0; i < vars.size(); ++i )
            {
                agent.position[ i ] += agent.direction[ i ];
            }

            /// Compute function value in current position.
            for( qint32 i = 0; i < vars.size(); ++i )
            {
                parser.setValue( vars[ i ], agent.position[ i ] );
            }
            auto val = parser.evaluate();
            if( val < agent.personalBest )
            {
                agent.personalBest = val;
                agent.personalBestPos = agent.position;
                if( val < globalBest )
                {
                    globalBest = val;
                    globalBestPos = agent.position;
                }
            }

            /// Change direction.
            for( qint32 i = 0; i < vars.size(); ++i )
            {
                agent.direction[ i ] +=
                        acceleration1[ i ] * QRandomGenerator::global()->generateDouble() *
                        ( agent.personalBestPos[ i ] - agent.position[ i ] ) +
                        acceleration2[ i ] * QRandomGenerator::global()->generateDouble() *
                        ( globalBestPos[ i ] - agent.position[ i ] );
            }
        }

        auto result = QString( "%1 : best = { ").arg( iterNo );
        for( qint32 i = 0; i < vars.size(); ++i )
        {
            result.append( QString( " %1 " ).arg( globalBestPos[ i ] ) );
        }
        result.append( " } " );
        outputWidget->append( result );
    }
    while( MAX_ITERATIONS > iterNo++ );
}
