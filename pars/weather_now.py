import requests
from bs4 import BeautifulSoup

url = "https://yandex.ru/pogoda/ru/saint-petersburg"
response = requests.get(url)
bs = BeautifulSoup(response.text, 'lxml')

temp = bs.find('p', class_='AppFactTemperature_content__Lx4p9')

print(f'Погода в Санкт-Петербурге сейчас: {temp.text}')
