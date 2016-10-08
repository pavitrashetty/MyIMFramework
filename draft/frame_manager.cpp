#include "frame_manager.hpp"

Frame_Manager::Frame_Manager() {
  no_frames = 0;
}

void Frame_Manager::add_frame(Image *img) {
	list_frames.push_back(img);
	no_frames++;
}

int Frame_Manager::get_no_frames() {
  return no_frames;
}

Image *Frame_Manager::get_first_frame() {
  return *list_frames.begin();
}

Image *Frame_Manager::get_last_frame() {
  return list_frames.back();
}

frame_iterator Frame_Manager::begin() {
  return list_frames.begin();
}

frame_iterator Frame_Manager::end() {
  return list_frames.end();
}



void Frame_Manager::dump_frames(const char *path, const char* filename, const char* format, int start_no) {
  char no[10];
  char location[20];
  std::list<Image*>::iterator cur_frame;
  for (cur_frame = list_frames.begin(); cur_frame != list_frames.end(); ++cur_frame, ++start_no){
    sprintf(no, "%d", start_no);
    strcpy(location, path);
    strcat(location, "/");
    strcat(location, filename);
    strcat (location, no);
    strcat(location, ".");
    strcat (location, format);
    Image *frame = *cur_frame;
    frame->write(location);
  }
}



