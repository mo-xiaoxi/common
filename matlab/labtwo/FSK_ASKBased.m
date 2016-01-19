%% 合成法产生二进制FSK调制信号

clc;clear;

Ts = 1; %码元周期(每个码元周期为1s)
N_sample = 1000;  %每个码元的采样点数
N = 200; %码元总数
dt = Ts/N_sample; %采样点之间的时间间隔
f1 = 5;  %载波1频率
f2 = 10; %载波2频率

SimTime = N*Ts;       % 仿真信号的总时间长度
Fs = 1/dt;            % 采样频率
df = 1/SimTime;       % 计算频率分辨率
f = -Fs/2:df:Fs/2-df;     % 定义频率矢量（频谱图的横坐标）

%得到一个码元周期内的载波信号
t0 = 0:dt:(N_sample-1)*dt;

CarrB1 = sin(2*pi*f1*t0);
CarrB2 = sin(2*pi*f2*t0); 

C1 = zeros(N_sample,N);
C2 = zeros(N_sample,N);
for i=1:N
    C1(:,i) = CarrB1;
    C2(:,i) = CarrB2;
end;
C1 = reshape(C1,1,N_sample*N);
C2 = reshape(C2,1,N_sample*N);

% 产生基带码序列
baseC = randint(1,N); 

% 产生单极性不归零基带信号波形
baseS1 = zeros(N_sample,N);
baseS2 = zeros(N_sample,N);
for i=1:N_sample
  baseS1(i,:) = baseC;
  baseS2(i,:) = ~baseC;
end;
baseS1 = reshape(baseS1,1,N_sample*N);
baseS2 = reshape(baseS2,1,N_sample*N);

% 进行两种不同载波的ASK调制
ASK_Sig1 = baseS1.*C1;
ASK_Sig2 = baseS2.*C2;

% 根据基带码序列的值选择不同的载波，形成2FSK调制信号波形
FSK_Sig = ASK_Sig1+ASK_Sig2;
t = 0:dt:(N*N_sample-1)*dt;

%画图
M1 = max(baseS1);
m1 = min(baseS1);
subplot(511);
plot(t,baseS1,'LineWidth',1.5);grid on
axis([0 8 m1-0.1 M1+0.1]);title('二进制基带信号baseS1');

M1 = max(baseS2);
m1 = min(baseS2);
subplot(512);
plot(t,baseS2,'LineWidth',1.5);grid on
axis([0 8 m1-0.1 M1+0.1]);title('二进制基带信号反相baseS2');

M1 = max(ASK_Sig1);
m1 = min(ASK_Sig1);
subplot(513);
plot(t,ASK_Sig1);grid on
axis([0 8 m1-0.1 M1+0.1]);title('baseS1的2ASK调制信号');

M1 = max(ASK_Sig2);
m1 = min(ASK_Sig2);
subplot(514);
plot(t,ASK_Sig2);grid on 
axis([0 8 m1-0.1 M1+0.1]);title('baseS2的2ASK调制信号');

M1 = max(FSK_Sig);
m1 = min(FSK_Sig);
subplot(515);
plot(t,FSK_Sig);grid on 
axis([0 8 m1-0.1 M1+0.1]);title('2FSK调制信号');

%计算频谱并画图
figure(2)
fmt = fft(baseS1);        % 对时域信号进行FFT变换，计算其频谱
fmt = fftshift(fmt);
fmt = abs(fmt);

subplot(211)
plot(f,fmt);grid on;
maxF = max(fmt);
minF = min(fmt);
axis([-5 5 minF maxF]);
title('二进制基带信号频谱');

fmt = fft(FSK_Sig);        % 对时域信号进行FFT变换，计算其频谱
fmt = fftshift(fmt);
fmt = abs(fmt);
maxF=max(fmt);
minF=min(fmt);
subplot(212)
plot(f,fmt);grid on;
axis([-25 25 minF+20 maxF+20]);
title('FSK调制信号频谱');