/*
MOTIVE:
  Given product images, create a vertical ad video. Pseudo trail 2.
*/

#include "mynge.hpp"

int main(int argc,char **argv)
{

  InitializeMagick(*argv);          // is this needed?

  char no[10];
  char filename[20];
  int no_products = 3;
  Multiframe_Manager *main_mfm =  new Multiframe_Manager();
  Multiframe_Manager *prod_mfm = new Multiframe_Manager();
  Frame_Manager *temp_fm;

  Image *text1 = new Image ("/home/pavitra-ubuntu/Downloads/inputs/text_page1.jpg");
  Image *text2 = new Image ("/home/pavitra-ubuntu/Downloads/inputs/text_page2.jpg");
  Image *text3 = new Image ("/home/pavitra-ubuntu/Downloads/inputs/text_page3.jpg");
  Image *text4 = new Image ("/home/pavitra-ubuntu/Downloads/inputs/text_page4.jpg");
  Image *prod1 = new Image ("/home/pavitra-ubuntu/Downloads/inputs/tv3.jpg");
  Image *prod2 = new Image ("/home/pavitra-ubuntu/Downloads/inputs/tv2.jpg");
  Image *prod3 = new Image ("/home/pavitra-ubuntu/Downloads/inputs/tv1.jpg");
  Image *canvas = new Image("/home/pavitra-ubuntu/Downloads/inputs/canvas.jpg");

  Movement *mvobj = new Movement();
  Frame_Transformer *ftrans = new Frame_Transformer();

  // Starting page1
  mvobj->set_background(canvas);
  mvobj->set_moving_object(text1);
  main_mfm->add_frame_manager(mvobj->straight_line(new Resolution(600,300), new Position(-750,400), new Position(50,400), 1));
  main_mfm->add_frame_manager( ftrans->copy_frames( main_mfm->get_last_frame_manager()->get_last_frame(), 2, 30 ));

  // Ending page1
  mvobj->set_background(canvas);
  mvobj->set_moving_object(text1);
  main_mfm->add_frame_manager(mvobj->straight_line(new Resolution(600,300), new Position(50,400), new Position(740,400), 1));

  // Starting page2
  mvobj->set_background(canvas);
  mvobj->set_moving_object(text2);
  temp_fm = mvobj->straight_line(new Resolution(720,200), new Position(-750,200), new Position(0,200), 1);

  mvobj->set_background(temp_fm);
  mvobj->set_moving_object(prod1);
  main_mfm->add_frame_manager(mvobj->straight_line(new Resolution(720,400), new Position(0,1800), new Position(0,400), 1));

  // Page2 transitions
  mvobj->set_background(main_mfm->get_last_frame_manager()->get_last_frame());
  mvobj->set_moving_object(text3);
  main_mfm->add_frame_manager(mvobj->straight_line(new Resolution(200,100), new Position(-250,1000), new Position(0,1000), 1));

  mvobj->set_background(main_mfm->get_last_frame_manager()->get_last_frame());
  mvobj->set_moving_object(text4);
  temp_fm = mvobj->straight_line(new Resolution(200,100), new Position(800,1000), new Position(500,1000), 1);
  
  mvobj->set_background(temp_fm);
  main_mfm->add_frame_manager( mvobj->draw_line(new Position(0,1010), new Position(150,1010), 1) );

  // Creating slideshow of products
  Transformer *img_trans = new Transformer();
  img_trans->composite(canvas, img_trans->resize(text2,720,200), "simple_overlay", Position(0,200).get_postion());
  img_trans->composite(canvas, img_trans->resize(text3,200,100), "simple_overlay", Position(0,1000).get_postion());
  img_trans->composite(canvas, img_trans->resize(text4,200,100), "simple_overlay", Position(500,1000).get_postion());
  mvobj->set_background(canvas);
  mvobj->set_moving_object(prod1);
  temp_fm = mvobj->straight_line(new Resolution(720,400), new Position(0,400), new Position(-750,400), 1);
  mvobj->set_background(temp_fm);
  mvobj->set_moving_object(prod2);
  prod_mfm->add_frame_manager( mvobj->straight_line(new Resolution(720,400), new Position(720,400), new Position(0,400), 1) );
  prod_mfm->add_frame_manager( ftrans->copy_frames( temp_fm->get_last_frame(), 2, 30 ) );
  mvobj->set_background(canvas);
  mvobj->set_moving_object(prod2);
  temp_fm = mvobj->straight_line(new Resolution(720,400), new Position(0,400), new Position(-750,400), 1);
  mvobj->set_background(temp_fm);
  mvobj->set_moving_object(prod3);
  prod_mfm->add_frame_manager( mvobj->straight_line(new Resolution(720,400), new Position(720,400), new Position(0,400), 1) );
  prod_mfm->add_frame_manager( ftrans->copy_frames( temp_fm->get_last_frame(), 2, 30 ) );

  temp_fm = prod_mfm->append_frame_managers();
  mvobj->set_background(temp_fm);
  main_mfm->add_frame_manager( mvobj->draw_line(new Position(0,1010), new Position(150,1010), 1) );


  Frame_Manager *fm = main_mfm->append_frame_managers();
  cout<<"Dumping final frames..."<<endl;
  fm->dump_frames("new_frames","ad","jpg", 1);

  return 0;
}
