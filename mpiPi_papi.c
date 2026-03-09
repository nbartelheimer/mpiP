#include <stdlib.h>
#include "mpiPi_papi.h"

int llc_event_set = -1;

void papi_module_init(){
	char *counter_name = NULL;
	int event_code = PAPI_NULL;
	PAPI_library_init(PAPI_VER_CURRENT);
	llc_event_set = PAPI_NULL;
	PAPI_create_eventset(&llc_event_set);
	counter_name = getenv("MPIP_PAPI_EVENT_NAME");
	PAPI_event_name_to_code(counter_name, &event_code);
	PAPI_add_event(llc_event_set,event_code);
}

void papi_module_finalize(){
	PAPI_shutdown();
}
