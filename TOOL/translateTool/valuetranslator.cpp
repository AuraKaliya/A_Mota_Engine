#include "valuetranslator.h"

ValueTranslator* ValueTranslator::m_instance=nullptr;
QMap<QString,QString>ValueTranslator::m_propertiesDictionary={};
ValueTranslator *ValueTranslator::getInstance()
{
    if(m_instance==nullptr)
    {
        m_instance=new ValueTranslator;
    }
    return m_instance;
}

void ValueTranslator::translateToInt(const QString &str, QVariant &var, QObject *obj)
{
    obj->setProperty(str.toStdString().c_str(),var.toInt());
    m_propertiesDictionary.insert(str,QString("int"));
}

void ValueTranslator::translateToStr(const QString& str,QVariant &var, QObject *obj)
{
    obj->setProperty(str.toStdString().c_str(),var.toString());
    m_propertiesDictionary.insert(str,QString("QString"));
}

void ValueTranslator::translateToDouble(const QString& str,QVariant &var, QObject *obj)
{
    obj->setProperty(str.toStdString().c_str(),var.toDouble());
    m_propertiesDictionary.insert(str,QString("double"));
}

void ValueTranslator::translateToBool(const QString& str,QVariant &var, QObject *obj)
{
    obj->setProperty(str.toStdString().c_str(),var.toBool());
    m_propertiesDictionary.insert(str,QString("bool"));
}

void ValueTranslator::translate(const QString& str,const QString& type,QObject*obj)
{

    auto it=m_dictionary.find(type);
    if(it == m_dictionary.end()) it =m_dictionary.find("default");
    qDebug()<<it.key();
    it.value()(str,m_var,obj);

}



ValueTranslator::ValueTranslator()
{
    m_var.setValue(0);
    m_dictionary.insert("int",translateToInt);
    m_dictionary.insert("QString",translateToStr);
    m_dictionary.insert("double",translateToDouble);
    m_dictionary.insert("bool",translateToBool);
    m_dictionary.insert("default",translateToStr);

}
