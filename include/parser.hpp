#ifndef PARSER_HPP
#define PARSER_HPP

#include <QHash>
#include <QString>
#include <QPair>

#include <muParser.h>

class Parser
{

public:
    Parser() = delete;
    explicit Parser( const QString& expression );
    ~Parser() = default;

    qreal evaluate();

    const QHash< QString, qreal >& getArguments() const;
    void setValue( const QString& name, const qreal val );

protected:
    QPair< qint32, qint32 > readVar( const QString& source, qint32 pos );

private:
    QHash< QString, qreal > args;
    mu::Parser parser;

    static const char* ALLOWED_VAR_SYMBOLS;
};

#endif /// PARSER_HPP
