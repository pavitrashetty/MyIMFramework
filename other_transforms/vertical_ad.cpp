#include <Magick++.h>
#include <iostream>
#include <string.h>
using namespace std;
using namespace Magick;

Magick::Image composeImg(Magick::Image dest, Magick::Image src, Magick::Geometry new_size, Magick::Geometry new_offset) {
  cout<<"In compose()\n";
  src.resize(new_size);
  dest.composite(src, new_offset.width(),new_offset.height(), OverCompositeOp);
  return dest;
}

void dumpFrames(list<Image> frames){
  cout<<"Dumping all frames";
  std::list<Image>::const_iterator itr;
  char no[10];
  int count;
  for (itr=frames.begin(), count = 0; itr != frames.end() ; itr++, count++){
    sprintf(no, "%d", count);
    char filename[] = "frames/frame";
    strcat (filename, no);
    strcat (filename, ".jpg");
    Image cur_frame = *itr;
    cur_frame.write(filename);
  }
}




int main(int argc,char **argv)
{
  InitializeMagick(*argv);
  Image canvas("720x1280", "yellow");
  Image input1(argv[1]);
  std::list<Image> frames;

  for (int i = 0; i < 150 ; i++) {
    Geometry new_size("720x300!");
    Geometry new_offset (0, i);
    frames.push_back(composeImg(canvas, input1, new_size, new_offset));
  }

  dumpFrames(frames);
  return 0;
}
