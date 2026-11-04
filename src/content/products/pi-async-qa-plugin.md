---
title: "Pi Async Q&A Plugin"
description: "主任务继续，提问不用等。为 Pi 添加异步问答能力的插件。"
descriptionEn: "Ask questions while your main task keeps running. An asynchronous Q&A plugin for Pi."
source: "https://github.com/Tsan1024/pi-async-qa-plugin"
tags: [Pi, AI, Developer Tools]
order: 1
draft: false
---

<section lang="en" aria-label="English introduction">

Pi Async Q&A Plugin lets you ask questions while Pi's main agent keeps working. Select Async through `/mode` to receive separate answers based on the conversation context available when you ask. Side answers are read-only: they cannot inspect files, run tools, or change the main task. When the main agent is idle, input follows Pi's normal conversation flow. Install it through Pi's native package system, with no changes to Pi itself.

</section>

---

<section lang="zh-CN" aria-label="中文介绍">

Pi Async Q&A Plugin 让你在 Pi 主 Agent 执行任务时继续提问。通过 `/mode` 切换到 Async，问题会基于提交时的对话上下文获得独立回答，主任务继续运行。旁路问答只读，不会读取文件、调用工具或修改主任务；主 Agent 空闲时，输入仍进入正常对话。插件通过 Pi 原生包管理安装，无需修改 Pi 本身。

</section>
