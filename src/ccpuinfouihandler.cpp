/**
 * This class handles UI for the application. Includes initial screen,
 * button handling, UI updating, fetching data from server.
 *
 * Author: Hari Rajan
 * Date: Sept 29, 2015
 *
 *
 */


#include <QDebug>
#include "ccpuinfouihandler.h"

#define ELEMENTNAME "listelement"
#define VALUELABEL  "valuelabel"
#define MODELLABEL  "cpuNameHeading"
#define CORESLABEL  "coresHeading"
#define MODELNAME   "model name"
#define CORESNAME   "cpu cores"
#define BTNPREV     "prevButton"
#define BTNNEXT     "nextButton"
#define LOWERBOUND  1

CCPUInfoUIHandler::CCPUInfoUIHandler(QObject *parent) : QObject(parent)
, mIndex(LOWERBOUND)
, mParent(parent)
{
    mCPUInfoServer = new CCPUInfoServer();
    initUI();
}

CCPUInfoUIHandler::~CCPUInfoUIHandler()
{
}

void CCPUInfoUIHandler::initUI()
{
    QObject::connect(mParent, SIGNAL(btnClick(QString)), this, SLOT(onBtnClick(QString)));

    //initial screen...
    updateScreen ();
}


void CCPUInfoUIHandler::updateScreen()
{
    //qDebug() << __PRETTY_FUNCTION__ << " " << mIndex;

    //mIndex is 1 based index to match to UI elements. Hence subtracting 1 before requesting data.
    QQueue<QPair<QString, QString>> data = mCPUInfoServer->requestMap((mIndex-1));

    // handle empty data
    if (data.isEmpty() == true)
    {
        handleNoData(true);
        qWarning() << "no data";
        return;
    }

    handleNoData(false);

    //go through the data list and populate.
    //handles button states for end of page scenarios
    for (int i = 0; i < data.length(); ++i)
    {
       QPair<QString, QString> pair = data[i];
       QString keystr = ELEMENTNAME + QString::number(i);
       QObject* keylbl = mParent->findChild<QObject*>(keystr);

       if (keylbl)
       {
           //qDebug() << "setting " << pair.first;
           keylbl->setProperty("key", pair.first);
           keylbl->setProperty("value", pair.second);
       }

       if (pair.first == MODELNAME)
       {
           QObject* modelname = mParent->findChild<QObject*>(MODELLABEL);
           if (modelname)
               modelname->setProperty("text", pair.second);
       }

       QVariant returnedValue;
       QMetaObject::invokeMethod(mParent, "updateList",
               Q_RETURN_ARG(QVariant, returnedValue),
               Q_ARG(QVariant, pair.first),
               Q_ARG(QVariant, pair.second),
               Q_ARG(QVariant, i));
    }

    //Check Index bounds. Handles 1 core or more
    if (mIndex == LOWERBOUND)
    {
        showHideButton(QString("left"), false);
    }

    if (mIndex == mCPUInfoServer->getCoreCount())
    {
        showHideButton("right", false);
    }

    if (mIndex > LOWERBOUND && mIndex < mCPUInfoServer->getCoreCount())
    {
        showHideButton("left", true);
        showHideButton("right", true);
    }
}

//callback from qml signal.
void CCPUInfoUIHandler::onBtnClick (QString msg)
{
    //qDebug() << msg;

    if (msg == "left")
    {
        mIndex--;
    }
    else if (msg == "right")
    {
        mIndex++;
    }

    uint count = mCPUInfoServer->getCoreCount();
    if (mIndex >= count) mIndex = count;

    updateScreen();
}

//button state handler
void CCPUInfoUIHandler::showHideButton(QString type, bool bShowHide)
{
    QString btntype;
    if (type == "left")
    {
        btntype = BTNPREV;
    }
    else if (type == "right")
    {
        btntype = BTNNEXT;
    }
    else
    {
        qWarning() << "showHideButton(). Incorrect type " << type;
        return;
    }

    QVariant returnedValue;
    QMetaObject::invokeMethod(mParent, "setButtonState",
            Q_RETURN_ARG(QVariant, returnedValue),
            Q_ARG(QVariant, btntype),
            Q_ARG(QVariant, bShowHide));
}

//no data handler. Enables no data text and hides listview or vice-versa
void CCPUInfoUIHandler::handleNoData(bool bNoData)
{
    QObject* noData = mParent->findChild<QObject*>("noData");
    QObject* textContainer = mParent->findChild<QObject*>("scrollview");
    QObject* header = mParent->findChild<QObject*>("cpuNameHeading");

    if (textContainer)
    {
        textContainer->setProperty("visible", !bNoData);
    }

    if (noData)
    {
        noData->setProperty("visible", bNoData);
    }

    if (header)
    {
        header->setProperty("visible", !bNoData);
    }

    showHideButton("left", !bNoData);
    showHideButton("right", !bNoData);
}

