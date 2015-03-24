#include "periodic_arena.h"


void areneEnvoyerMessage(void * arg) {
    int status;
    DImage* img;
    DJpegimage* jpegImage;
    DMessage *message;

    rt_printf("tEnvoiMessageArene : Debut de l'exécution de l'envoi d'images de l'arene\n");
    rt_task_set_periodic(NULL, TM_NOW, 600000000);

    while(1){
        rt_task_wait_period(NULL);
        rt_mutex_acquire(&mutexArene, TM_INFINITE);
        status = etatArene;
        rt_mutex_release(&mutexArene);
        if(status == ARENE_SEND){
            img = d_new_image();
            jpegImage = d_new_jpegimage();
            rt_mutex_acquire(&mutexCamera, TM_INFINITE);
    		camera->get_frame(camera, img);
    		rt_mutex_release(&mutexCamera);
            jpegImage->compress(jpegImage, img);
            message = d_new_message();
            message->put_jpeg_image(message, jpegImage);
            printf("arena send image : Envoi message & image arene\n");
            if (write_in_queue(&queueMsgGUI, message, sizeof (DMessage)) < 0) {
                message->free(message);
            }
        } 
    }   
}