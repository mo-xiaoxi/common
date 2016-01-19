%% �ϳɷ�����������FSK�����ź�

clc;clear;

Ts = 1; %��Ԫ����(ÿ����Ԫ����Ϊ1s)
N_sample = 1000;  %ÿ����Ԫ�Ĳ�������
N = 200; %��Ԫ����
dt = Ts/N_sample; %������֮���ʱ����
f1 = 5;  %�ز�1Ƶ��
f2 = 10; %�ز�2Ƶ��

SimTime = N*Ts;       % �����źŵ���ʱ�䳤��
Fs = 1/dt;            % ����Ƶ��
df = 1/SimTime;       % ����Ƶ�ʷֱ���
f = -Fs/2:df:Fs/2-df;     % ����Ƶ��ʸ����Ƶ��ͼ�ĺ����꣩

%�õ�һ����Ԫ�����ڵ��ز��ź�
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

% ��������������
baseC = randint(1,N); 

% ���������Բ���������źŲ���
baseS1 = zeros(N_sample,N);
baseS2 = zeros(N_sample,N);
for i=1:N_sample
  baseS1(i,:) = baseC;
  baseS2(i,:) = ~baseC;
end;
baseS1 = reshape(baseS1,1,N_sample*N);
baseS2 = reshape(baseS2,1,N_sample*N);

% �������ֲ�ͬ�ز���ASK����
ASK_Sig1 = baseS1.*C1;
ASK_Sig2 = baseS2.*C2;

% ���ݻ��������е�ֵѡ��ͬ���ز����γ�2FSK�����źŲ���
FSK_Sig = ASK_Sig1+ASK_Sig2;
t = 0:dt:(N*N_sample-1)*dt;

%��ͼ
M1 = max(baseS1);
m1 = min(baseS1);
subplot(511);
plot(t,baseS1,'LineWidth',1.5);grid on
axis([0 8 m1-0.1 M1+0.1]);title('�����ƻ����ź�baseS1');

M1 = max(baseS2);
m1 = min(baseS2);
subplot(512);
plot(t,baseS2,'LineWidth',1.5);grid on
axis([0 8 m1-0.1 M1+0.1]);title('�����ƻ����źŷ���baseS2');

M1 = max(ASK_Sig1);
m1 = min(ASK_Sig1);
subplot(513);
plot(t,ASK_Sig1);grid on
axis([0 8 m1-0.1 M1+0.1]);title('baseS1��2ASK�����ź�');

M1 = max(ASK_Sig2);
m1 = min(ASK_Sig2);
subplot(514);
plot(t,ASK_Sig2);grid on 
axis([0 8 m1-0.1 M1+0.1]);title('baseS2��2ASK�����ź�');

M1 = max(FSK_Sig);
m1 = min(FSK_Sig);
subplot(515);
plot(t,FSK_Sig);grid on 
axis([0 8 m1-0.1 M1+0.1]);title('2FSK�����ź�');

%����Ƶ�ײ���ͼ
figure(2)
fmt = fft(baseS1);        % ��ʱ���źŽ���FFT�任��������Ƶ��
fmt = fftshift(fmt);
fmt = abs(fmt);

subplot(211)
plot(f,fmt);grid on;
maxF = max(fmt);
minF = min(fmt);
axis([-5 5 minF maxF]);
title('�����ƻ����ź�Ƶ��');

fmt = fft(FSK_Sig);        % ��ʱ���źŽ���FFT�任��������Ƶ��
fmt = fftshift(fmt);
fmt = abs(fmt);
maxF=max(fmt);
minF=min(fmt);
subplot(212)
plot(f,fmt);grid on;
axis([-25 25 minF+20 maxF+20]);
title('FSK�����ź�Ƶ��');