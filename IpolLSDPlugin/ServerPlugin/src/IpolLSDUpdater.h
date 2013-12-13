#ifndef IPOLLSDUPDATER_H
#define IPOLLSDUPDATER_H

#include <Soca/Updater.h>
class SodaClient;
//class QDataStream;

/**
*/
class IpolLSDUpdater : public Updater {
protected:
    bool run( MP mp );
    virtual QString type() const { return "IpolLSDItem"; }
    
public:
    SodaClient *sc;
};

#endif // IPOLLSDUPDATER_H
