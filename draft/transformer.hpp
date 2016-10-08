#ifndef __TRANSFORMER__
#define __TRANSFORMER__

# include "base.hpp"


/* TRANSFORMER CLASS:
    Imitation of the IM library
    Input= 1 or 2 images
    Output= 1 image
*/
class Transformer {

	public:

		Transformer ();

		bool affine (Image *img, float angle);
		Image *resize (Image *img, int width, int height);
		bool composite (Image *dest, Image *src, const char *composition_method, Geometry *new_geom);
    //blah blah methods as per requirement

    // Not yet implemented
    Image * getCanvas (char *geom, char *color);
    Image * copyImage (Image *img);


};

#endif