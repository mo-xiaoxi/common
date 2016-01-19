%% �����źż���Ƶ��
clc;
clear all;

Ts = 1;  %��Ԫ����ʱ��
N_sample = 1000;  %ÿ����Ԫ�Ĳ�������
N = 1000;  %��Ԫ����
  
%����������NRZ�����ź�
% [st,t] = basesig_gen(1,N,1,N_sample);  
% title_str1 = '������NRZ�����źŲ���';
% title_str2 = '������NRZ�����ź�Ƶ��';
%����������RZ�����ź�
[st,t] = basesig_gen(2,N,1,N_sample);  
title_str1 = '������RZ�����źŲ���';
title_str2 = '������RZ�����ź�Ƶ��';
%����˫����NRZ�����ź�
% [st,t] = basesig_gen(3,N,1,N_sample);  
% title_str1 = '˫����NRZ�����źŲ���';
% title_str2 = '˫����NRZ�����ź�Ƶ��';
%����˫����RZ�����ź�
% [st,t] = basesig_gen(4,N,1,N_sample);  
% title_str1 = '˫����RZ�����źŲ���';
% title_str2 = '˫����RZ�����ź�Ƶ��';

figure(1);
plot(t,st,'LineWidth',2);grid on;   % ��ʱ���źŲ���
M1 = max(st);
m1 = min(st);
axis([0 20 m1-0.1 M1+0.1]);title(title_str1);
xlabel('ʱ��(s)');ylabel('��ѹֵ(V)');
title(title_str1);

SimTime = N*Ts;       % �����źŵ���ʱ�䳤��
dt = Ts/N_sample;     %������֮���ʱ����
Fs = 1/dt;            % ����Ƶ��
df = 1/SimTime;       % ����Ƶ�ʷֱ���
f = -Fs/2:df:Fs/2-df;     % ����Ƶ��ʸ����Ƶ��ͼ�ĺ����꣩

%����Ƶ�ײ���ͼ
figure(2)
fmt = fft(st);        % ��ʱ���źŽ���FFT�任��������Ƶ��
fmt = fftshift(fmt);
fmt = abs(fmt);

plot(f,fmt);grid on;
maxF = max(fmt);
minF = min(fmt);
axis([-5 5 minF maxF]);
title(title_str2);