close all; clear all; clc
% Set up communications
arduino = serialport("/dev/ttyACM0",9600,"Timeout",15);
pause(1);

x = 0:100;
y1 = zeros(1,101);
y2 = zeros(1,101);
y3 = zeros(1,101);
y4 = zeros(1,101);
y5 = zeros(1,101);

for K = 0 : 100
    flush(arduino)
    write(arduino,K,'string');
    pause(0.5)
    
    a=readline(arduino);
    y1(K+1)=str2double(a);
    
    a=readline(arduino);
    y2(K+1)=str2double(a);
    
    a=readline(arduino);
    y3(K+1)=str2double(a);

    a=readline(arduino);
    y4(K+1)=str2double(a);
    
    a=readline(arduino);
    y5(K+1)=str2double(a);

    flush(arduino)
    
    disp([K,y1(K+1)]);
end
delete(arduino);
clear arduino;
figure
hold on
plot(x,y1*5/1023,'ro','MarkerFaceColor','red')
plot(x,y2*5/1023,'bo','MarkerFaceColor','blue')
plot(x,y3*5/1023,'go','MarkerFaceColor','green')
plot(x,y4*5/1023,'mo','MarkerFaceColor','magenta')
plot(x,y5*5/1023,'yo','MarkerFaceColor','yellow')

grid on
xlabel('Duty Cycle (%)')
ylabel('Output Voltage (V)')
title("Experiment 4: Output Voltage (V) vs Duty Cycle (%)")
legend(["Trial 1", "Trial 2", "Trial 3", "Trial 4", "Trial 5"], Location="southeast")