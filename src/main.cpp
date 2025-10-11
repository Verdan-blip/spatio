#include <LLauncher.h>
#include <LCompositor.h>
#include <LLog.h>
#include "../include/SpatioCompositor.h"

using namespace Louvre;

int main() {
    setenv("LOUVRE_DEBUG", "4", 0);

    LLauncher::startDaemon();

    SpatioCompositor compositor;

    if (!compositor.start()) {
        LLog::fatal("[louvre-example] Failed to start compositor.");
        return 1;
    }

    while (compositor.state() != LCompositor::Uninitialized) {
        compositor.processLoop(-1);
    }

    return 0;
}