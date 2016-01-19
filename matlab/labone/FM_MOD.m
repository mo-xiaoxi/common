%% 模拟调制-产生FM调制信号

SimTime = 20;         % 时域信号总时间长度
Ts = 0.0001;          % 采样时间间隔
t = 0:Ts:SimTime;     % 时间矢量
N = length(t);        % 总采样点数

Fs = 1/Ts;            % 采样频率
df = Fs/N;            % 计算频率分辨率（事实上df=1/SimTime）
f = -Fs/2:df:Fs/2-df;     % 定义频率矢量（频谱图的横坐标）

kf = 50;              % 调频灵敏度
fc = 60;              % 载波频率

figure(1);
mt = sin(6*pi*t);     % 产生调制信号
plot(t,mt);grid on;
axis([0 1 -1.1 1.1]);
xlabel('时间(s)');ylabel('电压值(V)');
title('调制信号m(t)=sin6πt');

figure(2);
fmt = fft(mt);
fmt = fftshift(fmt);
fmt = abs(fmt);
plot(f,fmt);grid on;
minF = min(abs(fmt));
maxF = max(abs(fmt));
axis([-10 10 minF maxF]);
xlabel('频率(Hz)');ylabel('频谱幅度值');
title('调制信号幅频特性');

% 求被调制信号的积分
int_m = zeros(1,length(t));             % 积分信号初始化
for i=1:length(t)-1
  int_m(i+1) = int_m(i)+mt(i)*Ts;       % 求积分
end

figure(3);
plot(t,int_m);grid on;
minS = min(int_m);
maxS = max(int_m);
axis([0 1 minS maxS]);
xlabel('时间(s)');ylabel('电压值(V)');
title('调制信号积分');

figure(4);
ct = cos(120*pi*t);   %产生载波信号
plot(t,ct);grid on;
axis([0 1 -1.1 1.1]);
xlabel('时间(s)');ylabel('电压值(V)');
title('载波信号c(t)=cos120πt');

figure(5);
st = cos(2*pi*fc*t+2*pi*kf*int_m);  %进行FM调制
plot(t,st);grid on;
minS = min(st);
maxS = max(st);
axis([0 1 minS maxS]);
xlabel('时间(s)');ylabel('电压值(V)');
title('FM已调信号');

figure(6);
fst = fft(st);
fst = fftshift(fst);
fst = abs(fst);
plot(f,fst);grid on;
minF = min(fst);
maxF = max(fst);
axis([-200 200 minF maxF]);
xlabel('频率(Hz)');ylabel('频谱幅度值');
title('FM已调信号幅频特性');

