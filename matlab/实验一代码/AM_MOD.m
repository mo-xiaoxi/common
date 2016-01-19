%% 模拟调制-产生AM调制信号

SimTime = 20;         % 时域信号总时间长度
Ts = 0.0001;          % 采样时间间隔
t = 0:Ts:SimTime;     % 时间矢量
N = length(t);        % 总采样点数

Fs = 1/Ts;            % 采样频率
df = Fs/N;            % 计算频率分辨率（事实上df=1/SimTime）
f = -Fs/2:df:Fs/2-df;     % 定义频率矢量（频谱图的横坐标）

figure(1);
mt = sin(6*pi*t);     % 产生调制信号
plot(t,mt);grid on;   % 画时域信号波形
axis([0 1 -1.1 1.1]);
xlabel('时间(s)');ylabel('电压值(V)');
title('调制信号m(t)=sin6πt');

figure(2);
fmt = fft(mt);        % 对时域信号进行FFT变换，计算其频谱
fmt = fftshift(fmt);
fmt = abs(fmt);
plot(f,fmt);grid on;
minF = min(abs(fmt));
maxF = max(abs(fmt));
axis([-10 10 minF maxF]);
xlabel('频率(Hz)');ylabel('频谱幅度值');
title('调制信号幅频特性');

figure(3);
ct = cos(120*pi*t);   %产生载波信号
plot(t,ct);grid on;
axis([0 1 -1.1 1.1]);
xlabel('时间(s)');ylabel('电压值(V)');
title('载波信号c(t)=cos120πt');

figure(4);
A0 = 1.5;
st = (A0+mt).*ct;     % 进行AM调制
plot(t,st);grid on;
minS = min(st);
maxS = max(st);
axis([0 1 minS maxS]);
xlabel('时间(s)');ylabel('电压值(V)');
title('AM已调信号s(t)=(A0+sin6πt)*cos120πt');

figure(5);
fst = fft(st);
fst = fftshift(fst);
fst = abs(fst);
plot(f,fst);grid on;
minF = min(fst);
maxF = max(fst);
axis([-65 65 minF maxF]);
xlabel('频率(Hz)');ylabel('频谱幅度值');
title('AM已调信号幅频特性');

