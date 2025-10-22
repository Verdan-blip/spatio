#include <LSolidColorView.h>
#include <LView.h>
#include "../include/SpatioTopbar.h"
#include "../include/SpatioOutput.h"
#include "../include/SpatioCompositor.h"

SpatioTopbar::SpatioTopbar(SpatioOutput *output) : spatioOutput(output) {
    view = new LSolidColorView(0.0f, 0.0f, 0.0f, 0.8f, &this->spatioOutput->spatioCompositor->overlayLayer);
}

SpatioTopbar::~SpatioTopbar() {
    destroyThumbnails();
}

void SpatioTopbar::destroyThumbnails() {
    while (!view->children().empty()) {
        delete view->children().back();
    }
}

void SpatioTopbar::copyThumbnailsFromAnotherTopbar() {
    updateGui();
}

void SpatioTopbar::updateGui() {
    this->view->setSize(this->spatioOutput->size().w(), TOPBAR_HEIGHT);
    this->view->setPos(this->spatioOutput->pos());
    this->spatioOutput->repaint();
}
