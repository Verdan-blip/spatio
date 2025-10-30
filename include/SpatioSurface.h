#ifndef SPATIO_SURFACE_H
#define SPATIO_SURFACE_H

#include <LSurface.h>
#include <LLayerView.h>
#include "SpatioCompositor.h"

using namespace Louvre;

class SpatioSurface : public LSurface {
    public:
    SpatioSurface(LLayerView* layerView, const void *params);

    void roleChanged() override;
    void orderChanged() override;

    LLayerView* layerView = nullptr;
    LSurfaceView *view = nullptr;
};

#endif