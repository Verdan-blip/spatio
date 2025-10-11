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
#include "../include/SpatioOutput.h"

SpatioOutput::SpatioOutput(const void *params) : LOutput(params) { };

void SpatioOutput::initializeGL() {
    wallpaper = LOpenGL::loadTexture(compositor()->defaultAssetsPath() / "wallpaper.png");
    if (!wallpaper) {
        LLog::error("[SpatioOutput] Failed to load wallpaper");
    }

    repaint();
}

void SpatioOutput::moveGL() {
    repaint();
}

void SpatioOutput::resizeGL() {
    repaint();
}

void SpatioOutput::paintGL() {
    LPainter *p = painter();
    LRect r = rect();

    LPainter::TextureParams params;
    LRect surfaceRect;

    params.texture = wallpaper;
    params.srcRect = LRect(0, 0, wallpaper->sizeB().w(), wallpaper->sizeB().h());
    params.pos = LPoint(r.x(), r.y());
    params.dstSize = LSize(r.w(), r.h());

    p->bindTextureMode(params);
    p->drawRect(LRect(0, 0, size().w(), size().h()));


    for (LSurface *surface : compositor()->surfaces()) {
        if (surface->mapped() || surface->minimized() || surface->cursorRole()) {
            if (surface->cursorRole()) {
                surface->requestNextFrame();
            }
            continue;
        }

        surfaceRect = LRect(surface->rolePos(), surface->size());

        for (LOutput *output : compositor()->outputs()) {
            if (output->rect().intersects(surfaceRect)) {
                surface->sendOutputEnterEvent(output);
            } else {
                surface->sendOutputLeaveEvent(output);
            }
        }

        LPainter::TextureParams surfaceParams;
        surfaceParams.texture = surface->texture();
        surfaceParams.pos = surfaceRect.pos();
        surfaceParams.srcRect = surface->srcRect();
        surfaceParams.dstSize = surface->size();
        surfaceParams.srcTransform = surface->bufferTransform();
        surfaceParams.srcScale = (Float32) surface->bufferScale();

        p->bindTextureMode(surfaceParams);
        p->drawRect(surfaceRect);

        surface->requestNextFrame();

        if (!cursor()->hasHardwareSupport(this)) {
            LPainter::TextureParams cursorParams;
            cursorParams.pos = cursor()->pos();
            cursorParams.srcRect = cursor()->rect();
            cursorParams.dstSize = r.size();
            p->bindTextureMode(cursorParams);
            p->drawRect(LRect(0, 0, size().w(), size().h()));
        }
    }
}

void SpatioOutput::uninitializeGL() {
    if (wallpaper) {
        delete wallpaper;
    }
}