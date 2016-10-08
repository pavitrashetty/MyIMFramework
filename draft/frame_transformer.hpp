#ifndef __FRAME_TRANSFORMER_INCLDUED__
#define __FRAME_TRANSFORMER_INCLDUED__

#include "frame_manager.hpp"
#include "transformer.hpp"
#include "utils.hpp"

class Frame_Transformer {

  public:

    Frame_Transformer();
    // Create image template video
    Frame_Manager *copy_frames(Image *img, int duration, float fps);
    // For all frames, does affine transformation using angle range
    bool affine_transform(Frame_Manager *fm, float start_angle, float end_angle, float step);
    // Zoom in / out effect
    static const int ZOOM_IN = 1;
    static const int ZOOM_OUT = 2;
    Frame_Manager *zoomer(Frame_Manager *in_fm, Resolution *start_res, Resolution *end_res, Position *start, Position *end, int duration);
    Frame_Manager *enlarge(Image *img, Resolution *start_res, Resolution *end_res, int duration);
};

#endif