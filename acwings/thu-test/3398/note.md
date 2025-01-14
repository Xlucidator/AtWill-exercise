## 3398. 升次方

求满足$n = a^m$的$a$  $\iff$  求解 $f(x) = x^m - n = 0$  



#### 牛顿迭代法

基本算法

- 设$r$为$f(x)=0$的根，选择初始近似解$x_0$ 
- 过$(x_0, f(x_0))$做曲线$y=f(x)$的切线$l:y=f'(x_0)(x-x_0)+f(x_0)$，与$x$轴交于$x_1=x_0-\frac{f(x_0)}{f'(x_0)}$，则得到$r$的1次近似值$x_1$ ；如是循环迭代
- 得到递推式 $x_{n+1}=x_n-\frac{f(x_n)}{f'(x_n)}$ ，即$r$的$n+1$次近似值

初值估计：一开始还想错成$x = \log_m n$了，那样的话就很容易直接求了$\frac{\log_2n}{\log_2m}$ 

-  $x^m = n \iff x = \sqrt[m]{n}$，大致可推知 $x$的位数 = n的位数 / m
- 然后从高位开始，二分的确定是多少：仅对**如此确定最高位**，并不逐位进行，要不然复杂度太高（每一位二分都是$\log_2{10}$次，每次要计算$x^m$，共判断$\lg n / m$轮），牛顿迭代法应该收敛的更快些



#### 快速傅里叶变换

$O(n\log n)$的多项式乘法，普通的为$O(n^2)$ 

https://www.bilibili.com/video/BV1E14y1k7Ky/

- 【FFT】 Coefficient $\implies$ Value ： Evaluation 递归拆分；利用奇偶性，引入复数
- 【IFFT】 Value $\implies$ Coefficient ： Interpolation 将Evaluation过程看作矩阵，称为DFT；逆向的系数计算即求DFT的逆；经过计算发现DFT的逆和DFT本身相差无几，则可复用上面的FFT算法，将$\omega$换成$\frac{1}{n}\omega^{-1}$即可

