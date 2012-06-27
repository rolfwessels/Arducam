# Arducam

# Install

Download the following
```
install http://nodejs.org/dist/v0.8.0/x64/node-v0.8.0-x64.msi
install http://www.python.org/ftp/python/2.7.2/python-2.7.2.amd64.msi
```

Ensure path is 

```
set PYTHON=c:\dev\Software\Python27\python.exe
set PATH=%PATH%;c:\Program Files\nodejs\
```

Then run in git clone directory

```
npm install -g node-gyp
npm install serialport2
npm install sf
node server.js
```
