#include <LOutput.h>
#include <LSeat.h>
#include <LKeyboard.h>
#include <LFramebuffer.h>
#include <LCompositor.h>
#include <LSceneView.h>
#include <LColor.h>
#include "../include/SpatioOutput.h"
#include "../include/SpatioSurface.h"
#include "../include/SpatioCompositor.h"

SpatioCompositor::SpatioCompositor() {
    LRGBAF color = {
        .r = 0.3f,
        .g = 0.2f,
        .b = 0.7f,
        .a = 1.f
    };
    this->scene.mainView()->setClearColor(color);

    //softwareCursor.enableDstSize(true);
};

void SpatioCompositor::initialized() {
    seat()->keyboard()->setKeymap(nullptr, nullptr, "latam", nullptr);

    Int32 totalWidth { 0 };

    for (LOutput *output : seat()->outputs()) {
        float scale = output->dpi() >= 200 ? 2.0f : 1.0f;
        output->setScale(scale);
        output->setTransform(LTransform::Normal);

        output->setPos(LPoint(totalWidth, 0));
        totalWidth += output->size().w();

        addOutput(output);
        output->repaint();
    }
}

LFactoryObject* SpatioCompositor::createObjectRequest(LFactoryObject::Type objectType, const void *params) {
    switch (objectType) {
        case LFactoryObject::Type::LOutput:
            return new SpatioOutput(params);
        case LFactoryObject::Type::LSurface:
            return new SpatioSurface(&surfacesLayer, params);
        default:
            return LCompositor::createObjectRequest(objectType, params);
    }
}

void SpatioCompositor::placeOutputsVertically() {
    Int32 totalWidth = 0;
    for (LOutput *output : outputs()) {
        output->setPos(LPoint(totalWidth, 0));
        totalWidth += output->size().w();
    }
}
