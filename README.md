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
url: "https://example.com/article"
author: "作者或来源"
topic: "AI 基础"
date: 2026-10-27
---

两三句自己的点评。
```

同一 `topic` 自动归到同一书架，新主题自动增加书架；每层最多 12 本，放满后自动增加一层。收藏按日期倒序排列，书脊、编号书目、计数、原文入口和 List 视图均自动生成；点击书脊或书目直接显示点评，不需要找封面图或重复维护链接。编号书单默认收起，可通过“展开书单／收起书单”切换；新增收藏自动出现在书单中。

收藏展示在 `/bookmarks/`，不进入文章归档和文章 RSS。无需 JavaScript 也可用书架和书本的展开功能；Library / List 切换在 JavaScript 可用时启用。

## 产品

导航中的 Products 展示在 `/products/`。每个产品是 `src/content/products/` 下的一个 Markdown 文件，文件名对应详情页地址（例如 `my-tool.md` → `/products/my-tool/`）：

```md
---
title: "产品名称"
description: "一句话介绍产品解决的问题"
descriptionEn: "A short English introduction."
url: "https://example.com"
source: "https://github.com/username/repo"
tags: [AI, 工具]
order: 0
draft: false
---

介绍产品的功能、使用场景和上手方式。
```

列表优先显示 `descriptionEn` 英文摘要，未填写时显示中文摘要；详情正文可以按英文、中文的顺序撰写。下载类产品可设置 `download: true`，将入口按钮显示为 Download。

`url`（产品入口）、`source`（源码）和 `tags` 均可省略；`order` 越小越靠前，默认为 0。`draft: true` 的产品不会出现在列表或生成详情页。目录中的 `example.md` 是草稿模板，复制并修改后设为 `draft: false` 即可发布。产品不进入文章归档和 RSS。

## 本地预览

```sh
npm install
npm run dev
```

## 发布

推送到 `master` 分支后，GitHub Actions 会自动构建并发布到 GitHub Pages。
