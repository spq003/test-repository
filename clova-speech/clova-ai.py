import pyaudio
import wave
import keyboard
import os
import json
import requests
import urllib


def record_audio(file_path):
    FORMAT = pyaudio.paInt16
    CHANNELS = 1
    RATE = 44100
    CHUNK = 1024

    audio = pyaudio.PyAudio()
    stream = audio.open(format=FORMAT, channels=CHANNELS,
                        rate=RATE, input=True,
                        input_device_index=2,
                        frames_per_buffer=CHUNK)
    print("Recording... Press Enter to stop.") #어떤 방식으로 녹음할지는 아이디어 필요
    frames = []

    while True:
        data = stream.read(CHUNK)
        frames.append(data)
        if keyboard.is_pressed('enter'):
            break
    print("Recording finished.")
    stream.stop_stream()
    stream.close()
    audio.terminate()
    
    with wave.open(file_path, 'wb') as wf:
        wf.setnchannels(CHANNELS)
        wf.setsampwidth(audio.get_sample_size(FORMAT))
        wf.setframerate(RATE)
        wf.writeframes(b''.join(frames))


# 전송 용량 줄이기 위한 aac 변환 작업
def convert_wav_to_aac(input_path, output_path):
    import subprocess
    # FFmpeg 명령어로 WAV를 AAC로 변환
    command = [
        'ffmpeg',              #ffmpeg 설치 필요...
        '-i', input_path,      # 입력 파일
        '-c:a', 'aac',         # AAC 코덱 사용
        '-b:a', '192k',        # 비트레이트 (192kbps, 필요에 따라 조정)
        output_path            # 출력 파일
    ]
    # subprocess를 이용해 FFmpeg 명령어 실행
    try:
        subprocess.run(command, check=True)
        print(f"파일 변환 성공: {output_path}")
    except subprocess.CalledProcessError as e:
        print(f"변환 중 오류 발생: {e}")
    return output_path


def clova_STT(file_path):
    INVOKE_URL = os.environ.get("STT_INVOKE_URL")
    SECRET_KEY = os.environ.get("STT_SECRET_KEY")

    request_header = {
            'Accept': 'application/json;UTF-8',
            'X-CLOVASPEECH-API-KEY': SECRET_KEY
    }
    request_body = {
            'language': 'ko-KR',
            'completion': 'sync',
            # 'callback': 'none',
            # 'userdata': 'none',
            # 'wordAlignment': 'none',
            # 'fullText': 'none',
            # 'forbiddens': 'none',
            # 'boostings': 'none',
            'diarization': {"enable": "false"},
            # 'sed': 'none',
    } # json.dumps(request_body, ensure_ascii=False).encode('UTF-8')
    recoding_file = {
        'media': open(file_path, 'rb'),
        'params': (None, json.dumps(request_body, ensure_ascii=False).encode('UTF-8'), 'application/json')
    }
    response = requests.post(headers=request_header, url=INVOKE_URL + '/recognizer/upload', files=recoding_file)
    return response.json().get("text")


# AI·NAVER API의 Clova Voice 서비스 가입 필요.
def clova_TTS(tts_str, speaker, save_path):
    CLOVA_VOICE_API_KEY_ID = os.environ.get("CLOVA_VOICE_API_KEY_ID")
    CLOVA_VOICE_API_KEY = os.environ.get("CLOVA_VOICE_API_KEY")
    URL = "https://naveropenapi.apigw.ntruss.com/tts-premium/v1/tts"

    request_header = {
        'X-NCP-APIGW-API-KEY-ID': CLOVA_VOICE_API_KEY_ID,
        'X-NCP-APIGW-API-KEY': CLOVA_VOICE_API_KEY,
        'Content-Type': 'application/x-www-form-urlencoded'
    }
    request_body = {
        "speaker": speaker,
        "volume": "0",
        "speed": "-1",
        "pitch": "0",
        "text": tts_str,
        "format": "mp3"
    }
    response = requests.post(url=URL, headers=request_header, data=request_body)

    path = save_path + ".mp3"
    if(response.status_code == 200):
        with open(path, "wb") as f:
            f.write(response.content)
    else:
        print(f"실패: {response.text}")
        return -1
    print(f"TTS 생성: {path}")
    return path

if __name__ == '__main__':
    text = "test"
    clova_TTS(text, "nkyuwon", text)