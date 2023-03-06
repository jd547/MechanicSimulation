# Mechanic Simulation

This program simulates the process of mechanical repairs.
*claims.txt* is a test file containing repairing requirements. The idea is to find a mechanic in *mechanics.txt* that is able to repair a car with the given claim according to a certain of rules.

## Rules

- the successful probability follows a normal distribution, and its mean and standard deviations is
calculated as follows:
- Mean = mechanic ability - claim complexity
- Standard deviation = claim uncertainty + mechanic variability

## Compilation
'''
g++ main.cpp header.cpp -o mSim
'''

## Usage 
'''
./mSim claims.txt mechanics.txt output.txt
'''
