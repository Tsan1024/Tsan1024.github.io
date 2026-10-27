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

每条收藏是 `src/content/bookmarks/` 下一个 Markdown 文件：

```md
---
title: "文章标题"
coverTitle: "简短书封标题" # 可选，省略时使用完整标题
url: "https://example.com/article"
author: "作者或来源"
topic: "AI 基础"
date: 2026-10-27
---

两三句自己的点评。
```

同一 `topic` 自动归到同一书架，新主题自动增加书架。收藏按日期倒序排列，书封、计数、原文入口和 List 视图均自动生成；不需要找封面图或重复维护链接。

收藏展示在 `/bookmarks/`，不进入文章归档和文章 RSS。无需 JavaScript 也可用书架和书本的展开功能；Library / List 切换在 JavaScript 可用时启用。

## 本地预览

```sh
npm install
npm run dev
```

## 发布

推送到 `master` 分支后，GitHub Actions 会自动构建并发布到 GitHub Pages。
