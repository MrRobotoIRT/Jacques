#include "detection_arena.h"

void detectionArene(void * arg) {
	while(1){
		rt_task_suspend(NULL);
		int statutDetection;
		rt_mutex_acquire(&mutexDetectionArene, TM_INFINITE);
    	statutDetection = etatAreneDetection;
    	rt_mutex_release(&mutexDetectionArene);
    	switch(statutDetection){
    		case ACTION_FIND_ARENA:
    			findArene();
    			break;
        	case ACTION_ARENA_FAILED:
        		cancelFindArene();
        		break;
        	case ACTION_ARENA_IS_FOUND:
        		arenaFound();
        		break;
   	 	}

	}
}
void findArene(){
	DImage* img;
    DJpegimage* jpegImage;
    DMessage *message;
    DArena *tmpArene;
	rt_mutex_acquire(&mutexArene, TM_INFINITE);
    etatArene = ARENE_DONT_SEND;
    rt_mutex_release(&mutexArene);
    img = d_new_image();
    rt_mutex_acquire(&mutexCamera, TM_INFINITE);
    camera->get_frame(camera, img);
    rt_mutex_release(&mutexCamera);
    tmpArene=img->compute_arena_position(img);
    if(tmpArene != NULL){
    	d_imageshop_draw_arena(img, tmpArene);
    	rt_mutex_acquire(&mutexDetectionArene, TM_INFINITE);
    	arene = d_new_arena();
    	memcpy(arene, tmpArene, sizeof(DArena));
    	rt_mutex_release(&mutexDetectionArene);
    }
    jpegImage = d_new_jpegimage();
    jpegImage->compress(jpegImage, img);
    img->free(img);
    message = d_new_message();
    message->put_jpeg_image(message, jpegImage);
    jpegImage->free(jpegImage);
    printf("arena send image : Envoi message & image arene\n");
    if (write_in_queue(&queueMsgGUI, message, sizeof (DMessage)) < 0) {
        message->free(message);
    }
}
void cancelFindArene(){
	rt_mutex_acquire(&mutexDetectionArene, TM_INFINITE);
	if(arene !=NULL){
		 arene->free(arene);
	}
   
    rt_mutex_release(&mutexDetectionArene);
	rt_mutex_acquire(&mutexArene, TM_INFINITE);
    etatArene = ARENE_SEND;
    rt_mutex_release(&mutexArene);
}
void arenaFound(){
	rt_mutex_acquire(&mutexArene, TM_INFINITE);
    etatArene = ARENE_SEND;
    rt_mutex_release(&mutexArene);
}