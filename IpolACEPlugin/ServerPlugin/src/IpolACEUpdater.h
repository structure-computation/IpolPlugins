#ifndef IPOLACEUPDATER_H
#define IPOLACEUPDATER_H

#include <Soca/Updater.h>
class SodaClient;
//class QDataStream;

/**
*/
class IpolACEUpdater : public Updater {
protected:
    bool run( MP mp );
    virtual QString type() const { return "IpolACEItem"; }
    
public:
    SodaClient *sc;
};

#endif // IPOLACEUPDATER_H
