---
title: "Common git commands"
author: "Wenbo Lv"
date: "2024-06-05"
tags: ["git","coding","github"]
type: post
weight: 25
showTableOfContents: true
---

### View the git installation location

```
which git
```

### View the git installation version

```
git --version
```

###  Updating Git for Windows

```
git update-git-for-windows
```

### Setting up network proxy

```
git config --global http.proxy 'http://127.0.0.1:7890'
git config --global https.proxy 'http://127.0.0.1:7890'
```

### Setting default initial branch name to main

```
git config --global init.defaultBranch main
```

### View all git configuration information

```
git config --global --list
```

### Push local main to GitHub main and have local main track main on GitHub

```
git push --set-upstream origin main
# shorter form
git push -u origin main
# you only need to set upstream tracking once!
```

### Pull commits and don’t let it put you in a merge conflict pickle

```
git pull --ff-only
```

### Add a remote to existing local repo

```
git remote add origin [remote repo]
git remote --verbose
git remote show origin
```

### Reset the associated remote repository

```
git remote set-url origin [new remote repo url]
```

### Switch to a branch

```
git checkout [branch-name]
```

### Create a new branch and switch to that branch

```
git checkout -b [branch-name]
```

### Checking remote and branch tracking

```
git remote -v
git remote show origin
git branch -vv
```

### Check on the state of the Git world

```
git status
git log
git log --oneline
```
