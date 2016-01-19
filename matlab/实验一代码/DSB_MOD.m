%% ģ�����-����DSB�����ź�

SimTime = 20;         % ʱ���ź���ʱ�䳤��
Ts = 0.0001;          % ����ʱ����
t = 0:Ts:SimTime;     % ʱ��ʸ��
N = length(t);        % �ܲ�������

Fs = 1/Ts;            % ����Ƶ��
df = Fs/N;            % ����Ƶ�ʷֱ��ʣ���ʵ��df=1/SimTime��
f = -Fs/2:df:Fs/2-df;     % ����Ƶ��ʸ����Ƶ��ͼ�ĺ����꣩

figure(1);
mt = sin(6*pi*t);     % ���������ź�
plot(t,mt);grid on;
axis([0 1 -1.1 1.1]);
xlabel('ʱ��(s)');ylabel('��ѹֵ(V)');
title('�����ź�m(t)=sin6��t');

figure(2);
fmt = fft(mt);
fmt = fftshift(fmt);
fmt = abs(fmt);
plot(f,fmt);grid on;
minF = min(abs(fmt));
maxF = max(abs(fmt));
axis([-10 10 minF maxF]);
xlabel('Ƶ��(Hz)');ylabel('Ƶ�׷���ֵ');
title('�����źŷ�Ƶ����');

figure(3);
ct = cos(120*pi*t);   %�����ز��ź�
plot(t,ct);grid on;
axis([0 1 -1.1 1.1]);
xlabel('ʱ��(s)');ylabel('��ѹֵ(V)');
title('�ز��ź�c(t)=cos120��t');

figure(4);
st = mt.*ct;  %����DSB����
plot(t,st);grid on;
minS = min(st);
maxS = max(st);
axis([0 1 minS maxS]);
xlabel('ʱ��(s)');ylabel('��ѹֵ(V)');
title('DSB�ѵ��ź�s(t)=sin6��t*cos120��t');

figure(5);
fst = fft(st);
fst = fftshift(fst);
fst = abs(fst);
plot(f,fst);grid on;
minF = min(fst);
maxF = max(fst);
axis([-65 65 minF maxF]);
xlabel('Ƶ��(Hz)');ylabel('Ƶ�׷���ֵ');
title('DSB�ѵ��źŷ�Ƶ����');

