#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

struct Claim;
struct Mechanic;
void loadMechanics(char* b);
void processClaims(char* a, char* c);
void beginTrial(char* txt);
int valueGenerator(Claim oneClaim, Mechanic oneMechanic);

#endif // HEADER_H_INCLUDED
