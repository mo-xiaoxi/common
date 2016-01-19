%% ѡ�񷨲���������PSK�����ź�

clc;clear;

Ts = 1; %��Ԫ����(ÿ����Ԫ����Ϊ1s)
N_sample = 1000;  %ÿ����Ԫ�Ĳ�������
N = 200; %��Ԫ����
dt = Ts/N_sample; %������֮���ʱ����
fc = 5;  %�ز�Ƶ��

SimTime = N*Ts;       % �����źŵ���ʱ�䳤��
Fs = 1/dt;            % ����Ƶ��
df = 1/SimTime;       % ����Ƶ�ʷֱ���
f = -Fs/2:df:Fs/2-df;     % ����Ƶ��ʸ����Ƶ��ͼ�ĺ����꣩

%�õ�һ����Ԫ�����ڵ��ز��ź�
t0 = 0:dt:(N_sample-1)*dt;

CarrB1 = sin(2*pi*fc*t0);
CarrB2 = -CarrB1;

%�õ�N����Ԫ�����ڵ��ز��ź�
C1 = zeros(N_sample,N);
C2 = zeros(N_sample,N);
for i=1:N
    C1(:,i) = CarrB1;
    C2(:,i) = CarrB2;
end;
C1 = reshape(C1,1,N_sample*N);
C2 = reshape(C2,1,N_sample*N);

% ��������������
baseS = randint(1,N); 

% ���������źŲ���
Code = zeros(N_sample,N);
for i=1:N_sample
  Code(i,:) = baseS;
end;
Code = reshape(Code,1,N_sample*N);

% ���ݻ��������е�ֵѡ���ز���0���γ�2ASK�����źŲ���
PSK_Sig = zeros(N_sample,N);
t = 0:dt:(N*N_sample-1)*dt;

for i=1:N
    if (baseS(i)==0)
        PSK_Sig(:,i) = CarrB1;
    else
        PSK_Sig(:,i) = CarrB2;
    end;
end;
PSK_Sig = reshape(PSK_Sig,1,N_sample*N);%��ֱ��һά����

%��ͼ
M1 = max(Code);
m1 = min(Code);
subplot(411);
plot(t,Code,'LineWidth',1.5);grid on
axis([0 8 m1-0.1 M1+0.1]);title('�����ź�');

M1 = max(C1);
m1 = min(C1);
subplot(412);
plot(t,C1);grid on
axis([0 8 m1-0.1 M1+0.1]);title('�ز��ź�');

M1 = max(C2);
m1 = min(C2);
subplot(413);
plot(t,C2);grid on
axis([0 8 m1-0.1 M1+0.1]);title('�����ز��ź�');

M1 = max(PSK_Sig);
m1 = min(PSK_Sig);
subplot(414);
plot(t,PSK_Sig);grid on 
axis([0 8 m1-0.1 M1+0.1]);title('2PSK�����ź�');

%����Ƶ�ײ���ͼ
figure(2)
fmt = fft(Code);        % ��ʱ���źŽ���FFT�任��������Ƶ��
fmt = fftshift(fmt);
fmt = abs(fmt);

subplot(211)
plot(f,fmt);grid on;
maxF = max(fmt);
minF = min(fmt);
axis([-5 5 minF maxF]);
title('�����ƻ����ź�Ƶ��');

fmt = fft(PSK_Sig);        % ��ʱ���źŽ���FFT�任��������Ƶ��
fmt = fftshift(fmt);
fmt = abs(fmt);
maxF=max(fmt);
minF=min(fmt);
subplot(212)
plot(f,fmt);grid on;
axis([-25 25 minF+20 maxF+20]);
title('PSK�����ź�Ƶ��');