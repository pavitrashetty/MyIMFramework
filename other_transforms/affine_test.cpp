#include <Magick++.h>
#include <iostream>
#include <string.h>
#include <math.h>

#define PI 3.14159265

using namespace std;
using namespace Magick;

void dumpFrames(list<Image> frames){
  cout<<"Dumping all frames";
  std::list<Image>::const_iterator itr;
  char no[10];
  int count;
  for (itr=frames.begin(), count = 0; itr != frames.end() ; itr++, count++){
    sprintf(no, "%d", count);
    char filename[] = "out_frames/frame";
    strcat (filename, no);
    strcat (filename, ".jpg");
    Image cur_frame = *itr;
    cur_frame.write(filename);
  }
}




int main(int argc,char **argv)
{
  InitializeMagick(*argv);
  std::list<Image> frames;
  char no[10];
  float angle = 10.0;
  int flag = 0;
  int canvas_frame = 1;
  int canvas_limit = 200;

  for (int in_frame=1 ; in_frame < 376 ; in_frame++) {
    char filename[] = "in_effect/img";
    sprintf(no, "%d", canvas_frame);
    strcat (filename, no);
    strcat (filename, ".jpg");
    Image canvas(filename);
    cout<<"\nProcessing "<<filename;
    canvas_frame++;
    if (canvas_frame > canvas_limit)
        canvas_frame = 1;
    
    for (int in = 1 ; in < 5 ; in++) {
      if (in == 1)
        strcpy(filename,"in_video/vid1");
      else if (in == 2)
        strcpy(filename,"in_video/vid2");
      else if (in == 3)
        strcpy(filename,"in_video/vid3");
      else if (in == 4)
        strcpy(filename,"in_video/vid4");

      sprintf(no, "%d", in_frame);
      strcat (filename, no);
      strcat (filename, ".jpg");
      Image input1(filename);
      input1.virtualPixelMethod(TransparentVirtualPixelMethod);
      float sx = cos(angle * PI/180.0);
      float rx = sin(angle * PI/180.0);
      input1.affineTransform(DrawableAffine(sx,sx,rx,-1*rx,0,0));
      input1.resize(Geometry("500x300!"));

      if (in == 1)
        canvas.composite(input1, 100, 100, OverCompositeOp);
      else if (in == 2)
        canvas.composite(input1, 1000, 100, OverCompositeOp);
      else if (in == 3)
        canvas.composite(input1, 100, 600, OverCompositeOp);
      else if (in == 4)
        canvas.composite(input1, 1000, 600, OverCompositeOp);
    }
    frames.push_back(canvas);
    if (flag == 0)
      angle = angle - 0.1;
    else
      angle = angle + 0.1;
    if (angle < -10.0) {
      angle = -9.9;
      flag = 1;
    }
    if (angle > 10.0) {
      angle = 9.9;
      flag = 0;
    }
    //input1.rotate(-10);
    //input1.wave(-100,2160);
    //input1.crop(Geometry("1920x1080"));
    //input1.rotate(-90);
  }
  dumpFrames (frames);

  return 0;
}
