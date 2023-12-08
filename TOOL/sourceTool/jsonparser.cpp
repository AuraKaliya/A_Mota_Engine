#include "jsonparser.h"


JsonParser* JsonParser::m_instance=nullptr;
JsonParser *JsonParser::getInstance()
{
    if(m_instance== nullptr)
    {
        m_instance=new JsonParser;
    }
    return m_instance;
}

JsonParser::JsonParser()
{

}
