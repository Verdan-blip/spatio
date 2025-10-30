#include <LSurfaceView.h>
#include <LCompositor.h>
#include <LLayerView.h>
#include "../include/SpatioSurface.h"

SpatioSurface::SpatioSurface(LLayerView* layerView, const void *params) : LSurface(params), layerView(layerView) {
    view = new LSurfaceView((LSurface*) this, layerView);
    layerView->enableParentOffset(false);
}

void SpatioSurface::roleChanged() {
    if (cursorRole()) {
        view->setVisible(false);
    } else if (dndIcon()) {
        view->setParent(layerView);
        view->insertAfter(nullptr);
        setPos(cursor()->pos());
    }
}

void SpatioSurface::orderChanged() {
    SpatioSurface *prev = (SpatioSurface*) prevSurface();

    while (prev && prev->view->parent() != view->parent()) {
        prev = (SpatioSurface*) prev->prevSurface();
    }

    if (prev) {
        view->insertAfter(prev->view);
    } else {
        view->insertAfter(nullptr);
    }
}