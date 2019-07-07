#ifndef cbr_traffic_h
#define cbr_traffic_h

#include <stdlib.h>
 
#include "random.h"
#include "trafgen.h"
#include "ranvar.h"
/* 
 * Constant bit rate traffic source.   Parameterized by interval, (optional)
 * random noise in the interval, and packet size.  
 */

class CBR_Traffic : public TrafficGenerator {
 public:
	CBR_Traffic();
	virtual double next_interval(int&);
	//HACK so that udp agent knows interpacket arrival time within a burst
	inline double interval() { return (interval_); }
    void setmaxpkts(int maxpkts){maxpkts_ = maxpkts;} //sets maxpkts_
	int getmaxpkts(){return maxpkts_;} //gets maxpkts_
 protected:
	virtual void start();
	void init();
	double rate_;     /* send rate during on time (bps) */
	double interval_; /* packet inter-arrival time during burst (sec) */
	double random_;
	int seqno_;
	int maxpkts_;
};


static class CBRTrafficClass : public TclClass {
 public:
	CBRTrafficClass() : TclClass("Application/Traffic/CBR") {}
	TclObject* create(int, const char*const*) {
		return (new CBR_Traffic());
	}
} class_cbr_traffic;

#endif