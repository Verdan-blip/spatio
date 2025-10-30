#include <LOutput.h>
#include <LPainter.h>
#include <LTexture.h>
#include <LOpenGL.h>
#include <LLog.h>
#include <LSeat.h>
#include <LCompositor.h>
#include <LRect.h>
#include <LDND.h>
#include <LCursor.h>
#include <LRegion.h>
#include <LLog.h>
#include <iostream>
#include "../include/SpatioCompositor.h"
#include "../include/SpatioOutput.h"
#include "../include/SpatioTopbar.h"

LRect scaleToRect(const LSize &target, const LSize &dest);


SpatioOutput::SpatioOutput(const void *params) : LOutput(params) { 
    this->spatioCompositor = (SpatioCompositor*) compositor();
    this->topbar = new SpatioTopbar(this);

    this->wallpaperView = new LTextureView(nullptr, &spatioCompositor->backgroundLayer);

    const LRegion emptyRegion;
    this->wallpaperView->setTranslucentRegion(&emptyRegion);
};

void SpatioOutput::initializeGL() {
    updateWallpaper();

    topbar->copyThumbnailsFromAnotherTopbar();
    spatioCompositor->scene.handleInitializeGL(this);
    repaint();
}

void SpatioOutput::moveGL() {
    topbar->updateGui();
    spatioCompositor->scene.handleMoveGL(this);
    repaint();
}

void SpatioOutput::resizeGL() {
    topbar->updateGui();
    spatioCompositor->placeOutputsVertically();
    updateWallpaper();

    spatioCompositor->scene.handleResizeGL(this);
    repaint();
}

void SpatioOutput::paintGL() {
    spatioCompositor->softwareCursor.setTexture(cursor()->texture());
    spatioCompositor->softwareCursor.setPos(cursor()->pos());
    spatioCompositor->softwareCursor.setSrcRect(LRectF(0, 0, 32, 32));
    spatioCompositor->softwareCursor.setDstSize(cursor()->rect().size());
    spatioCompositor->softwareCursor.setVisible(cursor()->visible());

    spatioCompositor->scene.handlePaintGL(this);
}

void SpatioOutput::uninitializeGL() {
    if (wallpaperView->texture()) {
        delete wallpaperView->texture();
    }
    spatioCompositor->scene.handleUninitializeGL(this);

    topbar->destroyThumbnails();
}

void SpatioOutput::updateWallpaper() {
    if (wallpaperView->texture()) {
        if (wallpaperView->texture()->sizeB() == this->sizeB()) {
            wallpaperView->setBufferScale(this->scale());
            wallpaperView->setPos(this->pos());
            return;
        } 
        
        delete wallpaperView->texture();
    }

    LTexture *originalWallpaper = LOpenGL::loadTexture(compositor()->defaultAssetsPath() / "wallpaper.png");

    if (!originalWallpaper) {
        LLog::error("[spatio] Failed to load wallpaper.");
        return;
    }

    const LSize &originalSize = originalWallpaper->sizeB();
    LRect outputRect = scaleToRect(originalSize, this->sizeB());

    LTexture *scaledTexture = originalWallpaper->copy(this->sizeB(), outputRect);

    wallpaperView->setTexture(scaledTexture);
    wallpaperView->setBufferScale(this->scale());

    delete originalWallpaper;
    wallpaperView->setPos(this->pos());
}

LRect scaleToRect(const LSize &originalSize, const LSize &outputSize) {
    float originalRatio = (float)originalSize.w() / originalSize.h();
    float outputRatio = (float)outputSize.w() / outputSize.h();
    
    LRect srcRect;
    
    if (originalRatio > outputRatio) {
        float height = originalSize.h();
        float width = height * outputRatio;
        srcRect.setX((originalSize.w() - width) / 2);
        srcRect.setY(0);
        srcRect.setW(width);
        srcRect.setH(height);
    } else {
        float width = originalSize.w();
        float height = width / outputRatio;
        srcRect.setX(0);
        srcRect.setY((originalSize.h() - height) / 2);
        srcRect.setW(width);
        srcRect.setH(height);
    }
    
    return srcRect;
}