import requests
from bs4 import BeautifulSoup
import pandas as pd

url = 'https://pogoda-service.ru/archive_gsod_res.php?station=260630&datepicker_beg=01.09.2020&datepicker_end=01.09.2024'
response = requests.get(url)
response.encoding = 'utf-8'
bs = BeautifulSoup(response.text, 'lxml')

table = bs.find('table', class_='table_res')

all_tb = table.find_all('tbody')
data_tbody = None
for tbody in all_tb:
    rows = tbody.find_all('tr')
    if len(rows) > 0 and any(row.find_all('td') for row in rows):
        data_tbody = tbody
        break

data = []
rows = data_tbody.find_all('tr')
for row in rows:
    cells = row.find_all(['td'])
    row_data = [cell.get_text(strip=True) for cell in cells]

    with open("weather_data.txt", 'a') as file:
        for i in range(len(row_data)):
            if i == 1 or i == 2 or i == 3 or i == 7:
                file.write(row_data[i])
                file.write(' ')
        #file.write('\n')

print(row_data)

    
