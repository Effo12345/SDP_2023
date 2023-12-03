#include "include/soundmanager.hpp"

/**
 * @author bakar-bst
 * 
 * Construct a new SoundManager instance and invoke the necessary Windows API
 * features to enable XAudio sound playback
 **/
SoundManager::SoundManager() {
    // BasePath defaults to same directory as executable
    BasePath = "";

    // Initialize the COM library
    hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    if (FAILED(hr))
        std::cout << hr;

    // Start XAudio interface
    pXAudio2 = nullptr;
    if (FAILED(hr = XAudio2Create(&pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR)))
        std::cout << hr;

    // Create device to play sound through
    pMasterVoice = nullptr;
    if (FAILED(hr = pXAudio2->CreateMasteringVoice(&pMasterVoice)))
        std::cout << hr;
}

/**
 * @author Ethan Rosati
 * 
 * Stop all sounds if the SoundManager goes out of scope or is deleted. Prevents
 * accidental sound bleedover between levels
 **/
SoundManager::~SoundManager() {
    stopSounds();
}

/**
 * @author bakar-bst
 * 
 * Plays the audio file with specified volume and can be looped
 * 
 * @param path Path to .wav file to be played relative to BasePath
 * @param volume Volume of sound on [0, 1]
 * @param ShouldLoop Whether the audio should repeat upon completion
 * @return Error code
 **/
int SoundManager::play(std::string path, float volume, bool ShouldLoop) {
    path = BasePath + "\\" + path;
    WAVEFORMATEXTENSIBLE wfx = { 0 };
    XAUDIO2_BUFFER buffer = { 0 };

    TCHAR* strFileName = new TCHAR[path.size() + 1];
    strFileName[path.size()] = 0;
    std::copy(path.begin(), path.end(), strFileName);

    // Open the file
    HANDLE hFile = CreateFile(
        strFileName,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (INVALID_HANDLE_VALUE == hFile)
        return HRESULT_FROM_WIN32(GetLastError());

    if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
        return HRESULT_FROM_WIN32(GetLastError());

    DWORD dwChunkSize;
    DWORD dwChunkPosition;

    //check the file type, should be fourccWAVE or 'XWMA'
    FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
    DWORD filetype;
    ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);

    if (filetype != fourccWAVE)
        return S_FALSE;

    FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
    ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
    FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);

    BYTE* pDataBuffer = new BYTE[dwChunkSize];
    ReadChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPosition);

    buffer.AudioBytes = dwChunkSize;  // size of the audio buffer in bytes
    buffer.pAudioData = pDataBuffer;  // buffer containing audio data
    buffer.Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer

    if (ShouldLoop) 
        buffer.LoopCount = XAUDIO2_LOOP_INFINITE;

    IXAudio2SourceVoice* pSourceVoice;

    if (FAILED(hr = pXAudio2->CreateSourceVoice(&pSourceVoice, (WAVEFORMATEX*)&wfx))) 
        std::cout << hr;
    if (FAILED(hr = pSourceVoice->SubmitSourceBuffer(&buffer))) 
        std::cout << hr;

    pSourceVoice->SetVolume(volume);

    if (FAILED(hr = pSourceVoice->Start(0)))
        std::cout << hr;

    activeSounds.push_back(pSourceVoice);

    return 0;
}

/**
 * @author bakar-bst
 * 
 * Finds and parses file data
 * 
 * @param hFile File struct including filepath
 * @param fourcc File type to read in
 * @param dwChunkSize Size of data chunk processed. Modified by reference
 * @param dwChunkDataPosition Filesystem pointer to chunk read location
 * @return Error code
 **/
HRESULT SoundManager::FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition) {
    HRESULT hr = S_OK;
    if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
        return HRESULT_FROM_WIN32(GetLastError());

    DWORD dwChunkType;
    DWORD dwChunkDataSize;
    DWORD dwRIFFDataSize = 0;
    DWORD dwFileType;
    DWORD bytesRead = 0;
    DWORD dwOffset = 0;

    while (hr == S_OK) {
        DWORD dwRead;
        if (0 == ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
            hr = HRESULT_FROM_WIN32(GetLastError());

        if (0 == ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
            hr = HRESULT_FROM_WIN32(GetLastError());

        switch (dwChunkType) {
        case fourccRIFF:
            dwRIFFDataSize = dwChunkDataSize;
            dwChunkDataSize = 4;
            if (0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
                hr = HRESULT_FROM_WIN32(GetLastError());
            break;

        default:
            if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
                return HRESULT_FROM_WIN32(GetLastError());
        }

        dwOffset += sizeof(DWORD) * 2;

        if (dwChunkType == fourcc) {
            dwChunkSize = dwChunkDataSize;
            dwChunkDataPosition = dwOffset;
            return S_OK;
        }

        dwOffset += dwChunkDataSize;

        if (bytesRead >= dwRIFFDataSize) 
            return S_FALSE;

    }
    return S_OK;
}

/**
 * @author bakar-bst
 * 
 * Reads in data from chunk and writes it to a buffer
 * 
 * @param hFile File target to read from
 * @param buffer Buffer in memory to write data to
 * @param buffersize Maximum permissable size of the buffer
 * @param bufferoffset Offset from start of file
 */
HRESULT SoundManager::ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset) {
    HRESULT hr = S_OK;
    if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, bufferoffset, NULL, FILE_BEGIN))
        return HRESULT_FROM_WIN32(GetLastError());

    DWORD dwRead;
    if (0 == ReadFile(hFile, buffer, buffersize, &dwRead, NULL))
        hr = HRESULT_FROM_WIN32(GetLastError());
    return hr;
}

/**
 * @author Ethan Rosati
 * 
 * Stop all currently playing sounds
 */
void SoundManager::stopSounds() {
    // Loop through all active voices and stop them
    for(IXAudio2SourceVoice* sound : activeSounds) {
        sound->Stop();
        sound->DestroyVoice();
    }

    // Then clear the array to make room for new sounds
    activeSounds.clear();
}