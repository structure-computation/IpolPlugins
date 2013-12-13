#ifndef IPOLACEUPDATER_H
#define IPOLACEUPDATER_H

#include <Soca/Updater.h>
class SodaClient;
//class QDataStream;

/**
*/
class IpolSCAUpdater : public Updater {
protected:
    bool run( MP mp );
    virtual QString type() const { return "IpolSCAItem"; }
    
public:
    SodaClient *sc;
};

#endif // IPOLACEUPDATER_H
