/*
 * File:   global.h
 * Author: pehladik
 *
 * Created on 21 avril 2011, 12:14
 */

#include "global.h"

RT_TASK tServeur;
RT_TASK tconnect;
RT_TASK tmove;
RT_TASK tenvoyer;
RT_TASK tPeriodicArene;
RT_TASK tDetectionArene;
RT_TASK tBattery;
RT_MUTEX mutexArene;
RT_MUTEX mutexEtat;
RT_MUTEX mutexMove;
RT_MUTEX mutexDetectionArene;
RT_MUTEX mutexCamera;
RT_MUTEX mutexBattery;

RT_SEM semConnecterRobot;

RT_QUEUE queueMsgGUI;
int nbErreurConsecutive=0;
int etatCommMoniteur = 1;
int etatCommRobot = 1;
int etatArene = ARENE_SEND;
int etatAreneDetection;

DRobot *robot;
DMovement *move;
DServer *serveur;
DCamera *camera;
DArena *arene;

DBattery *battery;

int MSG_QUEUE_SIZE = 10;

int PRIORITY_TSERVEUR = 30;
int PRIORITY_TCONNECT = 20;
int PRIORITY_TMOVE = 10;
int PRIORITY_TENVOYER = 25;
int PRIORITY_TBATTERY = 10;
// RANDOM PRIORITY
int PRIORITY_TPERIODICARENE = 10;
int PRIORITY_TDETECTIONARENE = 20;
