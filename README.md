VLPRDemo
========
车牌识别Demo

用FFmpeg打开视频，并获取图像真图片进行车牌识别


[2014.2.10 17:20:04]
R2
1.完成用FFmpeg打开并获取视频流数据
2.调用算法库，并输出识别车牌
3.可以显示但是失真，需要修改
下一步：
1.修改显示失真问题
2.完善界面输出
3.增加配置

[2014.2.11 16:44:39]
1. 正常显示图片，不再失真
2. 车牌识别调用成功，并用3个线程来处理，1）播放线程;2）处理结果线程，包含存储图片车车牌图片并显示；3)识别线程
下一步
1. 将识别过程拆分成 视频流获取线程（存入队列）和识别线程，以提供速度
2. 修改界面


