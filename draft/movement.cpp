#include "movement.hpp"

Movement::Movement() {
  bkgnd_FM = NULL;
  overlay_img = NULL;
  overlay_FM = NULL;
}

void Movement::set_background (Image *img) {
  bkgnd_FM = NULL;
  bkgnd_FM = new Frame_Manager();
  Image *bkgnd_img = new Image(*img);
  bkgnd_FM->add_frame(bkgnd_img);
}

void Movement::set_background (Frame_Manager *fm) {
  bkgnd_FM = fm;
}

void Movement::set_background (char *res, char *color) {
  bkgnd_FM = new Frame_Manager();
  bkgnd_FM->add_frame(new Image(res, color));
}

void Movement::set_moving_object (Image *img) {
  overlay_img = img;
}

void Movement::set_moving_object (Frame_Manager *fm) {
  overlay_FM = fm;
}

void Movement::set_moving_object (char *res, char *color) {
  overlay_img = new Image(res, color);
}



Frame_Manager *Movement::straight_line(Resolution *res, Position *src, Position *dest, int duration) {

  Frame_Manager *ofm = new Frame_Manager();
  Multiframe_Manager *mfm =  new Multiframe_Manager(bkgnd_FM);
  std::list<Image*>::iterator frame_iter = bkgnd_FM->begin();
  Geometry *new_geom = new Geometry((*frame_iter)->baseColumns(), (*frame_iter)->baseRows());
  Image *transparent_base = new Image (*new_geom,"white");
  transparent_base->opacity(TransparentOpacity);

  int total_frames = duration*30;         //Duh!!!
  int x_offset = floor((dest->get_x() - src->get_x()) / total_frames);
  int y_offset = floor((dest->get_y() - src->get_y()) / total_frames);

  if (x_offset == 0 && y_offset == 0) {
    cout<<"ERROR: Incorrect positions given: empty FM"<<endl;
    return NULL;
  }

  int i, j, flag = 0;
  if(x_offset == 0 || y_offset == 0)
    flag++;

  for (i = src->get_x(), j = src->get_y() ;; i=i+x_offset, j=j+y_offset) {

    if (src->get_x() <= dest->get_x() && i > dest->get_x())
      flag++;
    if (src->get_x() >= dest->get_x() && i < dest->get_x())
      flag++;
    if (src->get_y() <= dest->get_y() && j > dest->get_y())
      flag++;
    if (src->get_y() >= dest->get_y() && j < dest->get_y())
      flag++;
    if (flag == 2)
      break;

    new_geom = new Geometry (0, 0, i, j);
    Transformer *trans = new Transformer();
    Image *base = new Image(*transparent_base);

    Image *over;
    if (overlay_FM != NULL)
      frame_iter = overlay_FM->begin();


    if (overlay_img != NULL) {
      over = overlay_img;
    } else
    if (overlay_FM != NULL) {
      over = *frame_iter;
      ++frame_iter;
      if (frame_iter == overlay_FM->end())
        frame_iter = overlay_FM->begin();
    } else {
      cout <<"I cannot move NULL around."<<endl;
      return NULL;
    }

    if (res != NULL) {
      over->resize(Geometry( res->get_w(), res->get_h() ));
    }

    trans->composite (base, over, "simple_overlay", new_geom);
    ofm->add_frame(base);
  }

  mfm->add_frame_manager(ofm);
  mfm->composite_frames ("simple_overlay", NULL, mfm->REPEAT_ALL);
  // delete frames in ofm;
  // delete mfm, frame_iter, new_geom, transparent_base;
  return bkgnd_FM;
}

Frame_Manager * Movement::circle(float radius, Position *center) {
  Frame_Manager *fm = new Frame_Manager();
  return fm;
}

Frame_Manager *Movement::draw_line(Position *src, Position *dest, int duration) {

  Frame_Manager *ofm = new Frame_Manager();
  Multiframe_Manager *mfm =  new Multiframe_Manager(bkgnd_FM);
  std::list<Image*>::iterator frame_iter = bkgnd_FM->begin();
  Geometry *new_geom = new Geometry((*frame_iter)->baseColumns(), (*frame_iter)->baseRows());
  Image *transparent_base = new Image (*new_geom,"white");
  transparent_base->opacity(TransparentOpacity);
  Image *prev_frame = transparent_base;

  int total_frames = duration*30;

  int x_offset = floor((dest->get_x() - src->get_x()) / total_frames);
  int y_offset = floor((dest->get_y() - src->get_y()) / total_frames);

  if (x_offset == 0 && y_offset == 0) {
    cout<<"ERROR: Incorrect positions given: empty FM"<<endl;
    return NULL;
  }

  int i, j, flag = 0;
  for (i = src->get_x(), j = src->get_y() ;; i=i+x_offset, j=j+y_offset) {

    if (src->get_x() <= dest->get_x() && i > dest->get_x())
      flag++;
    if (src->get_x() >= dest->get_x() && i < dest->get_x())
      flag++;
    if (src->get_y() <= dest->get_y() && j > dest->get_y())
      flag++;
    if (src->get_y() >= dest->get_y() && j < dest->get_y())
      flag++;
    if (flag == 2)
      break;

    Image *frame = new Image(*prev_frame);
    frame->strokeColor("black");
    frame->fillColor("black");
    frame->strokeWidth(5);
    frame->draw(DrawableLine(src->get_x(), src->get_y(), i,j));
    ofm->add_frame(frame);
    prev_frame = frame;
  }

  mfm->add_frame_manager(ofm);
  mfm->composite_frames ("simple_overlay", NULL, mfm->REPEAT_ALL);
  // delete transparent_base, delete ofm, set prev_frame to NULL;
  return bkgnd_FM;
}
