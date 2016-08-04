/* 
 * File:   SR_FRS.h
 * Author: Rick
 *
 * Created on August 3, 2016, 1:22 PM
 */

#ifndef SR_FRS_H
#define	SR_FRS_H

//TX Frequency - need to be the same, unless we use a repeater
#define TXFrequency 450.0250
#define RXFrequency 450.0250

//Radio channel Code
#define TXCX 83
#define RXCX 83

//Squelch
#define SQ 2

void SR_FRSTalk();
void SR_RRSPowerDown();
void SR_FRSStart();
void SetCommandMode();
void SetFrequency();
void SetPowerSave();
void SetVolume(char volume);
void SetVOX(int volume);
void SetMIC(char volume, char scram);

#endif	/* SR_FRS_H */

