#include "mynge.hpp"

int main(int argc,char **argv)
{

  InitializeMagick(*argv);          // is this needed?

  Image *over = new Image("/home/pavitra-ubuntu/my_trials/in1.jpg");
  Frame_Transformer *ftrans = new Frame_Transformer();
  Frame_Manager *in_fm = ftrans->copy_frames(over, 2, 30);
  Frame_Manager *fmgr = ftrans->zoomer(in_fm, new Resolution(100,100), new Resolution(1000,1000), new Position(500,500), new Position(0,0),5);
  fmgr->dump_frames("new_frames","zoom","jpg", 1);
  return 0;
}