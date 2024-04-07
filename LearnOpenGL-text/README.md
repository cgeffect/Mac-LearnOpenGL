# 24 字体渲染

修改 util/filesystem.h 中 logl_root 的值为工程的根目录

编译freetype静态库
git clone https://gitlab.freedesktop.org/freetype/freetype.git
git clone https://gitlab.freedesktop.org/freetype/freetype-demos.git

2. 编译静态库
DCMAKE_OSX_ARCHITECTURES="arm64" 参数可以设置多个 DCMAKE_OSX_ARCHITECTURES="arm64;x86_64;i386" 但是多个架构都支持, 库比较大, github上传限制100M

编译freetype
    cd freetype-2.13.2
    cmake -E remove CMakeCache.txt
    cmake -E remove_directory CMakeFiles
    cmake -E make_directory build    
    cmake -D FT_DISABLE_ZLIB=TRUE -D FT_DISABLE_BZIP2=TRUE -D FT_DISABLE_PNG=TRUE -D FT_DISABLE_HARFBUZZ=TRUE -D FT_DISABLE_BROTLI=TRUE -DCMAKE_INSTALL_PREFIX="./deploy" -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64" -DCMAKE_OSX_DEPLOYMENT_TARGET="11.0" ..

注意: 头文件引入目录要到freetype2
"$(SRCROOT)/LearnOpenGL/third/freetype-2.13.2/include/freetype2"


官方教程
https://freetype.org/freetype2/docs/tutorial/
