#ifndef VALUETRANSLATOR_H
#define VALUETRANSLATOR_H

#include <QObject>
#include <QVariant>
#include <QString>
#include <QMap>
#include <QDebug>
using func=void(*)(const QString&,QVariant& ,QObject*);

class ValueTranslator
{

public:
    static ValueTranslator* getInstance();

    static void translateToInt(const QString& str,QVariant& var,QObject*obj);
    static void translateToStr(const QString& str,QVariant& var,QObject*obj);
    static void translateToDouble(const QString& str,QVariant& var,QObject*obj);
    static void translateToBool(const QString& str,QVariant& var,QObject*obj);

    void translate(const QString& str,const QString& type,QObject*obj);


private:
    static ValueTranslator* m_instance;
    explicit ValueTranslator();
    QVariant m_var;
    QMap<QString,func> m_dictionary;
    static QMap<QString,QString>m_propertiesDictionary;
};

#endif // VALUETRANSLATOR_H
