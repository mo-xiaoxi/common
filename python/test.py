#!/usr/bin/env python
# coding=utf-8
import os
import re
import time
import requests
import threading

MAIN_PAGE = "http://cl.romcl.org/thread0806.php?fid=16"
PAGE_ENCODING = "gbk"
DATE = time.strftime("%Y-%m-%d", time.localtime(time.time()))

# 入口
def main():
    if os.path.exists(DATE):
        os.rmdir(DATE)
    os.mkdir(DATE)
    os.chdir(DATE)
    start()

# 从主页提取所有最新帖子的标题和URL
# 每篇帖子分配一个线程，交由onePage处理
def start():
    threads = []
    mainText = downHTML(MAIN_PAGE, PAGE_ENCODING)
    for url, title in extractPairs(mainText):
        print title
        t = threading.Thread(target = onePage, args = (title, "http://cl.romcl.org/"+url))
        threads.append(t)
    for t in threads:
        t.start()
    for t in threads:
        t.join()

# 下载页面内容
def downHTML(url, encoding):
    try:
        r = requests.get(url)
        r.encoding = encoding
        return r.text
    except:
        return ""

# 从页面中提取所有 (标题，地址)
def extractPairs(text):
    return re.findall(r'<h3><a href="(.+?)" target="_blank" id=""><font color=green>(.+?)</font></a></h3>', text)

# 线程函数
# 为每篇帖子创建一个子文件夹，下载该帖所有图片并保存在子文件夹中
def onePage(title, url):
    os.mkdir(title)
    n = 1
    for img in extractImgs(downHTML(url, PAGE_ENCODING)):
        print "[img]", img
        downSaveImg(title+"/"+str(n)+".jpg", img)
        n += 1

# 提取文本中所有图片地址
# 倒序正则，匹配效果好
def extractImgs(text):
    text = text[::-1]
    result = []
    for i in re.findall(r'gpj\..+?//:s?ptth', text):
        result.append(i[::-1])
    return result

# 下载并保存图片
def downSaveImg(filename, url):
    with open(filename, "wb") as f:
        f.write(requests.get(url).content)

if __name__ == "__main__":
    main()

