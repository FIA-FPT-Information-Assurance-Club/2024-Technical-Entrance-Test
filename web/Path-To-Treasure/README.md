# WEB - Path to Treasure - 500 point
## Description:

Captain Jack Sparrow is going to the island containing the treasure. However, he encountered a problem: he had to pass 3 missions to reach that treasure before Hector Barbossa. Help him pass the quest and reach the treasure first.

Mission:  [https://pathmission.fiahackingisfun.id.vn](https://pathmission.fiahackingisfun.id.vn/)

## Skills Required

 - Có kĩ năng Python cơ bản
 - Có kĩ năng Linux cơ bản
 - Có khả năng research lỗ hổng
 - Biết cách dùng BurpSuite

## Application Overview

![!\[\[1.png\]\]](assets/1.png)

### Analysis

Khi truy cập vào trang web thì ta thấy một thông báo rằng "**DO YOU WANT TO BECOME A ROBOT?**", Điều này có nghĩa là gì???
Khi mà ta thu thập thông tin của một trang web thì việc đầu tiên ta có thể kiểm tra là file **robots.txt** - [Read More](https://developers.google.com/search/docs/crawling-indexing/robots/intro)
Sau khi duyệt đến `robots.txt` thì ta có thể thấy
![!\[\[2.png\]\]](assets/2.png)
Một đường dẫn ta bị Disallow "**/s3cr3t-p4g3**" 
Truy cập vào đường dẫn trên
![!\[\[3.png\]\]](assets/3.png)
=> Trả về lỗi "**You are must be a HACKER-1337 to access this page!!!**" => Có nghĩa là trang web này đang kiểm tra HTTP Header User-Agent có phải là **HACKER-1337** không
Sửa lại Header và gửi request
![!\[\[4.png\]\]](assets/4.png)

### Begin solve the mission
#### Mission 1

![!\[\[5.png\]\]](assets/5.png)
Trong mission này, có thể thấy được đoạn mã kiểm tra đầu vào là:
* Phải bắt đầu với `fia`
* Và kết thúc không phải là `/flag`
* Và cuối cùng đường dẫn trả về phải là `/flag`

Giờ ta sẽ thử một số payload
Với `/fia/../../../../../flag/aa` 
![!\[\[6.png\]\]](assets/6.png)
Nếu thay `aa` thành `..` 
![!\[\[7.png\]\]](assets/7.png)
Kết hợp 2 điều trên ta được một payload
`/fia/../../../../../flag/aa/..`
![!\[\[8.png\]\]](assets/8.png)

#### Mission 2

![!\[\[9.png\]\]](assets/9.png)
Mission này sẽ xóa toàn bộ kí tự `../` nhiên nhiêu nếu ta dùng payload như mission 1 thì sẽ như thế nào
`/flag/aa/..`
![!\[\[10.png\]\]](assets/10.png)
=> Vậy là với payload giống với mission 1 thì ta đã hoàn thành mission 2

#### Mission 3

![!\[\[11.png\]\]](assets/11.png)
Mission này sẽ kiểm tra đầu vào xem có `../` hoặc `/flag` không
Để vượt qua mission này cũng rất đơn giản đó là............dùng lại payload của mission 2 :v
`/flag/aa/..`
![!\[\[12.png\]\]](assets/12.png)

#### FLAG
![!\[\[13.png\]\]](assets/13.png)
```
FLAG: FIA{Y0u_h4v3_5ucceSSfully_c0mplEted_All_m1sSiOns-57656c636f6d6520746f20464941}
```

Bài này thật sự quá dễ phải không nào =)))))
