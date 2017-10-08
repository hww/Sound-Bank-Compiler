/**********************************************************

	Sound Bank Compiller

 **********************************************************/


LPDIRECTSOUND lpDirectSound;

/**********************************************************

	Создаём PRIMARY sound buffer

 **********************************************************/

BOOL AppCreateBasicBuffer( LPDIRECTSOUND lpDirectSound, LPDIRECTSOUNDBUFFER *lplpDsb)
{
    
PCMWAVEFORMAT pcmwf;
DSBUFFERDESC dsbdesc;
HRESULT hr;

    // Set up wave format structure.
    
	memset(&pcmwf, 0, sizeof(PCMWAVEFORMAT));
    
		pcmwf.wf.wFormatTag = WAVE_FORMAT_PCM;
		pcmwf.wf.nChannels = 2;
		pcmwf.wf.nSamplesPerSec = 22050;
		pcmwf.wf.nBlockAlign = 4;
		pcmwf.wf.nAvgBytesPerSec = 
		pcmwf.wf.nSamplesPerSec * pcmwf.wf.nBlockAlign;
		pcmwf.wBitsPerSample = 16;
    
	// Set up DSBUFFERDESC structure.
    
	memset(&dsbdesc, 0, sizeof(DSBUFFERDESC)); // Zero it out.
	    dsbdesc.dwSize = sizeof(DSBUFFERDESC);
    
	// Need default controls (pan, volume, frequency).
    dsbdesc.dwFlags = DSBCAPS_CTRLDEFAULT; 
    
	// 3-second buffer.
    dsbdesc.dwBufferBytes = 3 * pcmwf.wf.nAvgBytesPerSec; 
    dsbdesc.lpwfxFormat = (LPWAVEFORMATEX)&pcmwf;
    
	// Create buffer.
    hr = lpDirectSound->lpVtbl->CreateSoundBuffer(lpDirectSound,
        &dsbdesc, lplpDsb, NULL);
    if(DS_OK == hr) {
        // Succeeded. Valid interface is in *lplpDsb.
        return TRUE;
    } else {
        // Failed.
        *lplpDsb = NULL;
        return FALSE;
    }
}

/**********************************************************

	Создаём PRIMARY sound buffer

 **********************************************************/

BOOL AppWriteDataToBuffer( 
							LPDIRECTSOUNDBUFFER lpDsb, 
							DWORD dwOffset, 
							LPBYTE lpbSoundData, 
							DWORD dwSoundBytes )
{
    LPVOID lpvPtr1;
    DWORD dwBytes1; 
    LPVOID lpvPtr2;
    DWORD dwBytes2;
    HRESULT hr;

    // Obtain write pointer.
    hr = lpDsb->lpVtbl->Lock(lpDsb, dwOffset, dwSoundBytes, &lpvPtr1, 
        &dwBytes1, &lpvPtr2, &dwBytes2, 0);
    
    // If DSERR_BUFFERLOST is returned, restore and retry lock.
    if(DSERR_BUFFERLOST == hr) {
        lpDsb->lpVtbl->Restore(lpDsb);
        hr = lpDsb->lpVtbl->Lock(lpDsb, dwOffset, dwSoundBytes,
            &lpvPtr1, &dwAudio1, &lpvPtr2, &dwAudio2, 0);
    }
    if(DS_OK == hr) {
        // Write to pointers.
        CopyMemory(lpvPtr1, lpbSoundData, dwBytes1);
        if(NULL != lpvPtr2) {
            CopyMemory(lpvPtr2, lpbSoundData+dwBytes1, dwBytes2);
        }
        // Release the data back to DirectSound.
        hr = lpDsb->lpVtbl->Unlock(lpDsb, lpvPtr1, dwBytes1, lpvPtr2, 
            dwBytes2);
        if(DS_OK == hr) {
            // Success.
            return TRUE;
        }
    }
    // Lock, Unlock, or Restore failed.
    return FALSE;
}


/**********************************************************

	Создаём PRIMARY sound buffer

 **********************************************************/

int open_sound()
{

	if(DS_OK == DirectSoundCreate(NULL, &lpDirectSound,NULL)) 
	{
		// Creation failed.
		// .
		printf("Can't create DIRRECT_SOUND object\n");
		return 0;
	}

	// Creation succeeded.
	lpDirectSound->lpVtbl->SetCooperativeLevel(lpDirectSound, hwnd, DSSCL_NORMAL);
	// .
	// . Place code to access DirectSound object here.
	// .







}