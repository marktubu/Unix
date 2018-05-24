#include "control.h"

int control_init(data_control* mycontrol)
{
	int mystatus;
	if(pthread_mutex_init(&(mycontrol->mutex),NULL))
		return 1;
	if(pthread_cond_init(&(mycontrol->cond),NULL))
		return 1;
	mycontrol->active = 0;
	return 0;
}

int control_destroy(data_control* mycontrol)
{
	int mystatus;
	if(pthread_mutex_destroy(&(mycontrol->mutex)))
		return 1;
	if(pthread_cond_destroy(&(mycontrol->cond)))
		return 1;
	mycontrol->active = 0;
	return 0;
}

int control_activate(data_control* mycontrol)
{
	int mystatus;
	if(pthread_mutex_lock(&(mycontrol->mutex)))
		return 0;
	mycontrol->active = 1;
	pthread_mutex_unlock(&(mycontrol->mutex));
	pthread_cond_broadcast(&(mycontrol->cond));
	return 1;
}

int control_deactivate(data_control* mycontrol)
{
	int mystatus;
	if(pthread_mutex_lock(&(mycontrol->mutex)))
		return 0;
	mycontrol->active = 0;
	pthread_mutex_unlock(&(mycontrol->mutex));
	pthread_cond_broadcast(&(mycontrol->cond));
	return 1;
}

