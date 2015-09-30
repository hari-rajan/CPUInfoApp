/***
 * This class fetches data from /proc/cpuinfo, parses, and
 * populates internal data structure. Class simply serves up data.
 *
 * Author: Hari Rajan
 *
 */


#include "src/ccpuinfoserver.h"
#include <QDebug>
#include <QFile>

#define CPUPROC_FILE "/proc/cpuinfo"
#define LINE_SPLIT_MARKER ":"
#define PROCESSOR_SPLIT_MARKER "\n"


CCPUInfoServer::CCPUInfoServer()
{
    initData();
}

CCPUInfoServer::~CCPUInfoServer()
{
    mCpuInfoHash.clear();
}

// Reads cpu info, parses, and populates data structure
int CCPUInfoServer::initData()
{
    FILE * cpuinfo = fopen(CPUPROC_FILE, "rb");
    char *arg = 0;
    size_t size = 0;

    QQueue<QPair<QString, QString>> datahash;
    while(getline(&arg, &size, cpuinfo) != -1)
    {
       QString str (arg);
       QStringList keyval;
       keyval = str.split (LINE_SPLIT_MARKER);

       if (keyval[0] != PROCESSOR_SPLIT_MARKER)
       {
           keyval[0] = keyval[0].simplified();
           keyval[1] = keyval[1].simplified();
       }

       if (keyval[0] == PROCESSOR_SPLIT_MARKER)
       {
           mCpuInfoHash.push_back(datahash);
           datahash.clear();
       }
       else
       {
           QPair<QString,QString> pair (keyval[0], keyval[1]);
           datahash.push_back(pair);
       }
    }

    free(arg);
    fclose(cpuinfo);
    return 0;
}

// Returns data queue for requested core index
QQueue<QPair<QString, QString>> CCPUInfoServer::requestMap(int index)
{
    //qDebug() << __PRETTY_FUNCTION__ << " - " + index;
    if (index < 0 ||
        index > mCpuInfoHash.length())
    {
        QPair<QString, QString> pair;
        QQueue<QPair<QString, QString>> queue;
        queue.push_back(pair);
        return queue;
    }

    return mCpuInfoHash[index];
}

// Returns number of cores (including hyper threads)
uint CCPUInfoServer::getCoreCount()
{
    return mCpuInfoHash.length();
}
