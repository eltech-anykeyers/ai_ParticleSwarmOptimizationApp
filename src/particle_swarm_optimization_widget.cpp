#include <particle_swarm_optimization_widget.hpp>
#include <parser.hpp>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

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
    auto inputString = expressionEditWidget->currentText();
    Parser p( inputString );

    for( qreal val = 0.0; val < 100.0; ++val )
    {
        for( const auto& varName : p.getArguments().keys() )
        {
            p.setValue( varName, val );
        }
        outputWidget->append( QString( "%1 : %2" )
                                  .arg( val )
                                  .arg( p.evaluate() ) );
    }
}
