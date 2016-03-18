T = 1000;                %仿真的总时间长度20s
Ts = 0.001;            %采样时间间隔
t = Ts:Ts:T;            %定义时间矢量
N = length(t);         %得到总采样点数
duty=50;               %占空比50%

Fs = 1/Ts;             %采样频率
df = Fs/N;             %计算频率分辨率
f = -Fs/2:df:Fs/2-df;  %定义频率矢量（频谱图的横坐标）

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(1)
Tsymbol = 1;  %每个码元的持续时间1s（即码元周期为1s）
N_sample = 1000;  %每个码元的采样点数（即采样频率）
N = 1000;  %码元总数
dt = Tsymbol/N_sample;%基带时域信号相邻样点之间的时间间隔
t = 0:dt:(N*N_sample-1)*dt;%产生时间矢量

gt = randint(1,N);    %产生二进制码序列（1000个二进制码）
%以下五行代码将二进制码序列扩充成采样率为1000Hz的基带信号
mt = zeros(N_sample,N);
for i=1:N_sample
  mt(i,:) = gt;
end;
mt = reshape(mt,1,N_sample*N); %重新矩阵的行数，列数，维数
plot(t,mt,'LineWidth',2);  %调整线的粗细
axis([0 20 -0.1 1.1]);
xlabel ('时间（s）');
ylabel('电压值（V）')    %横纵坐标显示
title('单极性NRZ波形')    %标题
grid on;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(2)              %定义2号画图窗口
fmt = fft(mt);         %对调制信号进行FFT，得到调制信号的频谱
fmt = fftshift(fmt);   %将得到的频谱的频率中心搬移回原点
fmt = abs(fmt);        %得到频谱的幅频特性
plot(f,fmt);
grid on;   %画调制信号的幅频特性图
mins=min(abs(fmt))          %傅里叶变换
maxs=max(abs(fmt))          %傅里叶变换
axis([-5 5 mins maxs])     %横纵坐标范围
xlabel('频率（Hz）');ylabel('频谱幅度值') %横纵坐标显示
title('单极性NRZ信号频谱')   %标题



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(3)
Tsymbol = 1;  %每个码元的持续时间1s（即码元周期为1s）
N_sample = 1000;  %每个码元的采样点数（即采样频率）
N = 1000;  %码元总数
dt = Tsymbol/N_sample;%基带时域信号相邻样点之间的时间间隔
t = 0:dt:(N*N_sample-1)*dt;%产生时间矢量

gt = randint(1,N);    %产生二进制码序列（1000个二进制码）

%以下五行代码将二进制码序列扩充成采样率为1000Hz的基带信号
mt = zeros(N_sample,N);
for i=1:500
  mt(i,:) = gt;%占空比百分之50
end;
mt = reshape(mt,1,N_sample*N);%重组矩阵

plot(t,mt,'LineWidth',2);
axis([0 20 -0.1 1.1]);
xlabel ('时间（s）');
ylabel('电压值（V）')    %横纵坐标显示
title('占空比50%单极性NRZ波形')    %标题
grid on;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(4)              %定义4号画图窗口
fmt = fft(mt);         %对调制信号进行FFT，得到调制信号的频谱
fmt = fftshift(fmt);   %将得到的频谱的频率中心搬移回原点
fmt = abs(fmt);        %得到频谱的幅频特性
plot(f,fmt);
grid on;   %画调制信号的幅频特性图
mins=min(abs(fmt))          %傅里叶变换
maxs=max(abs(fmt))          %傅里叶变换
axis([-5 5 mins maxs])     %横纵坐标范围
xlabel('频率（Hz）');ylabel('频谱幅度值') %横纵坐标显示
title('占空比50%单极性NRZ信号频谱')   %标题



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(5)
Tsymbol = 1;  %每个码元的持续时间1s（即码元周期为1s）
N_sample = 1000;  %每个码元的采样点数（即采样频率）
N = 1000;  %码元总数
dt = Tsymbol/N_sample;%基带时域信号相邻样点之间的时间间隔
t = 0:dt:(N*N_sample-1)*dt;%产生时间矢量

gt = 2.*ceil(rand(N,1)-0.5)-1    %产生双级性二进制码序列（1000个二进制码）  -1表示不归零
%以下五行代码将二进制码序列扩充成采样率为1000Hz的基带信号
mt = zeros(N_sample,N);
for i=1:N_sample
  mt(i,:) = gt;
end;
mmt = reshape(mt,1,N_sample*N);
plot(t,mmt,'LineWidth',2);
axis([0 20 -1.1 1.1]);
xlabel ('时间（s）');
ylabel('电压值（V）')    %横纵坐标显示
title('双极性NRZ波形')    %标题
grid on;


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(6)              %定义6号画图窗口
fmt = fft(mmt);         %对调制信号进行FFT，得到调制信号的频谱
fmt = fftshift(fmt);   %将得到的频谱的频率中心搬移回原点
fmt = abs(fmt);        %得到频谱的幅频特性
plot(f,fmt);
grid on;   %画调制信号的幅频特性图
mins=min(abs(fmt))          %傅里叶变换
maxs=max(abs(fmt))          %傅里叶变换
axis([-5 5 mins maxs])     %横纵坐标范围
xlabel('频率（Hz）');ylabel('频谱幅度值') %横纵坐标显示
title('双极性NRZ信号频谱')   %标题

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(7)
Tsymbol = 1;  %每个码元的持续时间1s（即码元周期为1s）
N_sample = 1000;  %每个码元的采样点数（即采样频率）
N = 1000;  %码元总数
dt = Tsymbol/N_sample;%基带时域信号相邻样点之间的时间间隔
t = 0:dt:(N*N_sample-1)*dt;%产生时间矢量

gt = 2.*ceil(rand(N,1)-0.5)-1    %产生双极性二进制码序列（1000个二进制码）

%以下五行代码将二进制码序列扩充成采样率为1000Hz的基带信号
mt = zeros(N_sample,N);
for i=1:500
  mt(i,:) = gt; %占空比 百分之50
end;
mt = reshape(mt,1,N_sample*N);

plot(t,mt,'LineWidth',2);%两倍粗细的线
axis([0 20 -1.1 1.1]);
xlabel ('时间（s）');
ylabel('电压值（V）')    %横纵坐标显示
title('占空比50%双极性NRZ波形')    %标题
grid on;


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(8)              %定义8号画图窗口
fmt = fft(mt);         %对调制信号进行FFT，得到调制信号的频谱
fmt = fftshift(fmt);   %将得到的频谱的频率中心搬移回原点
fmt = abs(fmt);        %得到频谱的幅频特性
plot(f,fmt);
grid on;   %画调制信号的幅频特性图
mins=min(abs(fmt))          %傅里叶变换
maxs=max(abs(fmt))          %傅里叶变换
axis([-5 5 mins maxs])     %横纵坐标范围
xlabel('频率（Hz）');ylabel('频谱幅度值') %横纵坐标显示
title('占空比50%双极性NRZ信号频谱')   %标题


