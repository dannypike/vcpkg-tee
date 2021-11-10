# vcpkg-tee

___WINDOWS ONLY___

TL;DR - Parses the output from vcpkg to display some progress feedback in the Command Prompt title bar.

When multiple packages are being built, this program monitors the output from `vcpkg`, looking for lines like this:
```
Starting package 1/9: a-package-name
```
and updates the Windows Console window title bar in real time to say things like this:
```
[1/9 - a-package-name] Original Title Text
```
