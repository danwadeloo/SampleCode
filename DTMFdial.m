function xx = DTMFdial(keyNames,fs)
% Daniel Loo, 1/28/15, digital signal processing

%DTMFDIAL Create a signal vector of tones that will dial
% a DTMF (Touch Tone) telephone system.
% Purpose: Outputs a signal vector that is the correct frequency of the tone of the
% key passed, it can be played using the sound(--) function to play the same sound
% the number makes on a touch tone phone
%
% usage: xx = DTMFdial(keyNames,fs)
% keyNames = vector of CHARACTERS containing valid key names
% fs = sampling frequency
% xx = signal vector that is the concatenation of DTMF tones.
%

% 2d array of the keytones to be played
TTkeys = ['1','2','3','A';
'4','5','6','B';
'7','8','9','C';
'*','0','#','D'];
TTcolTones = [1209,1336,1477,1633]; % column and row of tones in Hz
TTrowTones = [697,770,852,941];

numKeys = length(keyNames);

n1 = 1; %variables to be used to track the position of the value vectors
n2 = 0;
Ts = .0003; % Ts = .0003
durDualTone = .4; %-- in seconds
LenDualTone = .4; 
durSilence = 1;
LenSilence = 1;
xx = zeros(1, round(4/(1/fs))); % Make a vector of zeros to be filled later
xs = zeros(1, length(0:1/fs:durSilence)); % silence vector to be used in between tone vectors
tt = 0:1/fs:durDualTone;

% Loop to iterate through the given number of keys
for kk=numKeys:-1:1
    [jrow,jcol] = find(keyNames(kk) == TTkeys); %find the key and where it is on the touch dial
    DTMFsig = cos(2*pi*TTcolTones(jcol)*tt) + cos(2*pi*TTrowTones(jrow)*tt); % create the signal by summing the row frequency and column frequency sinusiods 
    n1 = round(1/Ts); % current position in the final vector
    n2 = n1+length(DTMFsig)-1; % ending position of the final vector, determined by the length of DTMFsig
    xx(n1:n2) = xx(n1:n2) + DTMFsig; % concatenate DTMFsig to the end of the final vector
    xx = [xs xx xs]; % Place silent vectors in between each DTMFsig
end


