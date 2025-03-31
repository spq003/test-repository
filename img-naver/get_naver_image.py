import os
import urllib.parse
import urllib.request
import requests
import xml.etree.ElementTree as xmlET
from dotenv import load_dotenv

load_dotenv()
client_id = os.environ.get("CLIENT_ID")
client_secret = os.environ.get("CLIENT_SECRET")

def get_naver_image(name, save_path):
    params = {
        'query': name,
        'display': "5",
    }
    query_string = urllib.parse.urlencode(params)
    url = "https://openapi.naver.com/v1/search/image.xml?" + query_string
    urlRequest = urllib.request.Request(url)
    urlRequest.add_header("X-Naver-Client-Id", client_id)
    urlRequest.add_header("X-Naver-Client-Secret", client_secret)
    
    response = urllib.request.urlopen(urlRequest)
    res_code = response.getcode()
    if(res_code == 200):
        response_body = response.read().decode('UTF-8')
    else:
        print("Error Code: " + res_code)
        return -1

    img_urls = xmlET.fromstring(response_body).findall('channel/item/link')
    
    for i in range(5):
        # ext = img_urls[i].text[-3:] //확장자 관계없이 jpg로 모두 열리는 듯
        # if(not(ext == "jpg" or ext == "png" or ext == "jpeg")):
        #     ext = "jpg"
        my_save_path = save_path + ".jpg"

        img_res = requests.get(img_urls[i].text, stream=True)

        with open(my_save_path, "wb") as file:
            for chunk in img_res.iter_content(1024):
                file.write(chunk)
            try:
                f = open(my_save_path, "rt")
                c = f.readlines()
                print(c)
                continue
            except:
                f.close()
                return img_res


res = get_naver_image(
    name = "식칼", 
    save_path = os.path.dirname(os.path.realpath(__file__)) + "/" + "img"
)
print(res)