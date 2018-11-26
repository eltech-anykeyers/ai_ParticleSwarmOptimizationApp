#include <parser.hpp>

const char* Parser::ALLOWED_VAR_SYMBOLS = "0123456789_@"
                                          "abcdefghijklmnopqrstuvwxyz"
                                          "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

Parser::Parser( const QString& expression )
{
    parser.DefineNameChars( ALLOWED_VAR_SYMBOLS );
    parser.SetExpr( expression.toStdString() );

    QPair< qint32, qint32 > var = readVar( expression, 0 );
    while( var.first > -1 )
    {
        QString varStr = expression.mid( var.first, var.second - var.first );
        args[ varStr ] = 0.0;
        parser.DefineVar( varStr.toStdString(), &args[ varStr ] );
        var = readVar( expression, var.second );
    }
}

qreal Parser::evaluate()
{
    return parser.Eval();
}

const QHash< QString, qreal >& Parser::getArguments() const
{
    return args;
}

void Parser::setValue( const QString& name, const qreal val )
{
    args[ name ] = val;
}

QPair< qint32, qint32 > Parser::readVar( const QString& source, qint32 pos )
{
    auto from = source.indexOf( '@', pos );
    if( from == -1 ) return qMakePair( -1, -1 );

    const QString allowedVarSymbols( ALLOWED_VAR_SYMBOLS );

    qint32 to;
    for( to = from + 1; to < source.size(); ++to )
    {
        if( !allowedVarSymbols.contains( source[ to ] ) ) break;
    }

    if( to - from > 1 ) return qMakePair( from, to );
    else return qMakePair( -1, -1 );
}
