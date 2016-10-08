#ifndef __FRAME_MANAGER_INCLDUED__
#define __FRAME_MANAGER_INCLDUED__

# include "base.hpp"

typedef std::list<Image*>::iterator frame_iterator;
typedef std::list<Image*>::const_iterator frame_const_iterator;

class Frame_Manager {

	std::list<Image*> list_frames;
	int no_frames;
	
	public:

		// Basic handlers
    Frame_Manager ();
    ~Frame_Manager();
    void add_frame(Image *img);
    int get_no_frames();
    Image *get_last_frame();
    Image *get_first_frame();
    void dump_frames(const char *path, const char* filename, const char* format, int start_no);
    frame_iterator begin();
    frame_iterator end();
    
};

#endif