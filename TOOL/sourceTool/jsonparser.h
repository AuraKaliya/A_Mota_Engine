#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QString>


static const QString RESOURCEDIR="./RESOURCE";

class JsonParser
{
public:
    static JsonParser* getInstance();
private:
    static JsonParser*m_instance;
    JsonParser();
    QString m_path;

};

#endif // JSONPARSER_H
