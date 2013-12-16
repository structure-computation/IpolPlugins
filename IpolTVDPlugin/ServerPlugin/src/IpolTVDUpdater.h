#ifndef IPOLTVDUPDATER_H
#define IPOLTVDUPDATER_H

#include <Soca/Updater.h>
class SodaClient;
//class QDataStream;

/**
*/
class IpolTVDUpdater : public Updater {
protected:
    bool run( MP mp );
    virtual QString type() const { return "IpolTVDItem"; }
    
public:
    SodaClient *sc;
};

#endif // IPOLTVDUPDATER_H
