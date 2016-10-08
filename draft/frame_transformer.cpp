#include "frame_transformer.hpp"

Frame_Transformer::Frame_Transformer() {}

Frame_Manager *Frame_Transformer::copy_frames(Image *img, int duration, float fps) {
  int no_frames_to_create = ceil(duration*fps);
  Frame_Manager *fm = new Frame_Manager();
  for (int i = 0 ; i < no_frames_to_create ; i++) {
    Image *next_frame = new Image (*img);
    fm->add_frame(next_frame);
  }
  if (fm->get_no_frames() == no_frames_to_create)
    return fm;
  else
    return NULL;
}

bool Frame_Transformer::affine_transform(Frame_Manager *fm, float start_angle, float end_angle, float step) {
  float angle = start_angle;
  int flag = 0;
  if (end_angle < start_angle)
    flag = 1;
  // if flag = 0, step up.
  // if flag = 1, step down.
  std::list<Image*>::iterator cur_frame;
  for (cur_frame = fm->begin(); cur_frame != fm->end(); ++cur_frame) {
    //Image *frame = *cur_frame;
    Transformer aff;
    aff.affine(*cur_frame, angle);

    if (flag == 1) {
      angle = angle - step;
      if(start_angle < end_angle && angle < start_angle) {
        angle = start_angle + step;
        flag = 0;
      }
      else if (start_angle > end_angle && angle < end_angle) {
        angle = end_angle + step;
        flag = 0;
      }
    } else {
      angle = angle + step;
      if (start_angle < end_angle && angle > end_angle) {
        angle = end_angle - step;
        flag = 1;
      } else if (start_angle > end_angle && angle > start_angle) {
        angle = start_angle - step;
        flag = 1;
      }
    }
  }
  return true;
}

/* Zoom from start to end positions with res sized box. */
Frame_Manager *Frame_Transformer::zoomer(Frame_Manager *in_fm, Resolution *start_res, Resolution *end_res, Position *start, Position *end, int duration) {

  int no_frames_to_create = duration*30;    // Seriously!!!

  while (no_frames_to_create > in_fm->get_no_frames()) {
    frame_iterator fiter = in_fm->end();
    Image *temp = new Image(**(--fiter));
    in_fm->add_frame(temp);
  }

  float delta_w = floor((end_res->get_w() - start_res->get_w())/no_frames_to_create);
  float delta_h = floor((end_res->get_h() - start_res->get_h())/no_frames_to_create);
  float delta_x = floor((end->get_x() - start->get_x())/no_frames_to_create);
  float delta_y = floor((end->get_y() - start->get_y())/no_frames_to_create);

  size_t crop_w = start_res->get_w();
  size_t crop_h = start_res->get_h();
  size_t crop_x = start->get_x();
  size_t crop_y = start->get_y();

  frame_iterator fiter = in_fm->begin();
  size_t std_w = (*fiter)->baseColumns();
  size_t std_h = (*fiter)->baseRows();

  cout<<"no_frames="<<no_frames_to_create<<"std values ="<<std_w<<","<<std_h<<endl<<"dw="<<delta_w<<" dh="<<delta_h<<" dx="<<delta_x<<" dy="<<delta_y<<endl;
  for (fiter = in_fm->begin(); fiter != in_fm->end() ; ++fiter) {
    cout<<"w="<<crop_w<<" h="<<crop_h<<" x="<<crop_x<<" y="<<crop_y<<endl;
    Image *cur_frame = *fiter;
    cur_frame->crop(Geometry(crop_w, crop_h, crop_x, crop_y));
    cur_frame->resize(Geometry(std_w,std_h,0,0));
    crop_w += delta_w;
    crop_h += delta_h;
    crop_x += delta_x;
    crop_y += delta_y;
  }  
  return in_fm;
}

Frame_Manager *Frame_Transformer::enlarge(Image *img, Resolution *start_res, Resolution *end_res, int duration) {

  Frame_Manager *fm = new Frame_Manager();
  int no_frames_to_create = duration * 30 ;
  Image *bkgnd = new Image(*(end_res->get_resolution()),"white");
  bkgnd->opacity(TransparentOpacity);

  size_t delta_w = (end_res->get_w() - start_res->get_w())/no_frames_to_create;
  size_t delta_h = (end_res->get_h() - start_res->get_h())/no_frames_to_create;

  size_t new_w = start_res->get_w();
  size_t new_h = start_res->get_h();

  while (no_frames_to_create) {
    Image *frame = new Image(*bkgnd);
    if (new_w != 0 && new_h != 0) {
      Transformer *tran = new Transformer();
      size_t mid_w = (end_res->get_w() - new_w)/2;
      size_t mid_h = (end_res->get_h() - new_h)/2;
      tran->composite (frame, tran->resize(img, new_w, new_h), "simple_overlay", new Geometry(0, 0, mid_w, mid_h));
    }
    fm->add_frame(frame);
    new_w += delta_w;
    new_h += delta_h;
    no_frames_to_create--;
  }
  return fm;
}

