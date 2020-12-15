> @Date    : 2020-11-06 10:48:00
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# Create a Git Diff in Markdown

> 原文：https://blog.alispit.tel/create-a-git-diff-in-markdown/ 20 October, 2020

One of my favorite blogging tips is using diff formatting in GitHub flavored markdown. I use this to show what has changed in code snippets. This works for code snippets in most markdown packages and on Dev.to.

If I wanted to show that I was changing a function from one thing to another, I could add a snippet that looks like this!

```diff
function addTwoNumbers (num1, num2) {
-  return 1 + 2
+  return num1 + num2
}
```

First, instead of specifying the programming language, use `diff` after the backticks. Then at the beginning of any lines of code you want to show as removed, add a `-`. At the beginning of any lines of code you want to show as added, add a `+`.

The code would look like this:

```
\`\`\`diff
function addTwoNumbers (num1, num2) {
-  return 1 + 2
+  return num1 + num2
}
\`\`\`
```

I have used this in tons of my coding tutorials, such as [this](https://welearncode.com/beginners-guide-react/) one. It makes it a lot easier for readers to see what is changing from snippet to snippet.
