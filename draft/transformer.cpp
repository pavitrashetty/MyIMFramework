#include "transformer.hpp"

Transformer::Transformer () {}

bool Transformer::affine (Image *img, float angle) {
	img->virtualPixelMethod(TransparentVirtualPixelMethod);
	float sx = cos(angle * PI/180.0);
	float rx = sin(angle * PI/180.0);
	img->affineTransform(DrawableAffine(sx,sx,rx,-1*rx,0,0));
	return true;
}

Image *Transformer::resize (Image *img, int width, int height) {
  Image *dest = new Image(*img);
  Geometry *geom = new Geometry(width,height,0,0);
  geom->aspect(1);      // similar to wxh!
  dest->resize(*geom);
  // TODO: -resize "widthxheight^" -crop -gravity center "widthxheight+0+0"
	return dest;
}

bool Transformer::composite (Image *dest, Image *src, const char *composition_method, Geometry *new_geom) {
	if (strcmp(composition_method,"simple_overlay") == 0 && new_geom == NULL) {
    dest->composite(*src, 0, 0, OverCompositeOp);
  }
  if (strcmp(composition_method,"simple_overlay") == 0 && new_geom != NULL) {
    dest->composite(*src, *new_geom, OverCompositeOp);
  }
  /*if (strcmp(composition_method,"blender") == 0) {
    // args = "blend=30"
    if (args.find("blend") == string::npos) {
      cout<<"Error in arguements provided...";
      return false;
    }
    int value = stoi(args.substr(args.find("blend")+7, 2), NULL);
    cout<<"Blend value is "<<value;
    Image *over = new Image (*src);
    // multiply alpha channel of over by blend %
    dest->composite(*over, 0, 0, OverCompositeOp);
  }*/
  return true;
}
