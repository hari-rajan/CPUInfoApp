#ifndef CCPUINFO
#define CCPUINFO

#include <QString>
#include <QVector>
#include <QQueue>
#include <QPair>

#define ERRORCODE_OK    0
#define ERRORCODE_ERR   -1

class CCPUInfoServer
{
public:
    CCPUInfoServer();

    /**
     * @brief getCoreCount: Method call to fetch number of cores (includes hyper-threading)
     * @return uint. Count.
     */
    uint getCoreCount();

    /**
     * @brief requestMap Method call to request data list (key value pair) for single core properties
     * @param index Index of core requested
     * @return QQueue of key value pairs
     */
    QQueue<QPair<QString, QString>> requestMap(int index);

protected:
    virtual ~CCPUInfoServer();

private:
    QVector<QQueue<QPair<QString, QString>>>   mCpuInfoHash;

    int initData();


};

#endif // CCPUINFO

