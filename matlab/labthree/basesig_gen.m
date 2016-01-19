function [Code,t]=basesig_gen(SymbolType,SymbolNum,SymbolTime,SymbolSampleNum)
% ���������ź�
% SymbolType -- �����ź����ͣ�1-�����Բ������룻2-�����Թ����룻
%                            3-˫���Բ������룻4-˫���Թ����룻
%                            5-�ĵ�ƽ�������룻6-�ĵ�ƽ�����룻
%                            7-�˵�ƽ�������룻8-�˵�ƽ�����룻
% SymbolNum -- ��Ԫ����
% SymbolTime -- ��Ԫ����ʱ�䣨��Ԫ����Ts��������Ϊ��λ
% SymbolSampleNum -- ÿ����Ԫ�Ĳ�������
% ���þ�����basssig_gen(1,100,1,8);

  Ts = SymbolTime;
  N_sample = SymbolSampleNum;
  N = SymbolNum;
  dt = Ts/N_sample;
  
  t = 0:dt:(N*N_sample-1)*dt;
  
  Ns = N_sample;  %���ڱ�ʾռ�ձ�
  if ( (SymbolType==2) | (SymbolType==4) | (SymbolType==6) | (SymbolType==8) )
      Ns = N_sample/2;
  end;
  
  switch SymbolType
      case {1,2}
          gt = randint(1,N);    %�����Զ���ƽ����
  
      case {3,4}
          gt = randint(1,N);    %�����Զ���ƽ����
          gt = 2*gt-1;          %˫���Զ���ƽ����
  
      case {5,6}
          gt = randint(1,N,4);  %�������ĵ�ƽ����
          if (SymbolType == 6) 
            gt = 2*gt-3;        %˫�����ĵ�ƽ����
          end;
  
      case {7,8}
          gt = randint(1,N,8);  %�����԰˵�ƽ����
          if (SymbolType == 8) 
            gt = 2*gt-7;        %˫���԰˵�ƽ����
          end;
          
      otherwise
          error('��Ч����������ֵ');
          exit;
  end;
  
  Code = zeros(N_sample,N);
  for i=1:Ns
    Code(i,:) = gt;
  end;
  Code = reshape(Code,1,N_sample*N);