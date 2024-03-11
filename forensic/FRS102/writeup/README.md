# [FORENSIC] FRS102

---

**Author**: `Evil Duck`

**Difficulty**: `Medium`

**Flag**: `FIA{TcP_C4tch_Th4m_4ll_W3ll_Done_63b0226c3a70b9ea967616e11a68e}`

### Description

> Welcome to wireshark
> 

### Objective

> Knowing TCP stream, network flow and some basic linux, crypto encryption
> 

---

# Solution

## Information Gathering

- Open wireshark and see what we got here

<p align="center">
  <img src="https://github.com/P5ySm1th/CTF/assets/100250271/7064bdf3-84e6-4e80-910f-7527fbf94008">
</p>

- It seems like there are a lot of TCP stream connection between the two IP: `192.168.112.161` and `192.168.112.133`


- Now using `Prototcol Hierachy` to see the full protocol between every single packet in pcap file
 
<p align="center">
  <img src="https://github.com/P5ySm1th/CTF/assets/100250271/0fe0a6a8-d0b7-4a87-ba63-f2f50278ae62">
</p>

- And `Conversation` also to see if there is another IP

<p align="center">
  <img src="https://github.com/P5ySm1th/CTF/assets/100250271/dcc3bb8b-77a3-4173-a329-236021239643">
</p>


## Solver

- So in this challenge, just typically click on the `TCP stream` to see the full conversation between those IP.

<p align="center">
  <img src="https://github.com/P5ySm1th/CTF/assets/100250271/ff18d931-3e7c-4aad-8941-25ba0aa2bc9a">
</p>

- The picture upper showing that this must be a reverse shell from the attacker using to control the victim's device. You can see that there are a lot of command, such as `whoami`, `groups`, `id`,etc

- In `stream 9` you can clearly see that the hacker try using the encryption tool for encrypt some file

<p align="center">
  <img src="https://github.com/P5ySm1th/CTF/assets/100250271/e6aebb5b-659f-45e4-b661-d904522d6d98">
</p>

- `Stream 10` will make you see it clearer

<p align="center">
  <img src="https://github.com/P5ySm1th/CTF/assets/100250271/df344287-389d-4a19-9dd0-d1098c495593">
</p>

- So it encrypt all file in the `Document` folder, and in `stream 11`, luckily the hacker show the `malicious code`

<p align="center">
  <img src="https://github.com/P5ySm1th/CTF/assets/100250271/8814ffee-c812-4d69-ac8c-6f5cfbfc01d8">
</p>

- Basically, there are `2 stages of encryption`, first one is use with `AES with CBC mode`, second stage is use `xor` and then conver it to `hex`

- So from `AES`, it assign `key` and `IV`, you can find it through `main` function, those can be retrived from `environment variable`. Take a look closer from `TCP stream 8`

<p align="center">
  <img src="https://github.com/P5ySm1th/CTF/assets/100250271/35b10330-93b2-4c27-bf0a-9798861a7a24">
</p>

- We can easily get the Key and IV,and then xoring again with the key.

- We can easily do that in `cyberchef` with 2 files in the `Document` folder and here is the result: 

<p align="center">
  <img src="https://github.com/P5ySm1th/CTF/assets/100250271/3395ec81-2a2f-48c9-9dd2-66853597a945">
</p>  

P/s: It should be add tag easy tho :D