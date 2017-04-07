## 简介
重新设计一个内核

## 环境
* NASM
* gcc
* [bochs2.6.8](https://jaist.dl.sourceforge.net/project/bochs/bochs/2.6.8/bochs-2.6.8.tar.gz)

    配置参数
        ./configure --enable-debugger --enable-debugger-gui --enable-x86-debugger --enable-disasm --with-sdl2 --prefix=/yourprefix

## 首次运行
    git clone https://github.com/gumppur/gsykernel
    make disk
    
## 运行
    make run
    bochs的gui中添加断点命令：pb 0x7c00
    
## 注意
需要修改 tools/my.bochsrc 中的路径


## 内存分布
