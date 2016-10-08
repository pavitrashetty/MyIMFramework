/*
MOTIVE:
  Given a background video and a foreground one, overlay the foreground on the background such that the overlay moves around in an arc
*/

#include "mynge.hpp"

int main(int argc,char **argv)
{

  InitializeMagick(*argv);

  Frame_Manager *fm_canvas = new Frame_Manager();
  Frame_Manager *fm_video = new Frame_Manager();
  Frame_Transformer *ft = new Frame_Transformer();
  Multiframe_Manager *mfm = new Multiframe_Manager();

  char no[10];
  char filename[20];

  int frame_tracker = 1;
  while (true) {
    strcpy(filename,"in_effect/img");
    sprintf(no, "%d", frame_tracker);
    frame_tracker++;
    strcat (filename, no);
    strcat (filename, ".jpg");
    if (FILE *file = fopen(filename, "r")) {
      try {
        Image *input1 = new Image(filename);
        fm_canvas->add_frame(input1);
      }
      catch(Magick::ErrorFileOpen &error)  {
        exit (1);
      }
    } else
      break;
  }
  cout<<"Breakpoint: filename1 "<<filename<<endl;

  frame_tracker = 1;
  while (true) {
    strcpy(filename,"in_video/vid");
    sprintf(no, "%d", frame_tracker);
    frame_tracker++;
    strcat (filename, no);
    strcat (filename, ".jpg");
    if (FILE *file = fopen(filename, "r")) {
      try {
        Image *input1 = new Image(filename);
        fm_video->add_frame(input1);
      }
      catch(Magick::ErrorFileOpen &error)  {
        exit (1);
      }
    } else
      break;
  }
  cout<<"Breakpoint: filename2 "<<filename<<endl;

  ft->affine_transform (fm_video, 10.0, -10.0, 0.1);
  cout<<"Breakpoint: transformed"<<endl;

  mfm->add_frame_manager(fm_canvas);
  mfm->add_frame_manager(fm_video);
  mfm->composite_frames("simple_overlay");

  cout<<"Dumping all frames"<<endl;
  fm_canvas->dump_frames("output_frames","img","jpg", 1);

  return 0;
}
