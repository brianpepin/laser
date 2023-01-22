#pragma once

//
// All UI is displayed through views. There is always one main
// view and one overlay view. The overlay view is always drawn
// last.
//
class View
{
public:
    //
    // Called when a view is about to become the active view.
    // A previous view can be passed if there is
    // a back stack.  Previous view can be null.
    //
    virtual void start(View* previousView) = 0;

    //
    // Called when this view is about to be replaced with another.
    //
    virtual void stop() = 0;

    //
    // Called in the render loop once a frame tick. This
    // can process any input or do other work. If the
    // display needs to be redrawn this should return true.
    //
    virtual bool tick(View **newView) = 0;

    //
    // Called to render the view if update returned true.
    //
    virtual void render() = 0;
};
