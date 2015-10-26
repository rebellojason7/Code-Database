Jason Joseph Rebello
Harvard University (September 2013 - August 2014) 
Fellow in Computer Science
Viterbi Algorithm

Run Viterbi.m
This script calculates the most probable state sequence given a set of observations, transition probabilities between states, initial probabilities and observation probabilities.

I have written this script based on two examples
example 1: http://ee163.caltech.edu/old/2005/handouts/viterbi.pdf
The correct answer to this problem is given on slide 40.

example 2: http://homepages.ulb.ac.be/~dgonze/TEACHING/viterbi.pdf

Inputs: 
If 's' represents the number of states in the problem, 'o' represents the number of possible observations in a state and 'n' represents size of the observed sequence
obsProb : (s x o) Probability of observers variable in a given state
obsLabels : (1 x o) Cell containing the names of the various output labels
transProb : (s [from] x s [to]) Probabilities of transitioning from one state to the other
translabels : (s x 1) Cell containing names of the states
sequence : (1 x n) Cell containing the observed sequence
initial : (s x 1) Initial probabilities of being in the particular states

Intermediate Outputs:
finalProbs : contains probabilities of transitioning from one state to the other and observing a variable given the observed sequence
states : contains the states of transition where maximum probability was observed from the previous observation

Outputs:
stateSeq : Contains final most probable state sequence

Explanation:

initial ---> S1 ----> S2 ----> ….
	       |	           |
   	      O1	          O2
The viterbi algorithm calculates the most probable state sequence given some observations.
The first calculation would consider the initial probabilities and the first observed data point.
The second calculation would be the probability of the transition from the previous state to the current state and the emission of the second observed point from this state.
Once we go through the entire sequence we then find the highest probability, this is the most probable value given the sequence. We then trace back our steps to find the most probable state sequence.
A better understanding of the algorithm can be achieved after reading example 2
http://homepages.ulb.ac.be/~dgonze/TEACHING/viterbi.pdf

* Please note the way the input matrices have been saved in order for this script to run properly on your example.
I have included 2 examples to help you understand the input matrices and implementation.