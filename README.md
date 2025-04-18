this Chinese, Click to [English](https://github.com/GengGode/cvAutoTrack/blob/master/doc/README_en.md) 
# GenshinImpact AutoTrack DLL

通过图像匹配算法，从原神客户端中获取角色在地图上的位置的DLL动态链接库

[![GitHub version](https://badge.fury.io/gh/GengGode%2FcvAutoTrack.svg)](https://badge.fury.io/gh/GengGode%2FcvAutoTrack) [![Build status](https://ci.appveyor.com/api/projects/status/12csww8lg756kucu?svg=true)](https://ci.appveyor.com/project/GengGode/cvautotrack) ![convention](https://img.shields.io/badge/convention-__stdcall-orange.svg) ![platform](https://img.shields.io/badge/platform-Windows-blue.svg) ![](https://img.shields.io/badge/cpu-AMD64-purple.svg)

# 介绍 

#### [空荧酒馆原神地图手动更新/测试教程](doc/kyjg.md)

##### 联系 QQ群[717355752](https://jq.qq.com/?_wv=1027&k=YvH6TsM4)

### 不再内嵌预计算结果，首次运行将会在运行目录生成缓存xml
### 目前支持任意分辨率，以及手柄模式，但暂不支持小地图设置的【跟随视角】仅支持【锁定方向】
### 地图目前支持区域

| 原神版本 | 地图区域 | dll版本 |
| -------- | ------ | ------ |
|  1.0 |  蒙德、雪山、璃月   |   -   |
|   -  |  稻妻I、稻妻II、稻妻III(鹤观)、稻妻IIII(渊下宫)、璃月II(层岩)、璃月III(地下层岩)  |   -   |
|  3.0 |  须弥              | 6.1.51 |
|  3.1 |  须弥沙漠           | 6.4.17 |
|  3.4 |  千壑沙地           | 7.4.0  |

### 各版本所支持的功能

| 版本 | 键盘模式 | 手柄模式 | 分辨率支持列表 |
| -------- | ------ | ------ | ------ |
|  6.4.x |  √ | × |  1920x1080 |
|  6.5.39 |  √ | × |  1920x1080, 2560x1440, 2560x1080 |
|  6.5.92 |  - | - |  - |
|  7.0.1 |  √ | √(DX模式下不支持) |  16:9 系列(但不包括4K及以上), 21:9 系列, 以及1920*1080以下的所有分辨率 |
|  7.3.0 |  √ | √ |  √(有用户反馈5k 21:9无法使用，待测试） |
|  7.3.0 |  √ | √ |  √  |


## 新版本计划 7.x

- [x] 优化了派蒙检测算法 [派蒙检测2nd](doc/paimon_check.md)
- [ ] 添加对秘境中的角度和视野识别
- [ ] 实现无透明通道下的视野识别
- [x] 实现日志可控制不输出
- [ ] 添加定位的惯性加速度导航算法（见 dev-inrtial-position 分支）
- [ ] 添加定位的自动校准算法
- [ ] 支持任意地图区域
- [ ] 支持传入地图而非内嵌
- [x] 可选的嵌入预计算结果
- [x] 更高的匹配精度

# 如何使用

1. 下载编译好的动态链接库。
   - https://github.com/GengGode/cvAutoTrack/releases/
2. 装载动态链接库后，根据[函数手册](#函数手册)对相关函数进行调用或封装。
3. 部分语言的调用可参见 `impl` 文件夹内的调用示例。
4. 由于默认接口输出的是[天理坐标模型](天理坐标模型)的坐标，所以使用者需要根据自身地图坐标系与天理坐标模型之间的映射关系，设置世界中心以及缩放系数或者后期手动换算。

# 如何编译

1. 环境需求，[Visual Studio 2019 +](https://visualstudio.microsoft.com/zh-hans/vs/) 、[Opencv 4.5.0 static lib zip](https://github.com/GengGode/opencv450Release/releases/download/v1.0/Release.zip)
2. 安装 Visual Studio 2019 +
3. 创建 Opencv 库的环境变量，若不使用环境变量则需要手动修改 cvAutoTrack 项目的`附加包含目录`和`附加库目录`

    ``` $OpenCvDir = C:\projects\opencv\ ```
4. 下载 Opencv 4.5.0 static lib zip 并解压到任意目录

    ``` 7z x ./*.zip -y -o%OpenCvDir% ```
5. Clone 代码

   ``` Git Clone https://github.com/GengGode/cvAutoTrack ```

6. 进入项目文件夹解压资源文件

    ``` cd .\cvAutoTrack | 7z -x resource.zip ```
7. 编译项目

    ``` msbuild cvAutoTrack.sln ```

## 注意事项

- 目前只编译了 Windows x64 平台上的动态链接库（.dll），对于 Windows x86 或其它平台，如 Linux 平台（.so），需要下载源代码另行编译。
- 本项目借游戏画面的窗口截图进行图像处理算法以实现所有功能，其不会对游戏内存进行读写，因而不会有封号的风险，但效果也因此具备一定的局限。
- 项目仅在有限的条件下测试过，如需排查错误，强烈建议按照以下描述进行环境配置。
  - 原神客户端 > 右上角派蒙 > 设置 > 抗锯齿，设置为 `SMAA`
  - 原神客户端 > 右上角派蒙 > 设置 > 其他 > 小地图锁定，设置为 `锁定方向`

# 对于开发者

- 码云上的仓库：[https://gitee.com/Yu_Sui_Xian/yuanshen-auto-tracking-dll](https://gitee.com/Yu_Sui_Xian/yuanshen-auto-tracking-dll)
- Git上的仓库： [https://github.com/GengGode/cvAutoTrack](https://github.com/GengGode/cvAutoTrack)

## 项目结构

- **cvAutoTrack**，dll工程
- **doc**，文档及部分插图
- **impl**，部分语言的调用示例
    - **Cpp/TEST_cvAutoTrack_Cpp** C++调用
    - **CSharp/TEST_cvAutoTrack_CSharp** C#调用
    - **Python** Python调用


# 函数目录( [详细文档](https://github.com/GengGode/cvAutoTrack/blob/master/doc/%E5%87%BD%E6%95%B0%E6%89%8B%E5%86%8C.md) )

|              接口名称            |                                 接口功能                         |
| ------------------------------- | --------------------------------------------------------------- |
| `verison`                       | 获取Dll版本。                                                    |
| `init`                          | 初始化运行环境。                                                  |
| `uninit`                        | 卸载初始化时所占用的内存。                                          |
| `startServe`                    | （未完成）开始服务，开启循环检测线程。                               |
| `stopServe`                     | （未完成）停止服务，停止循环检测线程。                               |
| ... | ... |
| `GetCompileVersion`             | 获取编译版本号信息。                                               | 
| `GetCompileTime`                | 获取编译时间信息。                                                 | 
| ... | ... |
| `SetUseBitbltCaptureMode`       | 设置使用Bitblt截图，默认启用，速度较快，效果好，但某些系统不支持。       |
| `SetUseDx11CaptureMode`         | 设置使用DirectX截图，效果较差，但支持win11及以上系统。                |
| `SetHandle`                     | 设置原神客户端的窗口句柄。                                          |
| `SetWorldCenter`                | 设置映射目标地图坐标系的原点中心所在天理坐标模型中的坐标。              |
| `SetWorldScale`                 | 设置映射目标地图坐标系缩放系数与所在天理坐标模型缩放系数的的比值。       |
| ... | ... |
| `SetDisableFileLog`             | 设置禁用日志文件。                                                 |
| `SetEnableFileLog`              | 设置启用日志文件。                                                 |
| ... | ... |
| `DebugCapture`                  | 获取本地视频中的UID、当前人物所在位置以及角度（箭头朝向）并保存至文本中。 |
| `DebugCapturePath`              | 获取本地视频中的UID、当前人物所在位置以及角度（箭头朝向）并保存至指定路径中。 |
| ... | ... |
| `GetTransformOfMap`             | 获取当前人物所在位置、角度（箭头朝向）及所在地图区域并重映射坐标区域。    |
| `GetPositionOfMap`              | 获取所在位置的所在地图区域并重映射坐标区域。                          |
| `GetDirection`                  | 获取当前角度（箭头朝向）。                                          |
| `GetRotation`                   | 获取当前视角方位（视角朝向）。                                      |
| `GetStar`                       | 获取小地图上可见的神瞳。                                           |
| `GetStarJson`                   | 获取小地图上可见的所有神瞳。                                        |
| `GetUID`                        | 获取在屏幕右下角显示的玩家的UID。                                   |
| `GetAllInfo`                    | 获取所在位置、地图区域、角度、视角和UID。所有信息的最新的状态。          |
| ... | ... |
| `GetInfoLoadPicture`            | 获取本地图片中的UID、当前人物所在位置以及角度（箭头朝向）。             |
| `GetInfoLoadVideo`              | 获取本地视频中的UID、当前人物所在位置以及角度（箭头朝向）并保存至文本中。 |
| ... | ... |
| `GetLastErr`                    | 获取最后设置的错误码。                                             |
| `GetLastErrMsg`                 | 获取最后设置的错误信息。                                           | 
| `GetLastErrJson`                | 获取错误码堆栈信息。                                               | 

## 错误处理
- ###  [运行时错误](https://github.com/GengGode/cvAutoTrack/blob/master/doc/%E6%97%A0%E6%B3%95%E8%BF%90%E8%A1%8C.md) 
- ### [编译、链接、打包过程中的异常及错误]()

## 天理坐标模型（待重写）

由于原神游戏中地图会不断扩展，而且不同的物理区块对应的地图贴图分辨率存在差异，所以直接根据贴图像素坐标系不可取，对未来的扩展不利。

所以目前根据原神2.0版本已有的地图区块，规划出了一个较为合理且易于扩展的地图模型，称为天理坐标模型。

之后所有关于地图坐标的接口都会默认以该坐标系输出。

目前模型以游戏中城镇位置的贴图缩放为标准缩放尺寸，即没有放大缩小的尺寸。

根据该尺寸将其他贴图一同缩放到相同比例下，最后拼合成为总图，此时的缩放系数即为天理坐标模型的缩放系数。

在该缩放系数下，原神2.1版本中，总图尺寸为
![坐标范围](https://github.com/GengGode/cvAutoTrack/blob/master/doc/page1.svg)
之后选择位于璃月的请仙典仪祭坛中心作为世界原点，即`( 0 , 0 )`。

之后为了便于Opencv的坐标计算，设定为地图从蒙德到璃月，是横坐标正方向。

地图从璃月到稻妻，是纵坐标正方向。

即

![坐标范围](https://github.com/GengGode/cvAutoTrack/blob/master/doc/page2.svg)

### 渊下宫及地下层岩

该部分区域未来会重做坐标映射，暂时只做简单说明，即地图右上角为原点，其他照例。

