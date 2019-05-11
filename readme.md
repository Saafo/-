## 关于空间中较近距离一个点电荷到带电球壳或圆环库仑力是否一致的验证实验
---
### 1.问题描述
设空间中有一点电荷，其带电量为q=5C，距该点电荷20m处有一个带电量为Q=10C的圆环（不包括圆盘中间）或球壳，它们的半径都是r = 10m，如图所示，验证圆环和球壳对该点电荷的库伦力是否相等。 
![](https://ws1.sinaimg.cn/large/005uxhkhgy1g290481lejj313q0djq85.jpg)
### 2.理论推导
#### 1.球壳
对于球壳到点电荷的库仑力计算问题，由于球体的对称性，我们可以只用计算球体的四分之一到点电荷的库伦力，所得结果乘以四倍即得最终结果。对于球壳y > 0, z > 0的部分，我们用第一类曲面积分算出四分之一个球面到点电荷的库仑力之和：  
![](https://ws1.sinaimg.cn/large/005uxhkhgy1g2xg5g8rb9j30hk01vq32.jpg)  
其中，  
![](https://ws1.sinaimg.cn/large/005uxhkhgy1g2xg7b6pl2j30c801vwek.jpg)  
![](https://ws1.sinaimg.cn/large/005uxhkhgy1g2xg82fuh6j303k02tq2q.jpg)  
#### 2.圆环
对于圆环到点电荷的库仑力计算问题，从圆上0~180度圆周上划分微元，积分算出库仑力之和：
![](https://ws1.sinaimg.cn/large/005uxhkhgy1g2xg8qg7h9j309201qjrc.jpg)  
其中，  
![](https://ws1.sinaimg.cn/large/005uxhkhgy1g2xg9khy36j308200wdfp.jpg)  
![](https://ws1.sinaimg.cn/large/005uxhkhgy1g2xgapkywuj306w01jdfq.jpg)  
理论结果为：  
![](https://ws1.sinaimg.cn/large/005uxhkhgy1g2xgb89809j303k01imwy.jpg)  
#### 3.理论误差
![](https://ws1.sinaimg.cn/large/005uxhkhgy1g2xgbqc9r2j30bo01i3yg.jpg)  
### 3.程序验证
#### 1.程序
程序请见[new_phy.c](https://github.com/Saafo/Physics_validating_program/blob/master/new_phy.c)
#### 2.运行结果
![](https://ws1.sinaimg.cn/large/005uxhkhgy1g2xgfph29mj307b01y743.jpg)  
![](https://ws1.sinaimg.cn/large/005uxhkhgy1g2xfv7rtpgj30e60c2gm7.jpg)  
可见当精确度达到1时精确度已经较高，达到  
![](https://ws1.sinaimg.cn/large/005uxhkhgy1g2xgiikhf5j309401iaa0.jpg)  
### 4.实验结论
在点电荷离球心或圆心距离较半径较近的情况下，点电荷到带电球壳或圆环的库仑力有较大的区别。
