QT       += core gui statemachine openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat
QMAKE_CXXFLAGS += -std:c++17 /Zc:__cplusplus
QMAKE_CXXFLAGS += /permissive-
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DATA/baseClass/clicklabel.cpp \
    DATA/baseClass/componentobject.cpp \
    DATA/baseClass/dynamicitem.cpp \
    DATA/baseClass/gamedemo.cpp \
    DATA/baseClass/gameobject.cpp \
    DATA/baseClass/gameobjectchilditem.cpp \
    DATA/baseClass/gameobjectitem.cpp \
    DATA/baseClass/instructionobject.cpp \
    DATA/baseClass/map2ditem.cpp \
    DATA/baseClass/mapitem.cpp \
    DATA/baseClass/script.cpp \
    DATA/baseClass/sourcemetadata.cpp \
    DATA/baseClass/systemobject.cpp \
    DATA/baseClass/uiwidget.cpp \
    DATA/constvalue.cpp \
    DATA/demo/motademo.cpp \
    DATA/enginestate.cpp \
    DATA/gameObject/motahero.cpp \
    DATA/gameObject/motamap.cpp \
    DATA/gameObject/motamonster.cpp \
    DATA/instructioncontext.cpp \
    DATA/model/model2dmap.cpp \
    DATA/model/model2dobjectmap.cpp \
    DATA/model/modelproperty.cpp \
    DATA/model/modelshowcharacter.cpp \
    DATA/model/modeltower.cpp \
    DATA/systemstate.cpp \
    EngineCore.cpp \
    EngineMain.cpp \
    TOOL/editTool/editsystem.cpp \
    TOOL/eventTool/eventsystem.cpp \
    TOOL/instructionTool/instructionsystem.cpp \
    TOOL/managerTool/editmanager.cpp \
    TOOL/managerTool/eventmanager.cpp \
    TOOL/managerTool/instructionmanager.cpp \
    TOOL/managerTool/scriptmanager.cpp \
    TOOL/managerTool/sourcemanager.cpp \
    TOOL/managerTool/statemanger.cpp \
    TOOL/managerTool/uimanager.cpp \
    TOOL/scriptTool/scriptsystem.cpp \
    TOOL/sourceTool/jsonparser.cpp \
    TOOL/sourceTool/sourcesystem.cpp \
    TOOL/translateTool/valuetranslator.cpp \
    TOOL/uiTool/uisystem.cpp \
    UI/componentWidget/addgameobjectinfowidget.cpp \
    UI/componentWidget/addsourceinfowidget.cpp \
    UI/componentWidget/addsourcewidget.cpp \
    UI/componentWidget/eventshowwidget.cpp \
    UI/componentWidget/gameobjectdropwidget.cpp \
    UI/componentWidget/gameobjectiteminfowidget.cpp \
    UI/componentWidget/gameobjectitemscriptwidget.cpp \
    UI/componentWidget/gameobjectpropertiesshowwidget.cpp \
    UI/componentWidget/gamescene.cpp \
    UI/componentWidget/gameshowview.cpp \
    UI/componentWidget/inswidget.cpp \
    UI/componentWidget/propertylabelwidget.cpp \
    UI/componentWidget/showlabelwidget.cpp \
    UI/componentWidget/sourcecardviewwidget.cpp \
    UI/componentWidget/sourcecardwidget.cpp \
    UI/componentWidget/sourcetreewidget.cpp \
    UI/componentWidget/statelabel.cpp \
    UI/componentWidget/toolwidget.cpp \
    UI/componentWidget/wheelslidewidget.cpp \
    UI/editWidget/eventeditwidget.cpp \
    UI/editWidget/gameshowwidget.cpp \
    UI/editWidget/propertyeditwidget.cpp \
    UI/editWidget/sourcemanagewidget.cpp \
    main.cpp



HEADERS += \
    DATA/baseClass/clicklabel.h \
    DATA/baseClass/componentobject.h \
    DATA/baseClass/dynamicitem.h \
    DATA/baseClass/gamedemo.h \
    DATA/baseClass/gameobject.h \
    DATA/baseClass/gameobjectchilditem.h \
    DATA/baseClass/gameobjectitem.h \
    DATA/baseClass/instructionobject.h \
    DATA/baseClass/map2ditem.h \
    DATA/baseClass/mapitem.h \
    DATA/baseClass/script.h \
    DATA/baseClass/sourcemetadata.h \
    DATA/baseClass/systemobject.h \
    DATA/baseClass/uiwidget.h \
    DATA/constvalue.h \
    DATA/demo/motademo.h \
    DATA/enginestate.h \
    DATA/gameObject/motahero.h \
    DATA/gameObject/motamap.h \
    DATA/gameObject/motamonster.h \
    DATA/instructioncontext.h \
    DATA/model/model2dmap.h \
    DATA/model/model2dobjectmap.h \
    DATA/model/modelproperty.h \
    DATA/model/modelshowcharacter.h \
    DATA/model/modeltower.h \
    DATA/systemstate.h \
    EngineCore.h \
    EngineMain.h \
    Factory.hpp \
    Registor.hpp \
    TOOL/editTool/editsystem.h \
    TOOL/eventTool/eventsystem.h \
    TOOL/instructionTool/instructionsystem.h \
    TOOL/managerTool/editmanager.h \
    TOOL/managerTool/eventmanager.h \
    TOOL/managerTool/instructionmanager.h \
    TOOL/managerTool/scriptmanager.h \
    TOOL/managerTool/sourcemanager.h \
    TOOL/managerTool/statemanger.h \
    TOOL/managerTool/uimanager.h \
    TOOL/scriptTool/scriptsystem.h \
    TOOL/sourceTool/jsonparser.h \
    TOOL/sourceTool/sourcesystem.h \
    TOOL/template/Factory.hpp \
    TOOL/template/Registor.hpp \
    TOOL/template/ThreadPool.hpp \
    TOOL/translateTool/valuetranslator.h \
    TOOL/uiTool/uisystem.h \
    UI/componentWidget/addgameobjectinfowidget.h \
    UI/componentWidget/addsourceinfowidget.h \
    UI/componentWidget/addsourcewidget.h \
    UI/componentWidget/eventshowwidget.h \
    UI/componentWidget/gameobjectdropwidget.h \
    UI/componentWidget/gameobjectiteminfowidget.h \
    UI/componentWidget/gameobjectitemscriptwidget.h \
    UI/componentWidget/gameobjectpropertiesshowwidget.h \
    UI/componentWidget/gamescene.h \
    UI/componentWidget/gameshowview.h \
    UI/componentWidget/inswidget.h \
    UI/componentWidget/propertylabelwidget.h \
    UI/componentWidget/showlabelwidget.h \
    UI/componentWidget/sourcecardviewwidget.h \
    UI/componentWidget/sourcecardwidget.h \
    UI/componentWidget/sourcetreewidget.h \
    UI/componentWidget/statelabel.h \
    UI/componentWidget/toolwidget.h \
    UI/componentWidget/wheelslidewidget.h \
    UI/editWidget/eventeditwidget.h \
    UI/editWidget/gameshowwidget.h \
    UI/editWidget/propertyeditwidget.h \
    UI/editWidget/sourcemanagewidget.h




FORMS += \
    EngineCore.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc


win32: LIBS += -L$$PWD/RESOURCE/lib/lua/ -llua54

INCLUDEPATH += $$PWD/RESOURCE/lib/lua
DEPENDPATH += $$PWD/RESOURCE/lib/lua
