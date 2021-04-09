#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2020-08-03 21:48:50
# @Author  : Lewis Tian (taseikyo@gmail.com)
# @Link    : github.com/taseikyo
# @Version : Python 3.8.5

import os
import requests
from bs4 import BeautifulSoup as soup

STAR_REPOS = []


def get_star(uname="", url=""):
    if not uname:
        return

    url = url or f"https://github.com/{uname}?tab=stars"
    headers = {
        "Upgrade-Insecure-Requests": "1",
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.61 Safari/537.36",
    }
    r = requests.get(url, headers=headers)
    if r.status_code != 200:
        return
    soup_obj = soup(r.text, "html5lib")

    repos = soup_obj.find_all("div", {"class": "d-inline-block"})
    local_star_repos = []
    for repo in repos:
        h3 = repo.h3
        if h3:
            repo_name = h3.a.text.strip().replace(" ", "")
            local_star_repos.append(repo_name)

    # 如下注释，无法通过 next_url 判断最后一页，因此通过比较来判断是否回头
    for tmp in STAR_REPOS:
        if local_star_repos[0] == tmp[0]:
            return
        else:
            continue

    STAR_REPOS.append(local_star_repos)
    print(local_star_repos)
    # 这里会死循环，到最后一页，这里得到的 url 是 previous
    next_urls = soup_obj.find_all("a", {"class", "BtnGroup-item"})
    if next_urls:
        get_star(uname, next_urls[-1]["href"])


if __name__ == "__main__":
    get_star("taseikyo")
    print(STAR_REPOS)
