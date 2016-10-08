#include <Magick++.h>
#include <iostream>
#include <string.h>
#include <strings.h>
using namespace std;
using namespace Magick;

int main(int argc,char **argv)
{
  InitializeMagick(*argv);

  std::list<Image> frames;
  std::list<string> image_files;
  image_files.push_back("/home/pavitra/Downloads/image_jugaad/kaleidoscope/new/Images1.jpg");
  image_files.push_back("/home/pavitra/Downloads/image_jugaad/kaleidoscope/new/Images2.jpg");
  image_files.push_back("/home/pavitra/Downloads/image_jugaad/kaleidoscope/new/Images3.jpg");
  image_files.push_back("/home/pavitra/Downloads/image_jugaad/kaleidoscope/new/Images4.jpg");
  image_files.push_back("/home/pavitra/Downloads/image_jugaad/kaleidoscope/new/Images5.jpg");
  image_files.push_back("/home/pavitra/Downloads/image_jugaad/kaleidoscope/new/Images6.jpg");

  try {
    std::list<string>::const_iterator cur_image;
    for (cur_image = image_files.begin(); cur_image != image_files.end(); ++cur_image) {
        for (int offset = 0; offset < 1297; offset = offset + 20) {
            Image element, mask;
            mask.read( cur_image->c_str() );
            element = mask;
            // create mask image
            mask.colorize(100, "black");
            mask.fillColor("white");
            std::list<Magick::Coordinate> cordinates;
            cordinates.push_back(Coordinate(offset, 0));
            cordinates.push_back(Coordinate(offset,1080));
            cordinates.push_back(Coordinate(offset+623,1080));
            mask.draw(DrawablePolygon(cordinates));
            mask.magick("PNG");
            mask.matte(false);
            // get element
            element.magick("PNG");
            element.matte(false);
            element.composite(mask, 0, 0, CopyOpacityCompositeOp);
            element.trim();
            //mask.write( "mask.png" );
            //element.write( "elem.png" );
            // get element2
            std::list<Image> imageList;
            Image flElement = element;
            flElement.flop();
            imageList.push_back(flElement);
            imageList.push_back(element);
            Image element2;
            appendImages(&element2, imageList.begin(), imageList.end(), false);
            //element2.write("elem2.png");
            //get element3
            Image element3 = element2;
            Color c(1,1,1,TransparentOpacity);
            element3.backgroundColor(c);
            element3.rotate(-60);
            element3.trim();
            //element3.write ("elem3.png");
            //get element4
            Image element4("3000x1080","black");
            element4.magick("PNG");
            element4.transparent("black");    //instead can we have a transparent bkgnd?
            element4.composite(element2, 0, 0, OverCompositeOp);
            element4.composite(element3, 624, 0, OverCompositeOp);
            element4.trim();
            //element4.write ("elem4.png");
            //get element5
            flElement = element4;
            flElement.flip();
            std::list<Image> imageList2;
            imageList2.push_back(flElement);
            imageList2.push_back(element4);
            Image element5;
            appendImages(&element5, imageList2.begin(), imageList2.end(), true);
            //element5.write("elem5.png");
            //get element6
            Image element6 = element4;
            element6.backgroundColor(c);
            element6.rotate(120);
            element6.trim();
            //element6.write ("elem6.png");
            //get element7
            Image element7("2500x2000","black");
            element7.magick("PNG");
            element7.transparent("black");    //instead can we have a transparent bkgnd?
            element7.composite(element6, 0, 0, OverCompositeOp);
            element7.composite(element5, 625, 0, OverCompositeOp);
            element7.trim();
            //element7.write ("elem7.png");
            //get frame
            int x_offset = element7.columns()/2 - 960;
            int y_offset = element7.rows()/2 - 540;
            Geometry newSize (1920, 1080, x_offset, y_offset);
            element7.crop(newSize);
            frames.push_back(element7);
        }
    }

    std::list<Image>::const_iterator framing;
    char no[10];
    int count;
    for (framing = frames.begin(), count = 0; framing != frames.end(); ++framing, ++count) {
        sprintf(no, "%d", count);
        char filename[] = "frames/frame";
        strcat (filename, no);
        strcat (filename, ".png");
        Image cur_frame = *framing;
        cur_frame.write(filename);
    }
  }
  catch( Exception &error_ )
    {
      cout << "Caught exception: " << error_.what() << endl;
      return 1;
    }
  return 0;
}
