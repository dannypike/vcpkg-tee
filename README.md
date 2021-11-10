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

## Usage

Pipe the output from `vcpkg` to `vcpkg-tee` and it will echo it to the console, e.g.:
```
vcpkg upgrade --no-dry-run --keep-going | vcpkg-tee
```

updates the Console window title and echoes the output from `vcpkg` back to the console at the same time.
