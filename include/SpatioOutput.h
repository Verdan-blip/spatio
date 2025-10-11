#ifndef SPATIO_OUTPUT_H
#define SPATIO_OUTPUT_H

#include <LOutput.h>

using namespace Louvre;

class SpatioOutput : public LOutput {
    public:
    SpatioOutput(const void *params);

    void initializeGL() override;
    void moveGL() override;
    void resizeGL() override;
    void paintGL() override;
    void uninitializeGL() override;

    private:
    LTexture *wallpaper { nullptr };
};

#endif