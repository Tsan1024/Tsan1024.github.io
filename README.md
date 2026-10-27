# Tsan1024

一个使用 Astro 和标准 Markdown 构建的极简个人博客。

## 写作

文章位于 `src/content/blog/`，每篇文章是一个 `.md` 文件：

```md
---
title: "文章标题"
description: "一句话摘要"
pubDate: 2026-08-27
tags: [Astro, GitHub]
draft: false
---

正文从这里开始。
```

## 收藏

收藏位于 `src/content/bookmarks.md`，新条目放在最上方。添加第一篇时删除“暂无收藏。”：

```md
## [文章标题](https://example.com/article)

作者或来源 · 收藏于 YYYY-MM-DD

两三句自己的点评。
```

收藏展示在 `/bookmarks/`，不进入文章归档和文章 RSS。

## 本地预览

```sh
npm install
npm run dev
```

## 发布

推送到 `master` 分支后，GitHub Actions 会自动构建并发布到 GitHub Pages。
