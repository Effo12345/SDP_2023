// https://stackoverflow.com/questions/9961949/playsound-in-c-console-application


#pragma once
#include <xaudio2.h>
#include <iostream>
#include <string>
#include <vector>
#ifdef _XBOX 
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif

#ifndef _XBOX
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif

class SoundManager {
private:
    HRESULT hr;
    IXAudio2* pXAudio2;
    IXAudio2MasteringVoice* pMasterVoice;
    HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition);
    HRESULT ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset);

    std::vector<IXAudio2SourceVoice*> activeSounds;
public:
    SoundManager();
    int play(std::string path, float volume = 1, bool ShouldLoop = false); // plays the audio file with specified volume and can be looped
    std::string BasePath; // Directory where all audio files (relevant to project) are stored i.e if all audio files are stored in "D:\game" than set BasePath to "D:\game", this will be automatically added in path of every audio file
    void stopSounds();
};