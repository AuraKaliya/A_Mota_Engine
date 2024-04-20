#ifndef ENGINESTYLE_H
#define ENGINESTYLE_H
#include<QFont>
#include <QString>

class EngineStyle
{
public:
    static EngineStyle* getInstance(QString styleName="Default");

    QFont thirdTitleFont() const;

    QFont secondTitleFont() const;

    QFont firstTitleFont() const;

    QString firstComboBoxStyle() const;

    QString editLabelStyle() const;

    QString firstButtonStyle() const;

    QFont firstTextFont() const;

    QString styleName() const;

    void setStyleName(const QString &newStyleName);

private:
    QString m_styleName;
    QFont m_firstTitleFont;
    QFont m_secondTitleFont;
    QFont m_thirdTitleFont;
    QFont m_firstTextFont;

    QString m_firstComboBoxStyle;

    QString m_editLabelStyle;

    QString m_firstButtonStyle;

    static EngineStyle * m_instance;
    EngineStyle(QString styleName="Default");
};

#endif // ENGINESTYLE_H
