#ifndef CCPUINFOUIHANDLER_H
#define CCPUINFOUIHANDLER_H

#include <QObject>
#include "ccpuinfoserver.h"

class CCPUInfoUIHandler : public QObject
{
    Q_OBJECT
public:
    explicit CCPUInfoUIHandler(QObject *parent = 0);

protected:
    virtual ~CCPUInfoUIHandler();

private:
    CCPUInfoServer *mCPUInfoServer;
    uint  mIndex;
    QObject* mParent;

    void initUI();
    void updateScreen();
    void showHideButton(QString type, bool bShowHide);
    void handleNoData(bool bNoData);

signals:

public slots:
    void onBtnClick(QString msg);
};

#endif // CCPUINFOUIHANDLER_H
