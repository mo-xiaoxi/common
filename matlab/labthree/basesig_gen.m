function [Code,t]=basesig_gen(SymbolType,SymbolNum,SymbolTime,SymbolSampleNum)
% 产生基带信号
% SymbolType -- 基带信号类型：1-单极性不归零码；2-单极性归零码；
%                            3-双极性不归零码；4-双极性归零码；
%                            5-四电平不归零码；6-四电平归零码；
%                            7-八电平不归零码；8-八电平归零码；
% SymbolNum -- 码元个数
% SymbolTime -- 码元持续时间（码元周期Ts），以秒为单位
% SymbolSampleNum -- 每个码元的采样点数
% 调用举例：basssig_gen(1,100,1,8);

  Ts = SymbolTime;
  N_sample = SymbolSampleNum;
  N = SymbolNum;
  dt = Ts/N_sample;
  
  t = 0:dt:(N*N_sample-1)*dt;
  
  Ns = N_sample;  %用于表示占空比
  if ( (SymbolType==2) | (SymbolType==4) | (SymbolType==6) | (SymbolType==8) )
      Ns = N_sample/2;
  end;
  
  switch SymbolType
      case {1,2}
          gt = randint(1,N);    %单极性二电平波形
  
      case {3,4}
          gt = randint(1,N);    %单极性二电平波形
          gt = 2*gt-1;          %双极性二电平波形
  
      case {5,6}
          gt = randint(1,N,4);  %单极性四电平波形
          if (SymbolType == 6) 
            gt = 2*gt-3;        %双极性四电平波形
          end;
  
      case {7,8}
          gt = randint(1,N,8);  %单极性八电平波形
          if (SymbolType == 8) 
            gt = 2*gt-7;        %双极性八电平波形
          end;
          
      otherwise
          error('无效的码型输入值');
          exit;
  end;
  
  Code = zeros(N_sample,N);
  for i=1:Ns
    Code(i,:) = gt;
  end;
  Code = reshape(Code,1,N_sample*N);