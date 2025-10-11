#ifndef SPATIO_COMPOSITOR
#define SPATIO_COMPOSITOR

#include <LCompositor.h>
#include <LScene.h>
#include <LLayerView.h>
#include <LTextureView.h>

using namespace Louvre;

class SpatioCompositor : public LCompositor {
    public:
    SpatioCompositor();
    
    void initialized() override;
    
    LFactoryObject* createObjectRequest(LFactoryObject::Type objectType, const void *params) override;
};

#endif