#include "sound.h"
#include "display.h"
#include "options.h"

byte soundAvailable=0;

void SoundSystemExists(void)
{
	soundAvailable=1;
}

void InitSound(void)
{
	JamulSoundPurge();
}

void ExitSound(void)
{
	// don't need to do nothing, it's handled by jamulsoundexit
}

void MakeSound(int snd,int x,int y,int flags,int priority)
{
	long pan,vol;
	int cx,cy;

	if(!soundAvailable)
		return;
	if(!opt.sound)
		return;

	GetCamera(&cx,&cy);
	x>>=FIXSHIFT;
	y>>=FIXSHIFT;
	pan=(x-cx)*2;
	vol=-((x-cx)*(x-cx)+(y-cy)*(y-cy))/128;
	if(vol<-5000)
		return;	// too quiet to play
	GoPlaySound(snd,pan,vol,(byte)flags,priority);
}

void MakeNormalSound(int snd)
{
	if(!soundAvailable)
		return;

	if(!opt.sound)
		return;

	GoPlaySound(snd,0,0,SND_MAXPRIORITY|SND_CUTOFF|SND_ONE,MAX_SNDPRIORITY);
}