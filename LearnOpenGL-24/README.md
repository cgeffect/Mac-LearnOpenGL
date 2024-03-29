# 24 模型加载

修改 util/filesystem.h 中 logl_root 的值为工程的根目录

编译assimp静态库
下载源码 https://github.com/assimp/assimp/archive/refs/tags/v5.3.1.zip

2. 编译静态库
cmake -DBUILD_SHARED_LIBS=OFF -DCMAKE_OSX_ARCHITECTURES="arm64" -DCMAKE_OSX_DEPLOYMENT_TARGET="11.0" -DCMAKE_INSTALL_PREFIX="./deploy" .. && make -j24 && make install

DCMAKE_OSX_ARCHITECTURES="arm64" 参数可以设置多个 DCMAKE_OSX_ARCHITECTURES="arm64;x86_64;i386" 但是多个架构都支持, 库比较大, github上传限制100M
