%% 模拟相乘法产生二进制ASK调制信号

clc;clear;

Ts = 1; %码元周期(每个码元周期为1s)
N_sample = 1000;  %每个码元的采样点数
N = 200; %码元总数
dt = Ts/N_sample; %采样点之间的时间间隔
fc = 10;  %载波频率

SimTime = N*Ts;       % 仿真信号的总时间长度
Fs = 1/dt;            % 采样频率
df = 1/SimTime;       % 计算频率分辨率
f = -Fs/2:df:Fs/2-df;     % 定义频率矢量（频谱图的横坐标）

t = 0:dt:(N*N_sample-1)*dt; %时间矢量

%得到载波信号
Carr = sin(2*pi*fc*t);

% 产生基带码序列
baseC = randint(1,N); 

% 产生单极性不归零基带信号波形
baseS = zeros(N_sample,N);
for i=1:N_sample
  baseS(i,:) = baseC;
end;
baseS = reshape(baseS,1,N_sample*N);

% 根据模拟相乘法进行ASK调制
ASK_Sig1 = baseS.*Carr;

%画图
M1 = max(baseS);
m1 = min(baseS);
subplot(311);
plot(t,baseS,'LineWidth',1.5);grid on
axis([0 8 m1-0.1 M1+0.1]);title('单极性二进制基带信号');

M1 = max(Carr);
m1 = min(Carr);
subplot(312);
plot(t,Carr,'LineWidth',1);grid on
axis([0 8 m1-0.1 M1+0.1]);title('载波信号');

M1 = max(ASK_Sig1);
m1 = min(ASK_Sig1);
subplot(313);
plot(t,ASK_Sig1,'LineWidth',1);grid on 
axis([0 8 m1-0.1 M1+0.1]);title('单极性码2ASK调制信号');

%计算频谱并画图
figure(2)
fmt = fft(baseS);        % 对时域信号进行FFT变换，计算其频谱
fmt = fftshift(fmt);
fmt = abs(fmt);

subplot(211)
plot(f,fmt);grid on;
maxF = max(fmt);
minF = min(fmt);
axis([-5 5 minF maxF]);
title('单极性基带信号频谱');

fmt = fft(ASK_Sig1);        % 对时域信号进行FFT变换，计算其频谱
fmt = fftshift(fmt);
fmt = abs(fmt);
maxF=max(fmt);
minF=min(fmt);
subplot(212)
plot(f,fmt);grid on;
axis([-25 25 minF+20 maxF+20]);
title('ASK调制信号频谱');