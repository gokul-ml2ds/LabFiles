% Discrete Time Signal Processing Lab 5
% Design of Butterworth IIR Filter
% MATLAB version R2018a
% Date : 16-02-2021

clc;
clear;
close all;

wp = 0.2*pi;
ws = 0.3*pi;
Ap = 1;
As = 15;
F = 1;
T = 1/F;

ohm_p = 2*tan(wp/2)/T;
ohm_s = 2*tan(ws/2)/T;

N = 0.5*log10((10^(0.1*As)-1)/(10^(0.1^Ap)-1))/log10(ohm_s/ohm_p);
N = ceil(N);

ohm_c = ohm_p/((10^(0.1*Ap)-1)^(1/(2*N)));

% Calculating location of poles
poles = zeros(1,N);
zeroes = [];

for k=0:N-1
    poles(k+1) = ohm_c*(cos((N+2*k+1)*pi/N)+sin((N+2*k+1)*pi/N)*1i);
end

% Calculating and plotting the analog transfer function (s-domain)
[num, den] = zp2tf(zeroes,poles,ohm_c^N);
% den = round(den);
sys = tf(num,den);
pzmap(sys);
ax = gca();
set(ax,'FontSize',13);
figure();


numerator = zeros(1,N+1);
denominator = zeros(1,N+1);
denominator(N+1) = (ohm_c*T)^N; 

for p=0:N
    numerator(p+1) = nchoosek(N,p)*((ohm_c*T)^N);
    denominator(p+1) = denominator(p+1)+((-1)^p)*nchoosek(N,p)*((2)^N);
end

H_z = tf(numerator,denominator,T);
pzmap(H_z);
ax = gca();
set(ax,'FontSize',13);
figure();

[h,w] = freqz(flip(numerator),flip(denominator),'whole',2001);

plot(w,20*log10(abs(h)),'r','LineWidth',3);
ax = gca();
set(ax,'xlim',[0 pi],'FontSize',12);
title('Magnitude response in dB');
xlabel('Frequency (rad/s)');
ylabel('Magnitude (dB)');
grid on;
figure();

% h = h./abs(h);
% freqz(numerator,denominator);
% figure();

plot(w.*pi,abs(h),'r','LineWidth',3);
ax = gca();
set(ax,'xlim',[0 pi],'FontSize',12);
title('Magnitude response');
xlabel('Frequency (rad/s)');
ylabel('Magnitude');
grid on;
figure();

phasez(flip(numerator),flip(denominator));
ax = gca();
set(ax,'FontSize',13);
figure();

w = 0:0.01:pi;
z = zeros(1,length(w));
H = zeros(1,length(w));

for k=1:length(w)
    z(k) = cos(w(k)) + sin(w(k))*1i;
    H(k) = evalfr(H_z,z(k));
    % H(k) = ((ohm_c*(z(k)+1)).^N)/((2*(z(k)-1)).^N+(ohm_c*T).^N);
end

H = H./abs(H(1));

plot(w.*pi,abs(H),'r','LineWidth',2);
ax = gca();
set(ax,'xlim',[0 pi],'FontSize',15);
title('Magnitude response (Normalized)','FontSize',15);
xlabel('Frequency (rad/s)','FontSize',15);
ylabel('Magnitude','FontSize',15);
grid on;
