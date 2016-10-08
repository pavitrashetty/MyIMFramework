/*
MOTIVE:
  Given product images, create a vertical ad video. Pseudo trial.
*/

#include "mynge.hpp"

int main(int argc,char **argv)
{

  InitializeMagick(*argv);          // is this needed?

  char no[10];
  char filename[20];
  int no_products = 3;
  Frame_Manager *in_fm = new Frame_Manager();
  Multiframe_Manager *mfm =  new Multiframe_Manager();

  in_fm->add_frame( new Image ("/home/pavitra-ubuntu/Downloads/inputs/text_page1.jpg") );
  in_fm->add_frame( new Image ("/home/pavitra-ubuntu/Downloads/inputs/tv3.jpg") );
  in_fm->add_frame( new Image ("/home/pavitra-ubuntu/Downloads/inputs/tv2.jpg") );
  in_fm->add_frame( new Image ("/home/pavitra-ubuntu/Downloads/inputs/tv1.jpg") );  

  Movement *mvobj = new Movement();
  mvobj->set_background(new Image("/home/pavitra-ubuntu/Downloads/inputs/canvas.jpg"));
  Resolution *res = new Resolution(720,500);
  int direction=1;
  Position *start = new Position(), *end = new Position(), *center = new Position(0,400);

  for (frame_iterator fitr = in_fm->begin() ; fitr != in_fm->end() ; fitr++, direction++) {

    Image *prod = *fitr;
    //cout<<"direction = "<<direction<<endl;
    
    if (direction % 4 == 1) {
      start->set_position(-750,400);
      end->set_position(740,400);
    } else if (direction % 4 == 2) {
      start->set_position(740,400);
      end->set_position(-750,400);
    } else if (direction % 4 == 3) {
      start->set_position(0,-500);
      end->set_position(0,1800);
    } else {
      start->set_position(0,1800);
      end->set_position(0,-500);
    }

    mfm->add_frame_manager(mvobj->straight_line(prod, res, start, center, 1));
    Frame_Transformer *ftrans = new Frame_Transformer();
    mfm->add_frame_manager( ftrans->copy_frames( mfm->get_last_frame_manager()->get_last_frame(), 2, 30 ));
    mfm->add_frame_manager(mvobj->straight_line(prod, res, center, end, 1));
  }

  Frame_Manager *fm = mfm->append_frame_managers();
  cout<<"Dumping all frames..."<<endl;
  fm->dump_frames("new_frames","ad","jpg", 1);

  return 0;
}
