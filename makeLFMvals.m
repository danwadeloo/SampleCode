function sigOut = makeLFMvals( sigLFM, dt )
% Daniel Loo, 2/1/2015, digital signal processing

% MAKELFMVALS generate a linear-FM chirp signal
%
% A chirp signal is a sinusoid whose frequency changes linearly from a
% starting frequency value to an ending frequency, given by the equations:
% cos(psi(t)), where psi(t) = 2*pi*u*t^2 + 2*pi*f0*t + phase
%
% usage: sigOut = makeLFMvals( sigLFM, dt )
% sigLFM.f1 = starting frequency (in Hz) at t = sigLFM.t1
% sigLFM.t1 = starting time (in secs)
% sigLFM.t2 = ending time
% sigLFM.slope = slope of the linear-FM (in Hz per sec)
% sigLFM.complexAmp = defines the amplitude and phase of the FM signal
% dt = time increment for the time vector, typically 1/fs (sampling frequency)
%
% sigOut.values = (vector of) samples of the chirp signal
% sigOut.times = vector of time instants from t=t1 to t=t2
%
if( nargin < 2 ) %-- Allow optional input argument for dt
dt = 1/8000; %-- 8000 samples/sec
end

tt = 0:dt:(sigLFM.t2-sigLFM.t1); % duration of the signal, starting at zero
mu = 2* sigLFM.slope; % mu determines the slope of the signal
f0 = sigLFM.f1; % starting frequency
psi = 2*pi*( f0*tt + mu*tt.*tt); % psi as given in the formula
xx = real( sigLFM.complexAmp * exp(j*psi) ); % the real values of the signal
sigOut.times = tt; 
sigOut.values = xx;

% plot the signal
plotspec(sigOut.values + j*1e-9, 8000, 256);
% spectrogram(sigOut.values, 1024, [], [], 8000, 'yaxis' );

% listen to the signal
soundsc(sigOut.values, 8000);


end