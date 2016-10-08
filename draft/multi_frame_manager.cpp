#include "multi_frame_manager.hpp"


Multiframe_Manager::Multiframe_Manager () {
	no_frame_managers = 0;
	//cur_FM = null;
}

Multiframe_Manager::Multiframe_Manager (Frame_Manager *FMgr) {
	this->no_frame_managers = 0;
	this->add_frame_manager(FMgr);
}

void Multiframe_Manager::add_frame_manager (Frame_Manager *FMgr) {
	if (!FMgr) {
		cout<<"Invalid frame manager"<<endl;
		return;
	}
	MFManager.push_back(FMgr);
	no_frame_managers++;
}

void Multiframe_Manager::remove_frame_manager(int index) {
	if (index >= no_frame_managers) {
		cout<<"Index out of range - Surprised?"<<endl;
		return;
	}
	fm_iterator itr = begin();
	std::advance(itr, index);
	MFManager.erase(itr);
	no_frame_managers--;
	return;
}

Frame_Manager *Multiframe_Manager::get_last_frame_manager() {
	if (no_frame_managers == 0)
		return NULL;
	return MFManager.back();
}

Frame_Manager *Multiframe_Manager::get_first_frame_manager() {
	if (no_frame_managers == 0)
		return NULL;
	fm_iterator itr = MFManager.begin();
	return *itr;

}

fm_iterator Multiframe_Manager::begin() {
  return MFManager.begin();
}

fm_iterator Multiframe_Manager::end() {
  return MFManager.end();
}

Frame_Manager *Multiframe_Manager::get_frame_manager(int index) {
	if (index >= no_frame_managers) {
		cout<<"Index out of range: Seriously!!!";
		return NULL;
	}
	fm_iterator itr = this->begin();
	std::advance(itr, index);
	return *itr;
}

// TODO: flag for shortest or longest
void Multiframe_Manager::composite_frames (const char *type_composition, Position *pos, int repeat_method) {

	Frame_Manager *baseFM = MFManager.front();

	fm_iterator cur_FM = begin();
	for (++cur_FM; cur_FM != end(); ++cur_FM) {

		std::list<Image*>::iterator base_frame;
		std::list<Image*>::iterator cur_frame;
		Transformer *trans = new Transformer();

		// What if no of frames in base != no of frames in overlay?
		// Now: whichever is the longest.

		base_frame = (*baseFM).begin();
		while ( (*cur_FM)->get_no_frames() - baseFM->get_no_frames() > 0) {
			Image *nimg = new Image(*(*base_frame));
			baseFM->add_frame(nimg);
			base_frame++;
		}		

		for (base_frame = (*baseFM).begin(), cur_frame = (*cur_FM)->begin(); base_frame != (*baseFM).end(); base_frame++, cur_frame++) {
			if (cur_frame == (*cur_FM)->end()) {
				if (repeat_method == REPEAT_ALL)
					cur_frame = (*cur_FM)->begin();
				else if(repeat_method == REPEAT_LAST)
					cur_frame--; 
			}
			Geometry *geom;
			if (pos != NULL)
				geom = new Geometry(0, 0, pos->get_x(), pos->get_y());
			else
				geom = NULL;
			if (trans->composite(*base_frame, *cur_frame, type_composition, geom) != true) {
				cout<<"Failed composition";
				return;
			}			
		}
	}
}

Frame_Manager *Multiframe_Manager::append_frame_managers() {
	Frame_Manager *fm = new Frame_Manager();
	for (fm_iterator itr = begin() ; itr != end() ; itr++) {
		Frame_Manager *cur_fm = *itr;
		for (std::list<Image*>::iterator cur_frame = cur_fm->begin() ; cur_frame != cur_fm->end() ; ++cur_frame) {
			fm->add_frame(*cur_frame);
		}
	}
	return fm;
}
