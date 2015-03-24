#include "compute_position.h"


void trouverPosition(void* arg){
	int status;
    DImage* img;
    DJpegimage* jpegImage;
    DMessage *messageImage, *messagePosition;
    DPosition* position;

    rt_printf("tComputePosition : Debut de l'exécution du thread compute_position\n");
    rt_task_set_periodic(NULL, TM_NOW, 600000000);

    while(1){
        rt_task_wait_period(NULL);
        rt_mutex_acquire(&mutexDetect, TM_INFINITE);
        status = hasToDetect;
        rt_mutex_release(&mutexDetect);
        if(status){
        	
        	if(arene !=NULL){
        		img = d_new_image();
    			rt_mutex_acquire(&mutexCamera, TM_INFINITE);
    			camera->get_frame(camera, img);
    			rt_mutex_release(&mutexCamera);
    			position=img->compute_robot_position(img, arene);
    			d_imageshop_draw_position(img, position);
    			jpegImage = d_new_jpegimage();
    			jpegImage->compress(jpegImage, img);
  				img->free(img);
  				messageImage = d_new_message();
    			messageImage->put_jpeg_image(messageImage, jpegImage);
    			jpegImage->free(jpegImage);
    			printf("arena send image : Envoi message & image arene\n");
    			if (write_in_queue(&queueMsgGUI, messageImage, sizeof (DMessage)) < 0) {
        		messageImage->free(messageImage);
    			}
    			if(position != NULL){
    				messagePosition = d_new_message();
    				messagePosition->put_position(messagePosition,position);
    				if (write_in_queue(&queueMsgGUI, messagePosition, sizeof (DMessage)) < 0) {
        			messagePosition->free(messagePosition);
    				}
    			}

        	}
    		

        }
    }   
}