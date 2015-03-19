/* 
 * File:   global.h
 * Author: pehladik
 *
 * Created on 12 janvier 2012, 10:11
 */

#ifndef GLOBAL_H
#define	GLOBAL_H

#include "includes.h"

/* @descripteurs des tâches */
extern RT_TASK tServeur;
extern RT_TASK tconnect;
extern RT_TASK tmove;
extern RT_TASK tenvoyer;
extern RT_TASK tPeriodicArene;
extern RT_TASK tDetectionArene;

/* @descripteurs des mutex */
extern RT_MUTEX mutexEtat;
extern RT_MUTEX mutexMove;
extern RT_MUTEX mutexArene;
extern RT_MUTEX mutexDetectionArene;
extern RT_MUTEX mutexCamera;

/* @descripteurs des sempahore */
extern RT_SEM semConnecterRobot;

/* @descripteurs des files de messages */
extern RT_QUEUE queueMsgGUI;

/* @variables partagées */
extern int etatCommMoniteur;
extern int etatCommRobot;
extern DServer *serveur;
extern DRobot *robot;
extern DMovement *move;
extern DCamera* camera;
extern DArena* arene;

/* @constantes */
extern int MSG_QUEUE_SIZE;
extern int PRIORITY_TSERVEUR;
extern int PRIORITY_TCONNECT;
extern int PRIORITY_TMOVE;
extern int PRIORITY_TENVOYER;
extern int PRIORITY_TPERIODICARENE;
extern int PRIORITY_TDETECTIONARENE;

//----A NOUS ---

extern int nbErreurConsecutive;
extern int etatArene;
extern int etatAreneDetection;

#endif	/* GLOBAL_H */

