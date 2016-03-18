T=1000;
Ts=0.001;
t=Ts:Ts:T;
N=length(t);

Fs=1/Ts;
df=Fs/N;
f=-Fs/2:df:Fs/2-df;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(1);
Tsymbol = 1;  %每个码元的持续时间1s（即码元周期为1s）
N_sample = 1000;  %每个码元的采样点数（即采样频率）
N = 1000;  %码元总数
dt = Tsymbol/N_sample;%基带时域信号相邻样点之间的时间间隔
t = 0:dt:(N*N_sample-1)*dt;%产生时间矢量
gt = randint(1,N);    %产生二进制码序列（1000个二进制码）
%以下五行代码将二进制码序列扩充成采样率为1000Hz的基带信号
mt = zeros(N_sample,N);%初始化
for i=1:N_sample
  mt(i,:) = gt;%赋值
end;
mt = reshape(mt,1,N_sample*N);%重组矩阵
plot(t,mt,'LineWidth',2);%绘制两倍粗
axis([0 20 -0.1 1.1]);
grid on;
xlabel('时间（s）');
ylabel('电压值（v）');
title('单极性NRZ波形');%标题
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(2);  %傅里叶变换
fmt=fft(mt);
fmt=fftshift(fmt);
fmt=abs(fmt);
plot(f,fmt);
mins=min(abs(fmt))
maxs=max(abs(fmt))
axis([-5 5 mins maxs]);%
grid on;
xlabel('频率（HZ）');
ylabel('频谱幅度值');
title('单极性NRZ信号频谱');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(3);
% for i = 1:20
%     ASK(i) = mt(i)*sin(pi *i);
% end
si = cos(pi*10*t); %产生一个另外的信号 
ASK = mt.*si;  %合成得ASK
plot(t,ASK); %绘制
axis([0 20 -1 1]);
title('2ASK调制');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(4);  %傅里叶变换
Askf=fft(ASK);
Askf=fftshift(Askf);
Askf=abs(Askf);
plot(f,Askf);
mins=min(abs(Askf))
maxs=max(abs(Askf))
axis([-10 10 mins maxs]);%
grid on;
xlabel('频率（HZ）');
ylabel('频谱幅度值');
title('2ASK调制频谱');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(5);
% for i = 1:
%     ASK(i) = mt(i)*sin(pi *i);
% end
s1 = cos(pi*8*t);
s2 = cos(pi*16*t);
FSK= mt.*s1 + ~mt.*s2;
plot(t,FSK);
axis([0 20 -1 1]);
title('2FSK调制');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(6); %傅里叶变换
Fskf=fft(FSK);
Fskf=fftshift(Fskf);
Fskf=abs(Fskf);
plot(f,Fskf);
mins=min(abs(Fskf))
maxs=max(abs(Fskf))
axis([-10 10 mins maxs]);%
grid on;
xlabel('频率（HZ）');
ylabel('频谱幅度值');
title('2FSK调制频谱');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(7);
% for i = 1:
%     ASK(i) = mt(i)*sin(pi *i);
% end
s1 = cos(pi*10*t);
s2 = -cos(pi*10*t);
PSK= mt.*s1 + ~mt.*s2;
plot(t,PSK);
axis([0 20 -1 1]);
title('2PSK调制');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(8);%傅里叶变换
Pskf=fft(PSK);
Pskf=fftshift(Pskf);
Pskf=abs(Pskf);
plot(f,Pskf);
mins=min(abs(Pskf))
maxs=max(abs(Pskf))
axis([-10 10 mins maxs]);%
grid on;
xlabel('频率（HZ）');
ylabel('频谱幅度值');
title('2PSK调制频谱');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
