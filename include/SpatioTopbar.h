#ifndef SPATIO_TOPBAR_H
#define SPATIO_TOPBAR_H

#include <LSolidColorView.h>
#include <LObject.h>

#define TOPBAR_HEIGHT 32

class SpatioOutput;

using namespace Louvre;

class SpatioTopbar : public LObject {
    public:
    SpatioTopbar(SpatioOutput *output);
    ~SpatioTopbar();

    void destroyThumbnails();
    void copyThumbnailsFromAnotherTopbar();
    void updateGui();

    SpatioOutput *spatioOutput;
    LSolidColorView *view;
};

#endif