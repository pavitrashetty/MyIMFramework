#ifndef __MOVEMENT__
#define __MOVEMENT__

#include "multi_frame_manager.hpp"
#include "utils.hpp"
#include "transformer.hpp"

/* MOVEMENT CLASS:
    Create a series of frames showing a movement
    Given= Background (Image or FM)
    Input= 1 image or FM
    Output= 1 FM
*/

// TODO: overlay input is not single image but a FM. Could introduce a set_moving_object(Image / FM) method and implement it.


class Movement {

  Frame_Manager *bkgnd_FM;
  Image *overlay_img;
  Frame_Manager *overlay_FM;

  public:

    Movement ();
    void set_background (Image *img);
    void set_background (Frame_Manager *fm);
    void set_background (char *res, char *color);

    void set_moving_object (Image *img);
    void set_moving_object (Frame_Manager *fm);
    void set_moving_object (char *res, char *color);

    Frame_Manager *straight_line(Resolution *res, Position *src, Position *dest, int duration);
    Frame_Manager *circle(float radius, Position *center);

    Frame_Manager *draw_line(Position *src, Position *dest, int duration);
};

#endif