#ifndef __MULTI_FRAME_MANAGER_INCLDUED__
#define __MULTI_FRAME_MANAGER_INCLDUED__

# include "frame_manager.hpp"
#include "transformer.hpp"
#include "utils.hpp"


typedef std::list<Frame_Manager*>::iterator fm_iterator;
typedef std::list<Frame_Manager*>::const_iterator fm_const_iterator;

class Multiframe_Manager {
	std::list<Frame_Manager*> MFManager;
	int no_frame_managers;

  public:
     
  	// Basic handlers
    Multiframe_Manager ();
  	Multiframe_Manager (Frame_Manager *FMgr);
  	void add_frame_manager (Frame_Manager *FMgr);
    void remove_frame_manager(int index);
    Frame_Manager *get_frame_manager(int index);
    Frame_Manager *get_last_frame_manager();
    Frame_Manager * get_first_frame_manager();
    fm_iterator begin();
    fm_iterator end();
    static const int REPEAT_LAST = 1;
    static const int REPEAT_ALL = 2;
    // Appends all FMs and returns a FM
    Frame_Manager *append_frame_managers();


    // Just like FM<-->FM_Transformer, we need to have MFM<-->FM_Movement that will have below methods
    // For now, Movement class takes care of it!!!

  	// Takes a base FM - the first FM in list - and composites all other FMs on it one by one using type_composition method
  	void composite_frames (const char* type_composition, Position *pos, int repeat_method);
};

#endif