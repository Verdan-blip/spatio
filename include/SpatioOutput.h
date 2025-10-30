#ifndef SPATIO_OUTPUT_H
#define SPATIO_OUTPUT_H

#include <LOutput.h>
#include <LTextureView.h>
#include <LLayerView.h>
#include "../include/SpatioCompositor.h"

using namespace Louvre;

class SpatioTopbar;

class SpatioOutput : public LOutput {
    public:
    SpatioOutput(const void *params);

    void initializeGL() override;
    void moveGL() override;
    void resizeGL() override;
    void paintGL() override;
    void uninitializeGL() override;

    //Extensions
    SpatioCompositor *spatioCompositor { nullptr };
    SpatioTopbar *topbar { nullptr };

    private:
    void updateWallpaper();
    LTextureView* wallpaperView;
};

#endif