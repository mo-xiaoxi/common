%% 模拟调制-产生SSB调制信号

SimTime = 20;         % 时域信号总时间长度
Ts = 0.0001;          % 采样时间间隔
t = 0:Ts:SimTime;     % 时间矢量
N = length(t);        % 总采样点数

Fs = 1/Ts;            % 采样频率
df = Fs/N;            % 计算频率分辨率（事实上df=1/SimTime）
f = -Fs/2:df:Fs/2-df;     % 定义频率矢量（频谱图的横坐标）

figure(1);
mt1 = sin(6*pi*t);     % 产生调制信号
mt2 = -cos(6*pi*t);    % 调制信号移相90度
plot(t,mt1);grid on;
axis([0 1 -1.1 1.1]);
xlabel('时间(s)');ylabel('电压值(V)');
title('调制信号m(t)=sin6πt');

figure(2);
fmt = fft(mt1);
fmt = fftshift(fmt);
% fmt = abs(fmt).^2/T;
fmt = abs(fmt);
plot(f,fmt);grid on;
minF = min(abs(fmt));
maxF = max(abs(fmt));
axis([-10 10 minF maxF]);
xlabel('频率(Hz)');ylabel('频谱幅度值');
title('调制信号幅频特性');

figure(3);
ct1 = cos(120*pi*t);   %产生载波信号
ct2 = sin(120*pi*t);   %载波信号移相90度
plot(t,ct1);%grid on;
axis([0 1 -1.1 1.1]);
xlabel('时间(s)');ylabel('电压值(V)');
title('载波信号c(t)=cos120πt');

figure(4);
st = mt1.*ct1/2-mt2.*ct2/2; %产生上单边带信号
% st = mt1.*ct1/2+mt2.*ct2/2; %产生下单边带信号
plot(t,st);%grid on;
minS = min(st);
maxS = max(st);
axis([0 1 minS maxS]);
xlabel('时间(s)');ylabel('电压值(V)');
title('SSB上单边带已调信号');

figure(5);
fst = fft(st);
fst = fftshift(fst);
fst = abs(fst);
plot(f,fst);grid on;
minF = min(fst);
maxF = max(fst);
axis([-65 65 minF maxF]);
xlabel('频率(Hz)');ylabel('频谱幅度值');
title('SSB上单边带已调信号幅频特性');

