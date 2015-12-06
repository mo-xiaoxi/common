T = 20;                %仿真的总时间长度20s
Ts = 0.0001;           %采样时间间隔
t = 0:Ts:T;            %定义时间矢量
N = length(t);         %得到总采样点数

Fs = 1/Ts;             %采样频率
df = Fs/N;             %计算频率分辨率
f = -Fs/2:df:Fs/2-df;  %定义频率矢量（频谱图的横坐标）

figure(1);             %定义1号画图窗口
mt = sin(6*pi*t);      %产生调制信号
plot(t,mt);
grid on;    %画调制信号的时域波形图
axis([0 1 -1.1 1.1])        %横纵坐标范围 0 1 横坐标 -1.1到1.1是纵坐标范围
xlabel ('时间（s）');ylabel('电压值（V）')    %横纵坐标显示
title('调制信号m（t）=sin6πt')    %标题

figure(2);             %定义2号画图窗口
fmt = fft(mt);         %对调制信号进行FFT，得到调制信号的频谱
fmt = fftshift(fmt);   %将得到的频谱的频率中心搬移回原点
fmt = abs(fmt);        %得到频谱的幅频特性
plot(f,fmt);           %画调制信号的幅频特性图
grid on;                %画网格
mins=min(abs(fmt));          %傅里叶变换
maxs=max(abs(fmt));          %傅里叶变换
axis([-10 10 mins maxs])     %横纵坐标范围
xlabel('频率（Hz）');ylabel('频谱幅度值') %横纵坐标显示
title('调制信号频谱特性')   %标题

figure(3)
ct = cos(120*pi*t);    %产生调制信号
plot(t,ct);grid on;     %画调制信号的时域波形图 grid on产生表格
axis([0 1 -1.1 1.1])             %横纵坐标范围 0 1 横坐标 0到1是纵坐标范围
xlabel ('时间（s）');ylabel('电压值（V）')    %横纵坐标显示
title('调制信号c(t)=cos120πt')    %标题

figure(4)
st = (1.5+sin(6*pi*t)).*cos(120*pi*t);    %产生调制信号
plot(t,st);
grid on;     %画调制信号的时域波形图 grid on产生表格
axis([0 1 -2.5 2.5])             %横纵坐标范围 0 1 横坐标 0到1是纵坐标范围
xlabel ('时间（s）');ylabel('电压值（V）')    %横纵坐标显示
title('AM已调信号s（t）=（A0+sin6πt）*cos120πt')    %标题

figure(5);             %定义2号画图窗口
fst = fft(st);         %对调制信号进行FFT，得到调制信号的频谱
fst = fftshift(fst);   %将得到的频谱的频率中心搬移回原点
fst = abs(fst);        %得到频谱的幅频特性
plot(f,fst);grid on;   %画调制信号的幅频特性图
mins=min(abs(fst));          %傅里叶变换
maxs=max(abs(fst));          %傅里叶变换
axis([-70 70 mins maxs])     %横纵坐标范围
xlabel('频率（Hz）');ylabel('频谱幅度值') %横纵坐标显示
title('AM已调信号频谱特性');   %标题

figure(6)
dsb = sin(6*pi*t).*cos(120*pi*t);    %产生调制信号
plot(t,dsb);
grid on;     %画调制信号的时域波形图 grid on产生表格
axis([0 1 -1 1])             %横纵坐标范围 0 1 横坐标 0到1是纵坐标范围
xlabel ('时间（s）');ylabel('电压值（V）')    %横纵坐标显示
title('DSB已调信号s(t)=sin(6πt)*cos(120πt)');    %标题

figure(7);             %定义2号画图窗口
fst = fft(dsb);         %对调制信号进行FFT，得到调制信号的频谱
fst = fftshift(fst);   %将得到的频谱的频率中心搬移回原点
fst = abs(fst);        %得到频谱的幅频特性
plot(f,fst);
grid on;   %画调制信号的幅频特性图
mins=min(abs(fst));          %傅里叶变换
maxs=max(abs(fst));          %傅里叶变换
axis([-70 70 mins maxs])     %横纵坐标范围
xlabel('频率（Hz）');ylabel('频谱幅度值') %横纵坐标显示
title('DSB已调信号信号频谱特性');   %标题


figure(8)
%原信号 sin(6*pi*t)
%载波c(t)=cos(120*pi)
USB =  1/2*cos(120*pi*t).*sin(6*pi*t)+1/2*sin(120*pi*t).*cos(6*pi*t);    %产生调制信号
plot(t,USB);
grid on;     %画调制信号的时域波形图 grid on产生表格
axis([0 1 -0.5 0.5])             %横纵坐标范围 0 1 横坐标 0到1是纵坐标范围
xlabel ('时间（s）');ylabel('电压值（V）')    %横纵坐标显示
title('SSB上边带已调信号');    

figure(9);             %定义2号画图窗口
fst = fft(USB);         %对调制信号进行FFT，得到调制信号的频谱
fst = fftshift(fst);   %将得到的频谱的频率中心搬移回原点
fst = abs(fst);        %得到频谱的幅频特性
plot(f,fst);
grid on;   %画调制信号的幅频特性图
mins=min(abs(fst));          %傅里叶变换
maxs=max(abs(fst));          %傅里叶变换
axis([-70 70 mins maxs])     %横纵坐标范围
xlabel('频率（Hz）');ylabel('频谱幅度值') %横纵坐标显示
title('SSB上边带信号频谱特性');   %标题

figure(10)
%原信号 sin(6*pi*t)
%载波c(t)=cos(120*pi*t)
s = sin(6*pi*t);                  % modulating signal
kf=50;                   %设定调频指数 
int_mt=zeros(1,N);  
for i=1:N-1        
    int_mt(i+1)=int_mt(i)+s(i)*Ts;        %求信号m(t)的积分  
end                                        %调制，产生已调信号 
sfm=cos(120*pi*t+2*pi*kf*int_mt);      %调制信号
          
plot(t,sfm);
axis([0 1 -1 1]);   %横纵坐标范围 0 1 横坐标 0到1是纵坐标范围
grid on;
xlabel ('时间（s）');ylabel('电压值（V）')    %横纵坐标显示
title('FM调制信号');    


figure(11);             %定义2号画图窗口
fst = fft(sfm);         %对调制信号进行FFT，得到调制信号的频谱
fst = fftshift(fst);   %将得到的频谱的频率中心搬移回原点
fst = abs(fst);        %得到频谱的幅频特性
plot(f,fst);
grid on;   %画调制信号的幅频特性图
mins=min(abs(fst));          %傅里叶变换
maxs=max(abs(fst));          %傅里叶变换
axis([-200 200 mins maxs]);     %横纵坐标范围
xlabel('频率（Hz）');ylabel('频谱幅度值') %横纵坐标显示
title('FM调制信号频谱特性');   %标题







