# Sound-Bank-Compiler
Sound Bank Compiler

SBC gets on input a text file. Each line of the text could have 2 parameters when the the line is not empty or commented out. First word is a parameter name the second is value.
One file could include others.

1)	#include C:\DIR\name.txt

Includes file name.txt inside this file

2)	end

Terminates inclusion

3)	'My Comment

All collments starts with character '

Example:

<file bank.txt>
[CODE]
'The first file
#include bank2.txt	
end	
[/CODE]

<file bank2.txt>

'The second file
myvariable foo	'myvariable equals foo
end	


4) New objects creation starts with object type followed by objects name. The objects declaration is required before using

5) Types

wave		the waveform
keymap		keyboard map
envelope	envelope form
sound		the sound 
instrument	the instrument
bank		the sound bank

5.1 WAVE Object

Has only one variable 'use' and the sample's file name as value.

Example:
-----------------------------------------------------------
wave yahhoo
use	"c:\smpls\yaho.wav"
end
-----------------------------------------------------------

5.2	KEYMAP Object

Defaults:

velocityMin	=	UC(1);
velocityMax	=	UC(127);
keyMin		=	UC(1);
keyMax		=	UC(127);
keyBase		=	UC(60);
detune		=	SC(0);

User defined values:

velocityMin	Minimum press force
velocityMax	Maximum press force
keyMin		Lover key number
keyMax		Higher key number
keyBase		Base tone frequency
detune		Tunning

Example
-----------------------------------------------------------
keymap 		key1
	velocityMin	10
	velocityMax	100
	keyMin		0
	keyMax		100
	keyBase		12
	detune		0
end
-----------------------------------------------------------

5.3	ENVELOPE Object

Default variables:

attackTime		=	S32(0);	
attackVolume	=	UC(AL_VOL_FULL);
decayTime		=	S32(0);
decayVolume		=	UC(AL_VOL_FULL); 
releaseTime		=	S32(0);

User defined variables:

attacktime
attackvolume
decaytime
decayvolume
releasetime

Example
-----------------------------------------------------------
envelope 		env1
	attacktime		1000
	attackvolume	100
	decaytime		1000
	decayvolume		50
	releasetime		2000
end
-----------------------------------------------------------

5.4 SOUND Object

Default variables:

samplePan		= SC(AL_PAN_CENTER);
sampleVolume	= UC(AL_VOL_FULL);
flags			= UC(0);

User defined variables:

envelope		Name of envelope
keymap			Name of keyboard's map
use				The waveform
samplePan		Sample's panorama
sampleVolume	Sample's volume
flags			Flags

ПРИМЕР
-----------------------------------------------------------
sound 		hi
	envelope	env1
	keymap 		kbd1
	use			yahhoo
	samplePan	100
	sampleVolume	100
	flags		0
end
-----------------------------------------------------------

5.5 INSTRUMRNT Object

Default variables:

volume		=UC(AL_VOL_FULL);	/* overall volume for this instrument */
pan			=SC(AL_PAN_CENTER); /* 0 = hard left, 127 = hard right */
priority	=SC(5);	/* voice priority for this instrument */
flags		=0;
tremType	=0;	/* the type of tremelo osc. to use */
tremRate	=0;	/* the rate of the tremelo osc. */
tremDepth	=0;	/* the depth of the tremelo osc */
tremDelay	=0;	/* the delay for the tremelo osc */
vibType		=0;	/* the type of tremelo osc. to use */
vibRate		=0;	/* the rate of the tremelo osc. */
vibDepth	=0;	/* the depth of the tremelo osc */
vibDelay	=0;	/* the delay for the tremelo osc */
bendRange	=S16(200);	/* pitch bend range in cents */
soundCount	=0;	/* number of sounds in this array */

User defined values

volume		The volume
pan			The panorama
priority	The priority value
flags		Flags
tremType	Tremolo type
tremRate	Tremolo speed
tremDepth	Tremolo depth
tremDelay	Tremolo length
vibType		Vibrato type
vibRate		Vibrato frequency
vibDepth	Vibrato depth
vibDelay	Vibrato duration
bendRange	Pitch percents
sound		Sound of this instrument

Example
-----------------------------------------------------------
instrument flute
	volume		100
	pan	120
	priority	5
	flags		0
	tremType	1
	tremRate	100
	tremDepth	10
	tremDelay	0
	vibType		1
	vibRate		100
	vibDepth	10
	vibDelay	12
	bendRange	200
	sound		lo
	sound		hi
end
-----------------------------------------------------------

5.6	BANK Object

Default variables:

instCount = 0;	/* number of programs in this bank */
flags = 0;
pad = 0;
sampleRate = S32(44100);	/* e.g. 44100, 22050, etc... */

user defined variables:

flags		Flags word
samplerate	Infrequence of discretization
percussion	Percussion instrument
instrument	Instrument

ПРИМЕР
-----------------------------------------------------------
bank stings2
	flags	5
	samplerate	32000
	percussion	baraban1
	instrumrnt	string1
	instrument	string2
	instrument	horus
end
-----------------------------------------------------------
