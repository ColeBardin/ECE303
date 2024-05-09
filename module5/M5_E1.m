close all; clear all; clc
% Set up communications
arduino = serialport("/dev/ttyACM0",9600,"Timeout",15);
pause(1);

x = 0:100;
y = zeros(1,101);
for K = 0 : 100
    flush(arduino)
    write(arduino,K,'string');
    pause(0.5)
    a=readline(arduino);
    flush(arduino)
    y(K+1)=str2double(a);
    disp([K,y(K+1)]);
end
delete(arduino);
clear arduino;
figure
plot(x,y*5/1023,'ko','MarkerFaceColor','black')
grid on
xlabel('Duty Cycle (%)')
ylabel('Output Voltage (V)')
title("Experiment 1: Output Voltage (V) vs Duty Cycle (%)")