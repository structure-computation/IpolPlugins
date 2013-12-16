#ifndef IPOLTVDECONVOLUTIONUPDATER_H
#define IPOLTVDECONVOLUTIONUPDATER_H

#include <Soca/Updater.h>
class SodaClient;
//class QDataStream;

/**
*/
class IpolTVDeconvolutionUpdater : public Updater {
protected:
    bool run( MP mp );
    virtual QString type() const { return "IpolLSDItem"; }
    
public:
    SodaClient *sc;
};

#endif // IPOLTVDECONVOLUTIONUPDATER_H
