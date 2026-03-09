#ifndef _MPIPI_PAPI_H
#define _MPIPI_PAPI_H
#include <papi.h>

extern int llc_event_set;

static inline void papi_start_collect(){
	PAPI_start(llc_event_set);
}

static inline void papi_stop_collect(long long *counter){
	PAPI_stop(llc_event_set, counter);
	PAPI_reset(llc_event_set);
}

void papi_module_init();
void papi_module_finalize();

#endif
