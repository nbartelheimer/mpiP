#include <stdlib.h>
#include <stdio.h>
#include "mpiPi_papi.h"

int llc_event_set = -1;

void papi_module_init(){
	char *counter_name = NULL;
	int event_code = PAPI_NULL;
	int ret = -1;
	if((ret = PAPI_library_init(PAPI_VER_CURRENT)) != PAPI_VER_CURRENT){
		fprintf(stderr,"[PAPI_MODULE_ERROR] Version mismatch! Requried: %i Actual: %i\n",PAPI_VER_CURRENT,ret);
		exit(EXIT_FAILURE);
	}
	llc_event_set = PAPI_NULL;
	if((ret = PAPI_create_eventset(&llc_event_set)) != PAPI_OK){
		fprintf(stderr,"[PAPI_MODULE_ERROR] %s in %s at %d\n", PAPI_strerror(ret),__FILE__,__LINE__);
		exit(EXIT_FAILURE);
	}
	counter_name = getenv("MPIP_PAPI_EVENT_NAME");
	if(counter_name == NULL){
		fprintf(stderr,"[PAPI_MODULE_ERROR] MPIP_PAPI_EVENT_NAME cannot be empty!\n");
		exit(EXIT_FAILURE);
	}
	if((ret = PAPI_event_name_to_code(counter_name, &event_code)) != PAPI_OK){
		fprintf(stderr,"[PAPI_MODULE_ERROR] %s in %s at %d\n", PAPI_strerror(ret),__FILE__,__LINE__);
		exit(EXIT_FAILURE);
	}

	if((ret = PAPI_add_event(llc_event_set,event_code)) != PAPI_OK){
		fprintf(stderr,"[PAPI_MODULE_ERROR] %s in %s at %d\n", PAPI_strerror(ret),__FILE__,__LINE__);
		exit(EXIT_FAILURE);

	}
}

void papi_module_finalize(){
	PAPI_shutdown();
}
