#pragma once
#include <xaudio2.h>
#include <iostream>
#include <string>
#include <vector>

#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'

/**
 * @author bakar-bst via StackExchange
 * @cite https://stackoverflow.com/a/72348537
 * 
 * Manages interfacing with Windows' XAudi2 API to play sounds in real time.
 * Supports short and long sounds as well as looping sounds. Inputs .wav files
 **/
class SoundManager {
    // Track the result of various operations for debugging
    HRESULT hr;

    // Pointers to manage audio interface
    IXAudio2* pXAudio2;
    IXAudio2MasteringVoice* pMasterVoice;

    HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition);
    HRESULT ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset);

    std::vector<IXAudio2SourceVoice*> activeSounds;
public:
    // Directory where all audio files (relevant to project) are stored
    // This will be prefixed on all files passed to the class
    std::string BasePath; 

    SoundManager();
    ~SoundManager();
    
    int play(std::string path, float volume = 1, bool ShouldLoop = false);
    void stopSounds();
};