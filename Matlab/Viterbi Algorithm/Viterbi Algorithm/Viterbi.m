% Jason Joseph Rebello
% Harvard University (September 2013 - August 2014) 
% Fellow in Computer Science
% Viterbi Algorithm

% Run Viterbi.m
% This script calculates the most probable state sequence given a set of
% observations, transition probabilities between states, initial
% probabilities and observation probabilities.

clear all
clc
close all

%% Load data

% example 1: http://ee163.caltech.edu/old/2005/handouts/viterbi.pdf
% The correct answer to this problem is given on slide 40.
load obsProb1.mat
load obsLabels1.mat
load transProb1.mat
load transLabels1.mat
load initial1.mat
load sequence1.mat

%% example 2: http://homepages.ulb.ac.be/~dgonze/TEACHING/viterbi.pdf
load obsProb2.mat
load obsLabels2.mat
load transProb2.mat
load transLabels2.mat
load initial2.mat
load sequence2.mat

%% Convert probabilities to log (to avoid underflow)
transProb = log2(transProb);
obsProb = log2(obsProb);
initial = log2(initial);

% Calculate the Probabilities and state transition
finalProbs = zeros(size(transLabels,1),size(sequence,2));
states = zeros(size(transLabels,1),size(sequence,2));

for i=1:size(sequence,2)
   obsVar = sequence{1,i};
   index = find([obsLabels{:}] == obsVar);
   if i == 1
       finalProbs(:,i) = initial + obsProb(:,index);
   else
       for j=1:size(obsProb,1)
            temp = finalProbs(:,i-1) + obsProb(j,index)*ones(size(obsProb,1),1) + transProb(:,j);
            [finalProbs(j,i) states(j,i)] = max(temp);
       end
   end
end

% Get the final States
[~,idx] = max(finalProbs(:,end));
stateSeq = transLabels(states(idx,end),1);
val = states(idx,i);
for i=size(states,2):-1:2
    stateSeq = [transLabels(states(val,i),1) stateSeq];
    val = states(val,i);
end
display('Given the Sequence:')
sequence
display('The most probable states are:')
stateSeq