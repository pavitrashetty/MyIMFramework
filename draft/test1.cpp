#include "mynge.hpp"

int main(int argc,char **argv)
{

  InitializeMagick(*argv);          // is this needed?

  Image *orig_base = new Image("/home/pavitra-ubuntu/Downloads/inputs/page0.jpg");
  Image *over = new Image("/home/pavitra-ubuntu/Downloads/inputs/page2.jpg");
  
  Geometry *geom = new Geometry(orig_base->baseColumns(), orig_base->baseRows());
  Image *base = new Image (*geom,"white");
  base->opacity(TransparentOpacity);

  base->write("/home/pavitra-ubuntu/my_trials/base.png");
  over->write("/home/pavitra-ubuntu/my_trials/over.png");
  over->resize("500x500");
  base->composite(*over, 0, 0, OverCompositeOp);
  orig_base->composite(*base, 0,0, OverCompositeOp);
  orig_base->write("/home/pavitra-ubuntu/my_trials/op.png");

  return 0;
}