%% 基带信号及其频谱
clc;
clear all;

Ts = 1;  %码元持续时间
N_sample = 1000;  %每个码元的采样点数
N = 1000;  %码元总数
  
%产生单极性NRZ基带信号
% [st,t] = basesig_gen(1,N,1,N_sample);  
% title_str1 = '单极性NRZ基带信号波形';
% title_str2 = '单极性NRZ基带信号频谱';
%产生单极性RZ基带信号
[st,t] = basesig_gen(2,N,1,N_sample);  
title_str1 = '单极性RZ基带信号波形';
title_str2 = '单极性RZ基带信号频谱';
%产生双极性NRZ基带信号
% [st,t] = basesig_gen(3,N,1,N_sample);  
% title_str1 = '双极性NRZ基带信号波形';
% title_str2 = '双极性NRZ基带信号频谱';
%产生双极性RZ基带信号
% [st,t] = basesig_gen(4,N,1,N_sample);  
% title_str1 = '双极性RZ基带信号波形';
% title_str2 = '双极性RZ基带信号频谱';

figure(1);
plot(t,st,'LineWidth',2);grid on;   % 画时域信号波形
M1 = max(st);
m1 = min(st);
axis([0 20 m1-0.1 M1+0.1]);title(title_str1);
xlabel('时间(s)');ylabel('电压值(V)');
title(title_str1);

SimTime = N*Ts;       % 仿真信号的总时间长度
dt = Ts/N_sample;     %采样点之间的时间间隔
Fs = 1/dt;            % 采样频率
df = 1/SimTime;       % 计算频率分辨率
f = -Fs/2:df:Fs/2-df;     % 定义频率矢量（频谱图的横坐标）

%计算频谱并画图
figure(2)
fmt = fft(st);        % 对时域信号进行FFT变换，计算其频谱
fmt = fftshift(fmt);
fmt = abs(fmt);

plot(f,fmt);grid on;
maxF = max(fmt);
minF = min(fmt);
axis([-5 5 minF maxF]);
title(title_str2);