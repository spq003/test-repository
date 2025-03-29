import os
import urllib.parse
import urllib.request
import requests
import xml.etree.ElementTree as xmlET
from dotenv import load_dotenv

load_dotenv()

# 네이버 오픈 API
# [GET] [JSON, XML] 네이버 검색의 이미지 검색 결과를 반환합니다.
# https://openapi.naver.com/v1/search/image
# https://openapi.naver.com/v1/search/image.xml

class ClovaSpeechClient:
    client_id = os.environ.get("CLIENT_ID")
    client_secret = os.environ.get("CLIENT_SECRET")

    def get_image(self, name, save_path):
        params = {
            'query': name,
            'display': "1",
        }
        query_string = urllib.parse.urlencode(params)
        url = "https://openapi.naver.com/v1/search/image.xml?" + query_string
        urlRequest = urllib.request.Request(url)
        urlRequest.add_header("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36")
        urlRequest.add_header("X-Naver-Client-Id", self.client_id)
        urlRequest.add_header("X-Naver-Client-Secret", self.client_secret)
        
        response = urllib.request.urlopen(urlRequest)
        res_code = response.getcode()
        if(res_code == 200):
            response_body = response.read().decode('UTF-8')
        else:
            print("Error Code: " + res_code)
            return -1
        
        img_url = xmlET.fromstring(response_body).find('channel/item/link').text

        img_res = requests.get(img_url, stream=True)
        # img_res.raise_for_status()
        with open(save_path, "wb") as file:
            for chunk in img_res.iter_content(1024):
                file.write(chunk)


res = ClovaSpeechClient().get_image(
    name = "성경", 
    save_path = os.path.dirname(os.path.realpath(__file__)) + "/" + "img.jpg"
)
print(res)
    