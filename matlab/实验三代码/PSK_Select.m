%% 选择法产生二进制PSK调制信号

clc;clear;

Ts = 1; %码元周期(每个码元周期为1s)
N_sample = 1000;  %每个码元的采样点数
N = 200; %码元总数
dt = Ts/N_sample; %采样点之间的时间间隔
fc = 5;  %载波频率

SimTime = N*Ts;       % 仿真信号的总时间长度
Fs = 1/dt;            % 采样频率
df = 1/SimTime;       % 计算频率分辨率
f = -Fs/2:df:Fs/2-df;     % 定义频率矢量（频谱图的横坐标）

%得到一个码元周期内的载波信号
t0 = 0:dt:(N_sample-1)*dt;

CarrB1 = sin(2*pi*fc*t0);
CarrB2 = -CarrB1;

%得到N个码元周期内的载波信号
C1 = zeros(N_sample,N);
C2 = zeros(N_sample,N);
for i=1:N
    C1(:,i) = CarrB1;
    C2(:,i) = CarrB2;
end;
C1 = reshape(C1,1,N_sample*N);
C2 = reshape(C2,1,N_sample*N);

% 产生基带码序列
baseS = randint(1,N); 

% 产生基带信号波形
Code = zeros(N_sample,N);
for i=1:N_sample
  Code(i,:) = baseS;
end;
Code = reshape(Code,1,N_sample*N);

% 根据基带码序列的值选择载波或0，形成2ASK调制信号波形
PSK_Sig = zeros(N_sample,N);
t = 0:dt:(N*N_sample-1)*dt;

for i=1:N
    if (baseS(i)==0)
        PSK_Sig(:,i) = CarrB1;
    else
        PSK_Sig(:,i) = CarrB2;
    end;
end;
PSK_Sig = reshape(PSK_Sig,1,N_sample*N);%拉直成一维数组

%画图
M1 = max(Code);
m1 = min(Code);
subplot(411);
plot(t,Code,'LineWidth',1.5);grid on
axis([0 8 m1-0.1 M1+0.1]);title('基带信号');

M1 = max(C1);
m1 = min(C1);
subplot(412);
plot(t,C1);grid on
axis([0 8 m1-0.1 M1+0.1]);title('载波信号');

M1 = max(C2);
m1 = min(C2);
subplot(413);
plot(t,C2);grid on
axis([0 8 m1-0.1 M1+0.1]);title('反相载波信号');

M1 = max(PSK_Sig);
m1 = min(PSK_Sig);
subplot(414);
plot(t,PSK_Sig);grid on 
axis([0 8 m1-0.1 M1+0.1]);title('2PSK调制信号');

%计算频谱并画图
figure(2)
fmt = fft(Code);        % 对时域信号进行FFT变换，计算其频谱
fmt = fftshift(fmt);
fmt = abs(fmt);

subplot(211)
plot(f,fmt);grid on;
maxF = max(fmt);
minF = min(fmt);
axis([-5 5 minF maxF]);
title('二进制基带信号频谱');

fmt = fft(PSK_Sig);        % 对时域信号进行FFT变换，计算其频谱
fmt = fftshift(fmt);
fmt = abs(fmt);
maxF=max(fmt);
minF=min(fmt);
subplot(212)
plot(f,fmt);grid on;
axis([-25 25 minF+20 maxF+20]);
title('PSK调制信号频谱');